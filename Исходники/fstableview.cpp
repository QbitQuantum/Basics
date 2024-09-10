void FSTableView::contextMenuEvent(QContextMenuEvent * event)
{
    QModelIndex index = indexAt(event->pos());
    QMenu * menu = 0;
    if (index.isValid())
    {
        if (selectionModel()->selectedRows().count() > 1)
            menu = createSelectionMenu();
        else
            menu = createItemMenu();

    }
    else
        menu = createMenu();

    menu->move(event->globalPos());
    menu->exec();
    delete menu;

}