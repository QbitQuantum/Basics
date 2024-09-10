void TaskWindow::NotifyDone(Task * task)
{
	if(closeOnDone)
		Exit();
	done = true;
}