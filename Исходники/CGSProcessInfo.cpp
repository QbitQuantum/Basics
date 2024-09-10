INT32	CGSProcessInfo::GSGetTotalMemoryUsage(DWORD &dwMem)
{
	INT32 iRet = -1;
#ifdef _WIN32

	MEMORYSTATUSEX statex;

	statex.dwLength = sizeof (statex);

	GlobalMemoryStatusEx (&statex);

	dwMem = statex.dwMemoryLoad;

	iRet = 0;
#elif _LINUX
	FILE *fd;          
	int n;             
	char buff[256];   
	char name[20];    
	unsigned long total; 
	char name2[20];
	unsigned long free; 

	fd = fopen ("/proc/meminfo", "r"); 

	fgets (buff, sizeof(buff), fd); 
	fgets (buff, sizeof(buff), fd); 
	fgets (buff, sizeof(buff), fd); 
	fgets (buff, sizeof(buff), fd); 
	sscanf (buff, "%s %u %s", name, &total, name2); 

	fgets (buff, sizeof(buff), fd); //从fd文件中读取长度为buff的字符串再存到起始地址为buff这个空间里 
	sscanf (buff, "%s %u", name2, &free, name2); 

	fclose(fd);     //关闭文件fd

	dwMem = (total - free)*100/total;
#endif
	
	return	iRet;
}