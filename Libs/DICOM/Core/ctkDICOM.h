/*=========================================================================

  Library:   CTK

  Copyright (c) Kitware Inc. 
  All rights reserved.
  Distributed under a BSD License. See LICENSE.txt file.

  This software is distributed "AS IS" WITHOUT ANY WARRANTY; without even
  the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
  See the above copyright notice for more information.

=========================================================================*/

#ifndef __ctkDICOM_h
#define __ctkDICOM_h

// Qt includes 
#include <QObject>
#include <QSqlDatabase>

// CTK includes
#include <ctkPimpl.h>

#include "CTKDICOMCoreExport.h"

class ctkDICOMPrivate;
class CTK_DICOM_CORE_EXPORT ctkDICOM : public QObject
{
  Q_OBJECT
public:
  typedef QObject Superclass;
  explicit ctkDICOM(QObject* parent = 0);
  virtual ~ctkDICOM();
  
  ///
  /// open the SQLite database in @param file. If the file does not
  /// exist, a new database is created and initialized with the
  /// default schema
  virtual bool openDatabase(const QString& file);

  const QSqlDatabase& database() const;
  const QString& GetLastError() const; 
  
  ///
  /// close the database. It must not be used afterwards.
  void closeDatabase();  
  ///
  /// delete all data and reinitialize the database.
  bool initializeDatabase(const char* schemaFile = ":/dicom/dicom-schema.sql");
private:
  CTK_DECLARE_PRIVATE(ctkDICOM);
};

#endif
