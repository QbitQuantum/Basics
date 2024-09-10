void QDesignerMenuBar::updateCurrentAction(bool selectAction)
{
    update();

    if (!selectAction)
        return;

    QAction *action = currentAction();
    if (!action || action == m_addMenu)
        return;

    QMenu *menu = action->menu();
    if (!menu)
        return;

    QDesignerObjectInspector *oi = 0;
    if (QDesignerFormWindowInterface *fw = formWindow())
        oi = qobject_cast<QDesignerObjectInspector *>(fw->core()->objectInspector());

    if (!oi)
        return;

    oi->clearSelection();
    oi->selectObject(menu);
}