#include "treeitem.h"

TreeItem::TreeItem()
{

}

TreeItem::TreeItem(const QList<QVariant> &data, TreeItem *parent)
{
    parentItem = parent;
    listItem = data;
    DateVipusk.setDate(2007,10,25);
    Primech="Новый";
}

TreeItem::~TreeItem()
{
    qDeleteAll(childItems);
}

bool TreeItem::saveFile(QDataStream& out)
{
    out<<listItem;
    QList<QVariant> l;
    l<<DateVipusk;
    l<<Primech;
    l<<Form_Pasport;
    out<<l;
    out<<listIstor;
    out<<childItems.size();
    for(int i=0;i<childItems.size();i++)
    {
        childItems.at(i)->saveFile(out);
    }
}

bool TreeItem::loadFile(QDataStream& in)
{
    in>>listItem;
    QList<QVariant> l;
    in>>l;
    DateVipusk=l.at(0).toDate();
    Primech=l.at(1).toString();
    Form_Pasport=l.at(2).toString();
    in>>listIstor;
    int size;
    in>>size;
    int n=childItems.size();
    for(int i=n;i<n+size;i++)
    {
        QList<QVariant> l;
        childItems.append(new TreeItem(l,this));
        childItems.at(i)->loadFile(in);
    }
}

void TreeItem::appendChild(TreeItem *item)
{
    childItems.append(item);
}

void TreeItem::insertChild(int position, TreeItem *item)
{
    childItems.insert(position,item);
    item->setParent(this);
}

void TreeItem::removChild(int position)
{
    delete childItems.at(position);
    childItems.removeAt(position);
}

void TreeItem::removChild(TreeItem* Child)
{
    childItems.removeAll(Child);
    delete Child;
}

void TreeItem::removChildAll()
{
    for(int i=0;i<childItems.size();i++)
    {
        delete childItems.first();
        childItems.removeFirst();
    }
}

void TreeItem::copy(TreeItem *Item)
{
    childItems.clear();
    for(int i=0;i<Item->childItems.size();i++)
    {
        childItems<<new TreeItem();
        *(childItems.last())=*(Item->childItems.at(i));
        childItems.last()->copy(Item->childItems.at(i));
        childItems.last()->setParent(this);
    }
}
QList<TreeItem *>* TreeItem::getChildItems()
{
    return &childItems;
}

QStringList TreeItem::getIstor()
{
    return listIstor;
}

void TreeItem::addIstor(QString s)
{
    listIstor<<s;
}

QDate TreeItem::isDate()
{
    return DateVipusk;
}

QString TreeItem::isPrimech()
{
    return Primech;
}

void TreeItem::setDate(QDate d)
{
    DateVipusk=d;
}

void TreeItem::setPrimech(QString s)
{
    Primech=s;
}

void TreeItem::setForm_Pasport(QString s)
{
    Form_Pasport=s;
}

TreeItem *TreeItem::child(int row)
{
    return childItems.value(row);
}

int TreeItem::childCount() const
{
    return childItems.count();
}

int TreeItem::row() const
{
    if (parentItem)
        return parentItem->childItems.indexOf(const_cast<TreeItem*>(this));

    return 0;
}

int TreeItem::columnCount() const
{
    return listItem.count();
}

QVariant TreeItem::data(int column) const
{
    return listItem.value(column);
}

QList<QVariant> TreeItem::data() const
{
    return listItem;
}

bool TreeItem::setData(const QVariant &value,int column)
{
    listItem.replace(column,value);
}

TreeItem *TreeItem::parent()
{
    return parentItem;
}

void TreeItem::setParent(TreeItem* parent)
{
     parentItem=parent;
}

ElemIst::ElemIst()
{

}

void ElemIst::obnSpis()
{
    spis<<dataNach;
    spis<<dataKon;
    spis<<parent;
}

QDate ElemIst::getDataNach() const
{
    return dataNach;
}

void ElemIst::setDataNach(const QDate &value)
{
    dataNach = value;
    obnSpis();
}
QDate ElemIst::getDataKon() const
{
    return dataKon;
}

void ElemIst::setDataKon(const QDate &value)
{
    dataKon = value;
    obnSpis();
}
QString ElemIst::getParent() const
{
    return parent;
}

void ElemIst::setParent(const QString &value)
{
    parent = value;
    obnSpis();
}
QList<QVariant> ElemIst::getSpis() const
{
    return spis;
}

void ElemIst::setSpis(const QList<QVariant> &value)
{
    spis = value;
}



