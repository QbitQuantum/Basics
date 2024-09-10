CBoardItem *CBoardItemsFactory::create(QString className, double zoomFactor, CPoint middle)
{
    int classid = QMetaType::type(className.toLocal8Bit());
    CBoardItem *newItem;
    if (classid == QMetaType::UnknownType) {
        QMessageBox::critical(nullptr, "Unknown class", "Error - cannot create object of unknown class " + className);
        return nullptr;
    }
    newItem = (CBoardItem*)QMetaType::create(classid);
    newItem->id = ++counter;
    newItem->setContainer(board);
    newItem->setParent(itemsContainer);
    newItem->scale(zoomFactor);
    CPoint pos = middle - itemsContainer->pos() - newItem->size() / 2;
    newItem->setStandardPos(pos);
    newItem->rename();
    newItem->show();
    return newItem;
}