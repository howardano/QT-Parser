#include "MainWindow.h"
#include <QPalette>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    resize(800, 600);
    QMenu* menu = new QMenu("File", this);
    menu->addAction("&Оpen", this, SLOT(OpenFile()), Qt::CTRL + Qt::Key_O);
    menu->addAction("&Close", this, SLOT(Close()), Qt::CTRL + Qt::Key_E);
    mainMenu = new QMenuBar(this);
    mainMenu->addMenu(menu);
    setMenuBar(mainMenu);
    tree = new QTreeWidget;
    tree_view = new QTreeView(this);
    text = new QTextEdit(this);
    download_button = new QPushButton("Load", this);
    download_button->setFixedHeight(28);
    execute_button = new QPushButton("Start", this);
    execute_button->setFixedHeight(28);
    tree_view->setModel(tree->model());
    tree_view->setContextMenuPolicy(Qt::CustomContextMenu);
    tree_view->setHeaderHidden(true);
    connect(execute_button, SIGNAL(clicked()), this, SLOT(ProcessQuery()));
    connect(download_button, SIGNAL(clicked()), this, SLOT(DownloadQuery()));
    connect(tree_view, SIGNAL(customContextMenuRequested(QPoint)), this, SLOT(slotCustomMenuRequested(QPoint)));
    mainLayout = new QVBoxLayout(this);
    mainLayout->setSpacing(5);
    mainLayout->addWidget(tree_view);
    mainLayout->addWidget(text);
    mainLayout->addWidget(download_button);
    mainLayout->addWidget(execute_button);
    mainWidget = new QWidget(this);
    mainWidget->setLayout(mainLayout);
    setCentralWidget(mainWidget);
    mainWidget->show();
}

MainWindow::~MainWindow()
{
}

void MainWindow::OpenFile()
{
    QString file_path = QFileDialog::getOpenFileName(this, "Choose",
                                                     "C:/Users/user/Desktop/Dz212", "*.xml");
    if (file_path.isEmpty()) {
        return;
    }

    QString file_name = file_path.section('/', -1);
    QFile file(file_path);

    xmlparser handler(tree, file_name);
    QXmlInputSource source(&file);
    QXmlSimpleReader reader;

    reader.setContentHandler(&handler);
    if (!reader.parse(source)) {
        (new QErrorMessage(this))->showMessage("Can not do that!");
    }
    file.close();
}

void MainWindow::Close()
{
    tree->clear();
}

void MainWindow::ProcessQuery()
{
    QString str_query = text->toPlainText();
    auto idx = tree_view->currentIndex();
    while (idx.parent().isValid()) {
        idx = idx.parent();
    }
    if (!selected_indx->isValid() || selected_indx==nullptr)
    {
        selected_indx=&idx;
    }
    QFile xml_file("C:/Users/user/Desktop/Dz212/" + selected_indx->data().toString());
    QXmlQuery query;
    if (xml_file.open(QIODevice::ReadOnly)) {
        query.bindVariable("inputDocument", &xml_file);
        query.setQuery(str_query);
        if (!query.isValid()) {
            (new QErrorMessage(this))->showMessage("Can not do that");
            return;
        }

        QStringList listOutput;
        QString strOutput;
        if (!query.evaluateTo(&listOutput)) {
            (new QErrorMessage(this))->showMessage("Can not do that");
            return;
        }
        xml_file.close();

        QListWidget* list_widget = new QListWidget;
        for (auto it : listOutput) {
            list_widget->addItem(it);
        }
        QListView* list_view = new QListView;
        list_view->setModel(list_widget->model());
        QDockWidget* doc = new QDockWidget;
        doc->setWidget(list_view);
        doc->resize(500,600);
        doc->show();
    }
}

void MainWindow::DownloadQuery()
{
    QString file_path = QFileDialog::getOpenFileName(this, "Choose", "C:/Users/user/Desktop/Dz212", "*.xq");
    if (file_path.isEmpty()) {
        return;
    }
    QFile file(file_path);

    if (file.exists() && file.open(QIODevice::ReadOnly)) {
        QString str_query = file.readAll();
        file.close();
        text->clear();
        text->setPlainText(str_query);
        emit ProcessQuery();
    }
    else {
        (new QErrorMessage(this))->showMessage("File does not exist");
        return;
    }
}

void MainWindow::slotCustomMenuRequested(QPoint pos)
{
    auto index = tree_view->indexAt(pos);
    if (!index.parent().isValid() && index.isValid()) {
        QMenu* menu = new QMenu(this);
        QAction *make_Big = new QAction("Make active",this);
        QAction* close = new QAction("Close", this);
        connect(close, SIGNAL(triggered()), this, SLOT(closeXMLTreeView()));
        connect(make_Big, SIGNAL(triggered()), this, SLOT(MakeBig()));
        menu->addAction(close);
        menu->addAction(make_Big);
        menu->popup(tree_view->viewport()->mapToGlobal(pos));
    }
}

void MainWindow::MakeBig()
{
    if(selected_indx!=nullptr && a == 0){
        a++;
    }
    else {
        tree_view->model()->setData(*selected_indx, data(*selected_indx, 0), Qt::FontRole);
    }
    auto index=tree_view->currentIndex();
    while (index.parent().isValid()){
        index=index.parent();
    }
    selected_indx=new QModelIndex(index);
    tree_view->model()->setData(*selected_indx,data(*selected_indx,Qt::FontRole),Qt::FontRole);
    tree_view->setCurrentIndex(*selected_indx);
}

QVariant MainWindow::data(const QModelIndex &index,int role)
{
    if (role==Qt::FontRole && index.column()==0)
    {
        QFont font;
        font.setBold(true);
        return font;
    }
    else{
        QFont font;
        font.setBold(false);
        return font;
    }
}

void MainWindow::closeXMLTreeView()
{
    auto idx = tree_view->currentIndex();
    if (!idx.parent().isValid() && idx.isValid()) {
        tree_view->model()->removeRow(idx.row(), idx.parent());
    }
}
