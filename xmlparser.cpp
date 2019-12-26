#include "xmlparser.h"

xmlparser::xmlparser(QTreeWidget* _tree, const QString& _title)
{
    tree = _tree;
    tree_item = nullptr;
    title = _title;
}

bool xmlparser::startElement(const QString&, const QString&, const QString& tag_name, const QXmlAttributes& attrs)
{
    if (tag_name == "catalog") {
        tree_item = new QTreeWidgetItem(tree);
        tree_item->setText(0, title);
    }
    else if (tag_name == "array") {
        tree_item = new QTreeWidgetItem(tree_item);
        tree_item->setText(0, tag_name);
    }
    else {
        tree_item = new QTreeWidgetItem(tree_item);
    }
    return true;
}

bool xmlparser::characters(const QString &str)
{
    text = str;
    return true;
}

bool xmlparser::endElement(const QString&, const QString&, const QString &str)
{
    if (str != "catalog" && str != "array") {
        if (str == "Name" || str== "FullName")
            tree_item->parent()->setText(0, text);
        tree_item->setText(0, str + ": " + text);
        tree_item = tree_item->parent();
    }
    else
        tree_item = tree_item->parent();
    return true;
}

bool xmlparser::fatalError(const QXmlParseException &exception)
{
    qDebug() << "Line:"      << exception.lineNumber()
             << ", Column:"  << exception.columnNumber()
             << ", Message:" << exception.message();
    return false;
}
