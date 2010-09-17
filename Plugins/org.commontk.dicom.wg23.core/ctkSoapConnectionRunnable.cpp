/*=============================================================================

  Library: CTK

  Copyright (c) 2010 German Cancer Research Center,
    Division of Medical and Biological Informatics

  Licensed under the Apache License, Version 2.0 (the "License");
  you may not use this file except in compliance with the License.
  You may obtain a copy of the License at

    http://www.apache.org/licenses/LICENSE-2.0

  Unless required by applicable law or agreed to in writing, software
  distributed under the License is distributed on an "AS IS" BASIS,
  WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
  See the License for the specific language governing permissions and
  limitations under the License.

=============================================================================*/


#include "ctkSoapConnectionRunnable_p.h"

#include <QTcpSocket>

ctkSoapConnectionRunnable::ctkSoapConnectionRunnable(int socketDescriptor)
  : socketDescriptor(socketDescriptor)
{
}

ctkSoapConnectionRunnable::~ctkSoapConnectionRunnable()
{

}

void ctkSoapConnectionRunnable::run()
{
  QTcpSocket tcpSocket;
  if (!tcpSocket.setSocketDescriptor(socketDescriptor))
  {
    // error handling
    return;
  }


  while (tcpSocket.state() == QTcpSocket::ConnectedState)
  {
    //const int timeout = 5 * 1000;

    tcpSocket.waitForReadyRead(-1);

    readClient(tcpSocket);
  }
}

void ctkSoapConnectionRunnable::readClient(QTcpSocket& socket)
{
  bool wsdlRequest = false;
  //qDebug() << socket->readAll();
  while (socket.canReadLine()) {
    QString line = socket.readLine();
    qDebug() << line;
    if(line.contains("?wsdl HTTP"))
    {
      wsdlRequest = true;
    }
    if (line.trimmed().isEmpty())
    {
      QString content;
      if(wsdlRequest)
      {
        wsdlRequest = false;
        emit incomingWSDLMessage("wsdl", &content);
      }
      else
      {
        // Read the http body, which contains the soap message
        QByteArray body = socket.readAll();
        qDebug() << body;

        if (body.trimmed().isEmpty())
        {
          qDebug() << "Message body empty";
          content = "";
        }
        else
        {
          QtSoapMessage msg;
          if (!msg.setContent(body))
          {
            qDebug() << "QtSoap import failed:" << msg.errorString();
            return;
          }

          QtSoapMessage reply;
          emit incomingSoapMessage(msg, &reply);

          if (reply.isFault())
          {
            qDebug() << "QtSoap reply faulty";
            return;
          }

          qDebug() << "SOAP reply:";

          content = reply.toXmlString();
        }
      }

      QByteArray block;
      block.append("HTTP/1.1 200 OK\n");
      block.append("Content-Type: text/xml;charset=utf-8\n");
      block.append("Content-Length: ").append(QString::number(content.size())).append("\n");
      block.append("\n");

      block.append(content);

      //qDebug() << block;

      socket.write(block);

    }
  }
}
