void DlgCustomToolbarsImp::setActionGroup(QAction* action, const QList<QAction*>& group)
{
    // See also ActionGroup::addTo()
    QList<QWidget*> widgets = action->associatedWidgets();
    for (QList<QWidget*>::iterator it = widgets.begin(); it != widgets.end(); ++it) {
        QToolButton* tb = qobject_cast<QToolButton*>(*it);
        if (tb) {
            QMenu* menu = tb->menu();
            if (!menu) {
                tb->setPopupMode(QToolButton::MenuButtonPopup);
                tb->setObjectName(QString::fromLatin1("qt_toolbutton_menubutton"));
                QMenu* menu = new QMenu(tb);
                menu->addActions(group);
                tb->setMenu(menu);
            }
        }
    }
}