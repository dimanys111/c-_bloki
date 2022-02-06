#ifndef BLOKMODEL_H
#define BLOKMODEL_H

#include <QAbstractItemModel>
#include <treeitem.h>

class BlokModel : public QAbstractItemModel
{
    Q_OBJECT

public:
    BlokModel(QObject *parent = 0);
    ~BlokModel();
    QVariant data(const QModelIndex &index, int role) const;
    Qt::ItemFlags flags(const QModelIndex &index) const;
    QVariant headerData(int section, Qt::Orientation orientation,
                        int role = Qt::DisplayRole) const;
    QModelIndex index(int row, int column,
                      const QModelIndex &parent = QModelIndex()) const;
    QModelIndex parent(const QModelIndex &index) const;
    int rowCount(const QModelIndex &parent = QModelIndex()) const;
    int columnCount(const QModelIndex &parent = QModelIndex()) const;
    bool insertRow(int position, const QModelIndex &index = QModelIndex());
    bool insertRows(int position, int rows, const QModelIndex &index = QModelIndex());
    bool removeRows(int position, int rows, const QModelIndex &index = QModelIndex());
    bool removeRow(int row, const QModelIndex &parent);
    QStringList mimeTypes() const;
    QMimeData *mimeData(const QModelIndexList &indexes) const;
    bool dropMimeData(const QMimeData *data, Qt::DropAction action,
                              int row, int column, const QModelIndex &parent);
    bool canDropMimeData(const QMimeData * data, Qt::DropAction action,
                         int row, int column, const QModelIndex & parent) const;
    bool setData(const QModelIndex &index, const QVariant &value, int role=Qt::EditRole);
    TreeItem *item(const QModelIndex &parent) const;
    Qt::DropActions supportedDropActions() const;
    QModelIndex indexForTreeItem(TreeItem *Item);
    int rowForTreeItem(TreeItem *Item);
    bool insertTreeItem(int position, TreeItem *Item, TreeItem *parentItem);
    bool remowTreeItem(TreeItem *Item);
    bool provChild(TreeItem *parentItem, TreeItem *childItem) const;
    bool saveFile(QString fileName);
    bool loadFile(QString fileName);
    bool exportFile(QString fileName,const QModelIndex &modind);
    bool CopyTreeItem(int position, TreeItem *Item, TreeItem *parentItem);
    TreeItem *copyTreeItem(TreeItem *Item);
    bool insertRow(int position, const QModelIndex &indcopy, const QModelIndex &parent);
    void sort(int column, Qt::SortOrder order = Qt::AscendingOrder);
    bool import(QString fileName, const QModelIndex &modind);
private:
    void setupModelData(const QStringList &lines, TreeItem *parent);
    TreeItem *rootItem;
signals:

};

#endif // BLOKMODEL_H
