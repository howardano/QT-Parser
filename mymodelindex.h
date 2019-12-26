#ifndef MYMODELINDEX_H
#define MYMODELINDEX_H
#include <QTreeView>

class Organizations : public QTreeView
{
public:
    Organizations();

private:
        QMenu *menu_cost;


public slots:
    void treeCustomMenu(const QPoint & pos);
};

#endif // MYMODELINDEX_H
