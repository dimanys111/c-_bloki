#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QListWidgetItem>
#include "blokmodel.h"


namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

    bool eventFilter(QObject *object, QEvent *event);
    QModelIndex select();
private slots:
    void on_pushButton_clicked();

    void on_treeView_clicked(const QModelIndex &index);

    void on_lineEdit_editingFinished();

    void on_dateEdit_editingFinished();

    void on_pushButton_2_clicked();

    void on_pushButton_4_clicked();

    void on_pushButton_3_clicked();

    void on_pushButton_5_clicked();

    void on_pushButton_6_clicked();

    void on_pushButton_11_clicked();

    void on_pushButton_8_clicked();

    void on_pushButton_9_clicked();

    void on_lineEdit_2_editingFinished();

    void on_listWidget_2_itemChanged(QListWidgetItem *item);

private:
    TreeItem* itemTek;
    BlokModel * model;
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
