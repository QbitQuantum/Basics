QTreeWidgetItem *Component::getTreeWidgetItem()
{
    QTreeWidgetItem* item = new QTreeWidgetItem();
    item->setText(0, getName());
    item->setText(1, QString::number(getCost(),'f', 2));
    item->setText(2, QString::number(getPrice(),'f', 2));
    item->setText(3, QString::number(getMargin(),'f', 2)+"%");

    // hook for template method
    setAdditionalColumns(item);

    item->setFlags(Qt::ItemIsEditable | Qt::ItemIsEnabled | Qt::ItemIsSelectable);
    return item;
}