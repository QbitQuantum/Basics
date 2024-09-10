void ActionEditor::slotCurrentItemChanged(QAction *action)
{
    QDesignerFormWindowInterface *fw = formWindow();
    if (!fw)
        return;

    const bool hasCurrentAction = action != 0;
    m_actionEdit->setEnabled(hasCurrentAction);

    if (!action) {
        fw->clearSelection();
        return;
    }

    QDesignerObjectInspector *oi = qobject_cast<QDesignerObjectInspector *>(core()->objectInspector());

    if (action->associatedWidgets().empty()) {
        // Special case: action not in object tree. Deselect all and set in property editor
        fw->clearSelection(false);
        if (oi)
            oi->clearSelection();
        core()->propertyEditor()->setObject(action);
    } else {
        if (oi)
            oi->selectObject(action);
    }
}