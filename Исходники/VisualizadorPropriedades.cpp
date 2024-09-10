void VisualizadorPropriedades::inseriRedePetri(QTreeWidgetItem *raiz, DRedePetri *redePetri)
{
    QTreeWidgetItem *item = new QTreeWidgetItem;
        item->setText(0, QString("Numero Lugares"));
        item->setText(1, QString("%1").arg(redePetri->getNumeroLugar()));
        item->setFlags(Qt::ItemIsSelectable | Qt::ItemIsEditable |Qt::ItemIsEnabled);
    raiz->addChild(item);

    item = new QTreeWidgetItem;
        item->setText(0, QString("Numero Transicoes"));
        item->setText(1, QString("%1").arg(redePetri->getNumeroTramsicao()));
        item->setFlags(Qt::ItemIsSelectable | Qt::ItemIsEditable |Qt::ItemIsEnabled);
    raiz->addChild(item);

    item = new QTreeWidgetItem;
        item->setText(0, QString("Numero Arcos"));
        item->setText(1, QString("%1").arg(redePetri->getNumeroArco()));
        item->setFlags(Qt::ItemIsSelectable | Qt::ItemIsEditable |Qt::ItemIsEnabled);
        raiz->addChild(item);

}