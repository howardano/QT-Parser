#ifndef XMLPARSER_H
#define XMLPARSER_H
#include <QMainWindow>
#include <QXmlDefaultHandler>
#include <QTreeWidget>
#include <QTreeWidgetItem>
#include <QDebug>


class xmlparser : public QXmlDefaultHandler
{
public:
    xmlparser(QTreeWidget*, const QString&);

    bool startElement(const QString&, const QString&, const QString&, const QXmlAttributes& attrs) override;

    bool characters(const QString& str) override;

    bool endElement(const QString&, const QString&, const QString& str) override;

    bool fatalError(const QXmlParseException& exception) override;

private:
    QTreeWidget* tree;
    QTreeWidgetItem* tree_item;
    QString title;
    QString text;

};

#endif // XMLPARSER_H
