Core::NavigationView FolderNavigationWidgetFactory::createWidget()
{
    Core::NavigationView n;
    FolderNavigationWidget *fnw = new FolderNavigationWidget;
    n.widget = fnw;
    QToolButton *filter = new QToolButton;
    filter->setIcon(QIcon(QLatin1String(Core::Constants::ICON_FILTER)));
    filter->setToolTip(tr("Filter Files"));
    filter->setPopupMode(QToolButton::InstantPopup);
    filter->setProperty("noArrow", true);
    QMenu *filterMenu = new QMenu(filter);
    filterMenu->addAction(fnw->m_filterHiddenFilesAction);
    filter->setMenu(filterMenu);
    n.dockToolBarWidgets << filter << fnw->m_toggleSync;
    return n;
}