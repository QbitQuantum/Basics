void TaskView::removeDialog(void)
{
    if (ActiveCtrl) {
        taskPanel->removeWidget(ActiveCtrl);
        delete ActiveCtrl;
        ActiveCtrl = 0;
    }

    TaskDialog* remove = NULL;
    if (ActiveDialog) {
        // See 'accept' and 'reject'
        if (ActiveDialog->property("taskview_accept_or_reject").isNull()) {
            const std::vector<QWidget*> &cont = ActiveDialog->getDialogContent();
            for(std::vector<QWidget*>::const_iterator it=cont.begin();it!=cont.end();++it){
                taskPanel->removeWidget(*it);
            }
            remove = ActiveDialog;
            ActiveDialog = 0;
        }
        else {
            ActiveDialog->setProperty("taskview_remove_dialog", true);
        }
    }

    taskPanel->removeStretch();

    // put the watcher back in control
    addTaskWatcher();
    
    if (remove) {
        remove->emitDestructionSignal();
        delete remove;
    }
}