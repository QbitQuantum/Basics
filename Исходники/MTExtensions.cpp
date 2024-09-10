int MT3Interface::processinput(const char *input)
{
	char *param;
	char command[256];

	mtmemzero(command,sizeof(command));
	strncpy(command,input,sizeof(command)-1);
	param = strchr(command,' ');
	if (param){
		*param++ = 0;
	};
	if ((stricmp(command,"open")==0) || (stricmp(command,"load")==0)){
		if (param) loadmodule(param);
		return 1;
	}
	else if ((stricmp(command,"exit")==0) || (stricmp(command,"quit")==0)){
#		ifdef _WIN32
			PostQuitMessage(0);
#		else
			extern bool running;
			running = false;
#		endif
		return 1;
	}
	else{
		return 0;
	};
}