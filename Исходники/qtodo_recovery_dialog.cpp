void QTodoRecoveryDialog::recover()
{
    QFileInfo file_info;
    QDir dir;

    QListViewItem* item = list->firstChild();
    for(; item; item = item->nextSibling())
    {
        if(item->text(2).isEmpty())
        {   //we can't recover from a backup file, so we at least (try to) restore the todo-list-name :(
            file_info.setFile(item->text(0));
            dynamic_cast<QTodoRecoveryListViewItem*>(item)->list_view_item->listWidget()->getHeader()->setName(file_info.fileName());
            dynamic_cast<QTodoRecoveryListViewItem*>(item)->list_view_item->update();
            dynamic_cast<QTodoRecoveryListViewItem*>(item)->list_view_item->listWidget()->setModified();
            dynamic_cast<QTodoRecoveryListViewItem*>(item)->list_view_item->save();
        }
        else
        {
            dir.rename(item->text(0)+'~',item->text(0),true);
            dynamic_cast<QTodoRecoveryListViewItem*>(item)->list_view_item->load();
        }
    }
}