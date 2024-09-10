void ThreadedTaskHandler::executeThread(void)
{
	while(!ExitRequested)
	{
		suspendThread();
		
		while(!ExitRequested && !TaskList.empty())
		{
			gprintf("\n\tThreadedTaskHandler::execute() TaskList.front");
			TaskList.front()->Execute();
			TaskList.pop();
		}
	}
}