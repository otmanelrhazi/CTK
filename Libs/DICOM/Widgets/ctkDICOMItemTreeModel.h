/*=========================================================================

  Library:   CTK

  Copyright (c) Kitware Inc. 
  All rights reserved.
  Distributed under a BSD License. See LICENSE.txt file.

  This software is distributed "AS IS" WITHOUT ANY WARRANTY; without even
  the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
  See the above copyright notice for more information.

=========================================================================*/

#ifndef __ctkDICOMItemTreeModel_h
#define __ctkDICOMItemTreeModel_h

// Qt includes 
#include <QAbstractItemModel>
#include <QModelIndex>

// CTK includes
#include <ctkPimpl.h>

#include "CTKDICOMWidgetsExport.h"

class ctkDICOMItemTreeModelPrivate;

class CTK_DICOM_WIDGETS_EXPORT ctkDICOMItemTreeModel : public QAbstractItemModel
{
public:
  typedef QAbstractItemModel Superclass;
  explicit ctkDICOMItemTreeModel(QObject* parent=0);
  virtual ~ctkDICOMItemTreeModel();

  virtual QModelIndex index(int row, int column,
                            const QModelIndex &parent = QModelIndex()) const;
                            
  virtual QModelIndex parent(const QModelIndex &child) const;
    
  virtual Qt::ItemFlags flags(const QModelIndex &index) const;

  virtual QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const;

  virtual QVariant headerData(int section, Qt::Orientation orientation,
                                int role = Qt::DisplayRole) const;

  virtual int rowCount(const QModelIndex &parent = QModelIndex()) const;
  virtual int columnCount(const QModelIndex &parent = QModelIndex()) const;

private:
  CTK_DECLARE_PRIVATE(ctkDICOMItemTreeModel);
};

#endif
