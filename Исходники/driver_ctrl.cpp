bool analysis::start_service()
{
	if(!manager)
		manager = OpenSCManager(NULL, NULL, SC_MANAGER_ALL_ACCESS);

	if(!manager)
		return false;
	
	if(!service)
		service = OpenServiceA( manager, "hookrevealer",  SERVICE_ALL_ACCESS);
	if (!service)
		return false;

	if(!StartServiceA(service, 0, NULL))
		return false;

	return true;
}