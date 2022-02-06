#ifndef TREEITEM_H
#define TREEITEM_H

#include <QVariant>
#include <QDate>
#include <QDataStream>

class ElemIst
{
public:
    ElemIst();
    void obnSpis();
    QDate getDataNach() const;
    void setDataNach(const QDate &value);
    QDate getDataKon() const;
    void setDataKon(const QDate &value);

    QString getParent() const;
    void setParent(const QString &value);

    QList<QVariant> getSpis() const;
    void setSpis(const QList<QVariant> &value);

private:
    QDate dataNach;
    QDate dataKon;
    QString parent;
    QList<QVariant> spis;
};

class TreeItem
{
public:
    TreeItem();
    TreeItem(const QList<QVariant> &data, TreeItem *parent = 0);
    ~TreeItem();

    void appendChild(TreeItem *child);

    TreeItem *child(int row);
    int childCount() const;
    int columnCount() const;
    QVariant data(int column) const;
    QList<QVariant> data() const;
    bool setData(const QVariant &value, int column);
    int row() const;
    TreeItem *parent();
    void insertChild(int position, TreeItem *item);
    void removChild(int position);
    QDate isDate();
    QString isPrimech();

    void setDate(QDate d);
    void setPrimech(QString s);
    void setForm_Pasport(QString s);
    void removChild(TreeItem *Child);
    void setParent(TreeItem *parent);

    bool saveFile(QDataStream &out);
    bool loadFile(QDataStream &in);
    void removChildAll();
    void copy(TreeItem *Item);
    QList<TreeItem *>* getChildItems();
    QStringList getIstor();
    void addIstor(QString s);
private:
    QList<TreeItem*> childItems;
    QStringList listIstor;
    QList<QVariant> listItem;
    QDate DateVipusk;
    QString Primech;
    QString Form_Pasport;
    TreeItem *parentItem;
};

#endif // TREEITEM_H
