#include "blokmodel.h"
#include "QMimeData"
#include "QDataStream"
#include "QDebug"
#include "QFile"
#include "QMessageBox"
#include <QSortFilterProxyModel>

BlokModel::BlokModel(QObject *parent)
     : QAbstractItemModel(parent)
 {
     QList<QVariant> rootData;
     rootData << "ЛА/Блоки"<<"Номер";
     rootItem = new TreeItem(rootData);
     //setupModelData(data.split(QString("\n")), rootItem);
 }

 BlokModel::~BlokModel()
 {
     delete rootItem;
 }

 TreeItem * BlokModel::item(const QModelIndex &parent)
             const
 {
     TreeItem *parentItem;

     if (!parent.isValid())
         parentItem = rootItem;
     else
         parentItem = static_cast<TreeItem*>(parent.internalPointer());
     return parentItem;
 }

 QModelIndex BlokModel::index(int row, int column, const QModelIndex &parent)
             const
 {
     if (!hasIndex(row, column, parent))
         return QModelIndex();

     TreeItem *parentItem;

     if (!parent.isValid())
         parentItem = rootItem;
     else
         parentItem = static_cast<TreeItem*>(parent.internalPointer());

     TreeItem *childItem = parentItem->child(row);
     if (childItem)
         return createIndex(row, column, childItem);
     else
         return QModelIndex();
 }

 QModelIndex BlokModel::parent(const QModelIndex &index) const
 {
     if (!index.isValid())
         return QModelIndex();

     TreeItem *childItem = static_cast<TreeItem*>(index.internalPointer());
     TreeItem *parentItem = childItem->parent();

     if (parentItem == rootItem)
         return QModelIndex();

     return createIndex(parentItem->row(), 0, parentItem);
 }

 int BlokModel::rowCount(const QModelIndex &parent) const
 {
     TreeItem *parentItem;
//     if (parent.column() > 0)
//         return 0;

     if (!parent.isValid())
         parentItem = rootItem;
     else
         parentItem = static_cast<TreeItem*>(parent.internalPointer());

     return parentItem->childCount();
 }

 int BlokModel::columnCount(const QModelIndex &parent) const
 {
     if (parent.isValid())
         return static_cast<TreeItem*>(parent.internalPointer())->columnCount();
     else
         return rootItem->columnCount();
 }

 bool BlokModel::insertRow(int position, const QModelIndex &index)
 {
     insertRows(position,1,index);
 }

 bool BlokModel::insertRow(int position, const QModelIndex &indcopy, const QModelIndex &parent)
 {
     QModelIndex p=parent;
     if(!p.isValid())
     {
         p=QModelIndex();
     }

     if(!(position>=0))
     {
         position=0;
     }

     beginInsertRows(p, position, position);

     TreeItem *item = static_cast<TreeItem*>(p.internalPointer());

     if (!item)
         item=rootItem;

     item->insertChild(position,new TreeItem(this->item(indcopy)->data(),item));

     endInsertRows();
     return true;

 }

 struct SortPredicate
 {
     SortPredicate(int column, Qt::SortOrder order = Qt::AscendingOrder):m_column(column),m_sortOrder(order)
     {
     }
     bool operator()(const QVariantList &who,const QVariantList &with )
     {
         if(m_sortOrder==Qt::AscendingOrder)
             return who[m_column].toString()<with[m_column].toString();
         else
             return who[m_column].toString()>with[m_column].toString();
     }
 private:
     int m_column;
     Qt::SortOrder m_sortOrder;

 };

 void BlokModel::sort(int column, Qt::SortOrder order)
 {
     //qSort(mModelData.begin(),mModelData.end(),SortPredicate(column,order));
 }

 QVariant BlokModel::data(const QModelIndex &index, int role) const
 {
     if (!index.isValid())
         return QVariant();

     if (role == Qt::DisplayRole || role == Qt::EditRole)
     {
         TreeItem *item = static_cast<TreeItem*>(index.internalPointer());
         return item->data(index.column());
     }
     else
         return QVariant();
 }

 Qt::ItemFlags BlokModel::flags(const QModelIndex &index) const
 {
     if (!index.isValid())
         return Qt::ItemIsEnabled | Qt::ItemIsDropEnabled;

     return QAbstractItemModel::flags(index) | Qt::ItemIsEditable |
             Qt::ItemIsDragEnabled | Qt::ItemIsSelectable| Qt::ItemIsDropEnabled;
 }

 QVariant BlokModel::headerData(int section, Qt::Orientation orientation,
                                int role) const
 {
     if (orientation == Qt::Horizontal && role == Qt::DisplayRole)
         return rootItem->data(section);

     return QVariant();
 }

 int BlokModel::rowForTreeItem(TreeItem * Item)
 {
     return Item->parent()->getChildItems()->indexOf(Item);
 }

 QModelIndex BlokModel::indexForTreeItem(TreeItem * Item)
 {
     if(Item==rootItem)
         return QModelIndex();
     int row=rowForTreeItem(Item);
     int column=0;
     return createIndex(row,column,Item);
 }

 bool BlokModel::insertTreeItem(int position, TreeItem * Item, TreeItem *parentItem)
 {
     QModelIndex par=indexForTreeItem(parentItem);

     beginInsertRows(par, position, position);

     parentItem->getChildItems()->insert(position,Item);

     Item->setParent(parentItem);

     endInsertRows();
     return true;
 }

 TreeItem * BlokModel::copyTreeItem(TreeItem * Item)
 {
     TreeItem *t=new TreeItem();
     *t=*Item;
     t->copy(Item);
     return t;
 }

 bool BlokModel::CopyTreeItem(int position, TreeItem * Item, TreeItem *parentItem)
 {
     QModelIndex par=indexForTreeItem(parentItem);

     beginInsertRows(par, position, position);

     TreeItem *item=copyTreeItem(Item);

     parentItem->getChildItems()->insert(position,item);

     item->setParent(parentItem);

     endInsertRows();
     return true;
 }



 bool BlokModel::remowTreeItem(TreeItem * Item)
 {
     TreeItem *parentItem=Item->parent();
     QModelIndex par=indexForTreeItem(parentItem);
     int position=rowForTreeItem(Item);
     beginRemoveRows(par, position, position);

     parentItem->getChildItems()->removeAt(position);

     endRemoveRows();
     return true;
 }

 bool BlokModel::insertRows(int position, int rows, const QModelIndex &parent)
 {
     beginInsertRows(parent, position, position+rows-1);

     TreeItem *item = static_cast<TreeItem*>(parent.internalPointer());

     if (!item)
         item=rootItem;

     for (int row = 0; row < rows; ++row) {
         QList<QVariant> data;
         data<<"123"<<"321";
         item->insertChild(position,new TreeItem(data,item));
     }

     endInsertRows();
     return true;
 }

 bool BlokModel::removeRows(int position, int rows, const QModelIndex &parent)
 {
     beginRemoveRows(parent, position, position+rows-1);

     TreeItem *item = static_cast<TreeItem*>(parent.internalPointer());

     if (!item)
         item=rootItem;

     for (int row = 0; row < rows; ++row) {
         item->removChild(position);
     }
     endRemoveRows();
     return true;
 }

 bool BlokModel::removeRow(int row, const QModelIndex &parent)
 {
     if(row>=0)
     {
         if(parent.isValid())
            return removeRows(row, 1, parent);
         else
         {
             if(rowCount()>row)
             {
                 return removeRows(row, 1);
             }
         }
     }
     else
        return false;
 }

 QStringList BlokModel::mimeTypes() const
 {
     QStringList types;
     types << "application/vnd.text.list";
     return types;
 }

 QMimeData *BlokModel::mimeData(const QModelIndexList &indexes) const
 {
     QMimeData *mimeData = new QMimeData();
     QByteArray encodedData;

     QDataStream stream(&encodedData, QIODevice::WriteOnly);

     TreeItem *childItem = static_cast<TreeItem*>(indexes.first().internalPointer());
     quint64 i= (quint64)childItem;
     stream << i;

     i= (quint64)(&(indexes.first()));
     stream << i;

     mimeData->setData("application/vnd.text.list", encodedData);
     return mimeData;
 }

 bool BlokModel::dropMimeData(const QMimeData *data, Qt::DropAction action, int row, int column, const QModelIndex &parent)
 {
     qDebug() << action;
      if (action == Qt::IgnoreAction)
          return false;

      if (!data->hasFormat("application/vnd.text.list"))
          return false;

//      if (column > 0)
//          return false;

      int beginRow;

      if (row != -1)
          beginRow = row;

      else if (parent.isValid())
          beginRow = rowCount(parent);

      else
          beginRow = rowCount(QModelIndex());

      QByteArray encodedData = data->data("application/vnd.text.list");
      QDataStream stream(&encodedData, QIODevice::ReadOnly);

      int Item;
      stream >> Item;
      TreeItem *childItem=(TreeItem *)Item;

      TreeItem *parentItem;
      if (!parent.isValid())
          parentItem = rootItem;
      else
          parentItem = static_cast<TreeItem*>(parent.internalPointer());

      if (action == Qt::MoveAction)
      {
          if (provChild(parentItem,childItem))
          {
              remowTreeItem(childItem);

              insertTreeItem(beginRow, childItem, parentItem);
          }
      }
      else
      {
          if (action == Qt::CopyAction)
          {
              CopyTreeItem(beginRow, childItem, parentItem);
          }
      }
      return false;
 }

 bool BlokModel::canDropMimeData(const QMimeData *data, Qt::DropAction action, int row, int column, const QModelIndex &parent) const
 {
     if (action == Qt::IgnoreAction)
         return true;

     if (!data->hasFormat("application/vnd.text.list"))
         return false;

//      if (column > 0)
//          return false;

     int beginRow;

     if (row != -1)
         beginRow = row;

     else if (parent.isValid())
         beginRow = rowCount(parent);

     else
         beginRow = rowCount(QModelIndex());

     QByteArray encodedData = data->data("application/vnd.text.list");
     QDataStream stream(&encodedData, QIODevice::ReadOnly);

     int Item;
     stream >> Item;
     TreeItem *childItem=(TreeItem *)Item;

     TreeItem *parentItem;
     if (!parent.isValid())
         parentItem = rootItem;
     else
         parentItem = static_cast<TreeItem*>(parent.internalPointer());

     if (provChild(parentItem,childItem))
     {
         return true;
     }
     else
     {
         return false;
     }
 }

 bool BlokModel::provChild(TreeItem *parentItem,TreeItem *childItem) const
 {
     TreeItem *par=parentItem;
     if(par==childItem)
     {
         return false;
     }
     while(par!=rootItem)
     {
         par=par->parent();
         if(par==childItem)
         {
             return false;
         }
     }
     return true;
 }

 Qt::DropActions BlokModel::supportedDropActions() const
 {
     return Qt::CopyAction | Qt::MoveAction;
 }


 bool BlokModel::setData(const QModelIndex &index,
                               const QVariant &value, int role)
 {
     if (index.isValid() && role == Qt::EditRole) {
         TreeItem *item = static_cast<TreeItem*>(index.internalPointer());
         item->setData(value,index.column());
         emit dataChanged(index, index);
         return true;
     }
     return false;
 }

bool BlokModel::saveFile(QString fileName)
{
    QFile file(fileName);
    if (!file.open(QFile::WriteOnly)) {
        return false;
    }

    QDataStream out(&file);
    rootItem->saveFile(out);

    return true;
}

bool BlokModel::exportFile(QString fileName,const QModelIndex&modind)
{
    QFile file(fileName);
    if (!file.open(QFile::WriteOnly)) {
        return false;
    }

    QDataStream out(&file);
    item(modind)->saveFile(out);

    return true;
}

bool BlokModel::import(QString fileName,const QModelIndex&modind)
{
    QFile file(fileName);
    if (!file.open(QFile::ReadOnly)) {
        return false;
    }

    QDataStream in(&file);
    beginResetModel();
    item(modind)->loadFile(in);
    endResetModel();
    return true;
}

bool BlokModel::loadFile(QString fileName)
{
    delete rootItem;
    QList<QVariant> rootData;
    rootData << "ЛА/Блоки"<<"Номер";
    rootItem = new TreeItem(rootData);

    QFile file(fileName);
    if (!file.open(QFile::ReadOnly)) {
        return false;
    }

    QDataStream in(&file);
    beginResetModel();
    rootItem->loadFile(in);
    endResetModel();
    return true;
}


