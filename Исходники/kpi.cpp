bool processSearch(process &currProcess)
{
    bool result = false;;
    if((currProcess.get_pname() != "") && (currProcess.get_pid() == 0)) //pname set, pid not set, search with pname
    {
#ifdef DEBUG
	print_string("Using Name Search");
#endif
	int pid = 0; //will be set in currprocess, can't be done by this function
	result = processSearch(currProcess.get_pname(), &pid);
	currProcess.set_pid(pid);
    } else {
#ifdef DEBUG
	print_string("Using PID Search");
#endif
	result = processSearch(currProcess.get_pid());
    }
    return result;
}