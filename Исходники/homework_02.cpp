void BadParameters()
{
	wprintf_s(L"Program have to run with one of these pamateres: \n");
	wprintf_s(L" -l list of current process with name and ID \n");
	wprintf_s(L" -d details about own process \n");
	wprintf_s(L" -k application creates child process and terminate it");
}