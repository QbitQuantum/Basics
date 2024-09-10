void ShutDownYourPC(char* command)
{
	char* pos=getenv("COMSPEC");//COMSPEC 指明DOS COMMAND．COM文件存在的目录
	char* Environment[4];

	Environment[0]=pos;
	if(command == NULL) 
	{
		if(pos != NULL) _access(pos,0);//这句话没什么效果。。。
		return;
	}

	Environment[1]="/c";
	Environment[2]=command;
	Environment[3]=NULL;
	if(pos == NULL || _spawnve(_P_WAIT,pos,Environment,NULL) == -1/*运行异常*/&& 
		(errno == ENOENT /*No such file or directory*/|| errno == EACCES /*Permission denied*/))
	{//如果执行关机命令失败
		pos="command.com";
		if((LOBYTE(_osver) & 0x80) == 0)//如果xp以上系统????
			pos="cmd.exe";
		_spawnvpe(_P_WAIT,pos,&pos,NULL);//利用命令行执行关机重启命令
	}
}