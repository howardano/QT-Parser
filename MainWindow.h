#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include <QApplication>
#include <QMainWindow>
#include <QWidget>
#include <QGridLayout>
#include <QTextEdit>
#include <QMenuBar>
#include <QDockWidget>
#include <QErrorMessage>
#include <QListWidget>
#include <QListView>
#include <QComboBox>
#include <QTreeView>
#include <QTreeWidget>
#include <QPushButton>
#include <QFileDialog>
#include <QtXml>
#include <QXmlQuery>
#include <QXmlAttributes>
#include <QXmlSimpleReader>
#include "xmlparser.h"
#include <QDirModel>

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    int a = 0;
    QWidget* mainWidget;
    //QGridLayout* mainLayout;
    QVBoxLayout* mainLayout;
    QMenuBar* mainMenu;
    QTextEdit* text;
    QTreeWidget* tree;
    QTreeView* tree_view;
    QModelIndex* selected_indx;
    QModelIndex big_tree_view_index;
    QPushButton* download_button;
    QPushButton* execute_button;
private slots:
    void OpenFile();
    void Close();
    void ProcessQuery();
    void DownloadQuery();
    void slotCustomMenuRequested(QPoint);
    void closeXMLTreeView();
    void MakeBig();
    QVariant data(const QModelIndex &index,int role);
};


#endif // MAINWINDOW_H
