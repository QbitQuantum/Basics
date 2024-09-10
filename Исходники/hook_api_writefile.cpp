int main(int argc,char *argv[]) 
{
	DWORD dwPID;
	
	if(argc!=2)
	{
		printf("Usage:%s pid\n",argv[0]);
		return 1;
	}
	
	//Attach Process
	dwPID=atoi(argv[1]);
	if(!DebugActiveProcess(dwPID))
	{
		printf("DebugActiveProcess(%d) failed!\n","Error code =%d\n",dwPID,GetLastError());
		return 1;
	}
	
	//debug loop
	DebugLoop();
	return 0;
}