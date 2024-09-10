void QG_GraphicView::setMenu(const QString& activator, QMenu* menu)
{
    destroyMenu(activator);
    menus[activator] = menu;
}