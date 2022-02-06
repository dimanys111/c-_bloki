#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QDebug>
#include <QFileDialog>
#include <QCommonStyle>
#include <QSortFilterProxyModel>

TreeItem* item;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->treeView->setUniformRowHeights(true);
    model=new BlokModel(this);
    ui->treeView->setModel(model);

    this->installEventFilter(this);

    ui->treeView->setSelectionMode(QAbstractItemView::SingleSelection);
    ui->treeView->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->treeView->setDragDropMode(QAbstractItemView::DragDrop);
    ui->treeView->setDragEnabled(true);
    ui->treeView->setAcceptDrops(true);
    ui->treeView->setDropIndicatorShown(true);
    ui->treeView->setDefaultDropAction(Qt::MoveAction);
    //ui->treeView->setSortingEnabled(true);
    //ui->treeView->setDragDropOverwriteMode(true);
}

bool MainWindow::eventFilter(QObject *object, QEvent *event)
{
//    if (object == ui->treeView) {

//    }
//    qDebug()<<object->children()
    return false;
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_clicked()
{
    QModelIndex m=select();
    model->insertRow(model->rowCount(m),m);
}

void MainWindow::on_treeView_clicked(const QModelIndex &index)
{
    TreeItem* item=model->item(index);
    itemTek=item;
    ui->dateEdit->setDate(item->isDate());
    ui->lineEdit->setText(item->isPrimech());
    ui->listWidget_2->clear();
    ui->listWidget_2->addItems(item->getIstor());
}

void MainWindow::on_lineEdit_editingFinished()
{
    QModelIndex m=select();
    model->item(m)->setPrimech(ui->lineEdit->text());
}

void MainWindow::on_dateEdit_editingFinished()
{
    QModelIndex m=select();
    model->item(m)->setDate(ui->dateEdit->date());
}

void MainWindow::on_pushButton_2_clicked()
{
    QModelIndex m=select();

    model->insertRow(m.row()+1,m,m.parent());
}

QModelIndex MainWindow::select()
{
    if(ui->treeView->selectionModel()->selectedIndexes().size())
        return ui->treeView->selectionModel()->selectedIndexes().first();
    else
    {
        QModelIndex m=QModelIndex();
        return m;
    }
}


void MainWindow::on_pushButton_4_clicked()
{
    QString fileName = QFileDialog::getSaveFileName(this);
    if (fileName.isEmpty())
        return;

    model->saveFile(fileName);
}

void MainWindow::on_pushButton_3_clicked()
{
    QString fileName = QFileDialog::getOpenFileName(this);
    if (!fileName.isEmpty())
        model->loadFile(fileName);
}

void MainWindow::on_pushButton_5_clicked()
{
    QModelIndex m=select();
    model->removeRow(m.row(),m.parent());
}

void MainWindow::on_pushButton_6_clicked()
{
    QString fileName = QFileDialog::getSaveFileName(this);
    if (fileName.isEmpty())
        return;
    QModelIndex m=select();
    model->exportFile(fileName,m);
}

void MainWindow::on_pushButton_11_clicked()
{
    QModelIndex m=select();
    QString fileName = QFileDialog::getOpenFileName(this);
    if (!fileName.isEmpty())
        model->import(fileName,m);
}

void MainWindow::on_pushButton_8_clicked()
{

}

void MainWindow::on_pushButton_9_clicked()
{
    QListWidgetItem *aitem=new QListWidgetItem();
    aitem->setText("123");
    aitem->setFlags(aitem->flags() | Qt::ItemIsEditable);
    ui->listWidget_2->addItem(aitem);
    itemTek->addIstor("123");
}

void MainWindow::on_lineEdit_2_editingFinished()
{
    QModelIndex m=select();
    model->item(m)->setPrimech(ui->lineEdit->text());
}

void MainWindow::on_listWidget_2_itemChanged(QListWidgetItem *item)
{

}
