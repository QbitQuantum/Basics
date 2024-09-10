_bstr_t CREBUS::getBuildPriority(_bstr_t project_id)
{
	ProjectTypeLib::Automation2Ptr project = 
		rebus.getProject(atol((char *) project_id));
	
	_bstr_t process_id = project->Getprocess_id();

	HANDLE hProcess = OpenProcess(PROCESS_QUERY_INFORMATION, FALSE, atol(process_id));
	if(hProcess) 
	{
		DWORD dwPriorityClass = GetPriorityClass(hProcess);
		CloseHandle(hProcess);

		switch(dwPriorityClass)
		{
		case ABOVE_NORMAL_PRIORITY_CLASS:
			return "High";
		case NORMAL_PRIORITY_CLASS:
			return "Normal";
		case BELOW_NORMAL_PRIORITY_CLASS:
			return "Low";
		case IDLE_PRIORITY_CLASS:
			return "Idle";
		}
	}
	return "";
}