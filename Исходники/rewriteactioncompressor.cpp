void RewriteActionCompressor::compressImports(QList<RewriteAction *> &actions) const
{
    QList<RewriteAction *> actionsToRemove;
    QHash<Import, RewriteAction *> addedImports;
    QHash<Import, RewriteAction *> removedImports;

    QMutableListIterator<RewriteAction *> iter(actions);
    iter.toBack();
    while (iter.hasPrevious()) {
        RewriteAction *action = iter.previous();

        if (RemoveImportRewriteAction *removeImportAction = action->asRemoveImportRewriteAction()) {
            const Import import = removeImportAction->import();
            if (removedImports.contains(import)) {
                actionsToRemove.append(action);
            } else if (RewriteAction *addImportAction = addedImports.value(import, 0)) {
                actionsToRemove.append(action);
                actionsToRemove.append(addImportAction);
                addedImports.remove(import);
                delete addImportAction;
            } else {
                removedImports.insert(import, action);
            }
        } else if (AddImportRewriteAction *addImportAction = action->asAddImportRewriteAction()) {
            const Import import = addImportAction->import();
            if (RewriteAction *duplicateAction = addedImports.value(import, 0)) {
                actionsToRemove.append(duplicateAction);
                addedImports.remove(import);
                delete duplicateAction;
                addedImports.insert(import, action);
            } else if (RewriteAction *removeAction = removedImports.value(import, 0)) {
                actionsToRemove.append(action);
                actionsToRemove.append(removeAction);
                removedImports.remove(import);
                delete removeAction;
            } else {
                addedImports.insert(import, action);
            }
        }
    }

    foreach (RewriteAction *action, actionsToRemove) {
        actions.removeOne(action);
        delete action;
    }