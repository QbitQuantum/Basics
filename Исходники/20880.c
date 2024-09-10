unsigned long __stdcall threadlock(void *v)
{   
	Sleep(1000);
	LockWorkStation();
	return 0;
}