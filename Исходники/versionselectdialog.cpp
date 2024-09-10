void VersionSelectDialog::loadList()
{
	TaskDialog *taskDlg = new TaskDialog(this);
	Task *loadTask = m_vlist->getLoadTask();
	loadTask->setParent(taskDlg);
	taskDlg->exec(loadTask);
}