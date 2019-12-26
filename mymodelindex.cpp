#include "mymodelindex.h"
#include <QMenu>

Organizations::Organizations()
{

    menu_cost = new QMenu(this);
    QAction *newact = new QAction("Закрыть");

    menu_cost->addAction(newact);

}

void Organizations::treeCustomMenu(const QPoint & pos){
    QModelIndex ind = indexAt(pos);


    if(ind.parent() == QModelIndex()){
        menu_cost->exec();

    } else {

        return;
    }
}
