pid_t HandleWebsocketExecRequest(STREAM *ClientCon, char *Data)
{
char *Tempstr=NULL, *Name=NULL, *Value=NULL;
char *ScriptPath=NULL;
int result, i;
HTTPSession *Response;

	//We will never read from this stream again. Any further data will be read
	//by the process we spawn off
	ClientCon->State |= SS_EMBARGOED;
	Response=ParseSessionInfo(Data);
	CleanStr(Response->Path);
	CleanStr(Response->SearchPath);
	CleanStr(Response->StartDir);
	ScriptPath=FindFileInPath(ScriptPath, Response->Path, Response->SearchPath);
	LogToFile(Settings.LogPath,"Script: Found=[%s] SearchPath=[%s] ScriptName=[%s] Arguments=[%s]", ScriptPath, Response->SearchPath, Response->Path, Response->Arguments);

	if (access(ScriptPath,F_OK) !=0)
	{
			LogToFile(Settings.LogPath,"No such script: %s in path %s = %s",Response->Path, Response->SearchPath, ScriptPath);
	}
	else if (
					(access(ScriptPath,X_OK) !=0) || 
					(! CheckScriptIntegrity(ScriptPath))
			)
	{
			LogToFile(Settings.LogPath,"Cannot execute script: %s", ScriptPath);
	}
	else
	{
		STREAMFlush(ClientCon);
		result=fork();
		if (result==0)
		{
			//do this so that when we exec the script, anything output goes to the client
			close(0);
			dup(ClientCon->in_fd);
			close(1);
			dup(ClientCon->out_fd);

      if (! SwitchGroup(Response->Group))
			{
        LogToFile(Settings.LogPath,"WARN: Failed to switch to group '%s' to execute script: %s using handler '%s'", Response->RealUser, ScriptPath, Tempstr);
			}

      //Switch user. ALAYA WILL NOT RUN SCRIPTS AS ROOT!
      if (! SwitchUser(Response->RealUser))
      {
        LogToFile(Settings.LogPath,"ERROR: Failed to switch to user '%s' to execute script: %s using handler '%s'", Response->RealUser, ScriptPath, Tempstr);
				LogFileFlushAll(TRUE);
        _exit(0);
      }

			if (geteuid()==0)
			{
				LogToFile(Settings.LogPath, "Failed to switch user to '%s' for running a .cgi program. Will not run programs as 'root'. Set 'DefaultUser' in config file or command line.", Response->RealUser);
			}
			else
			{
				SetupEnvironment(Response, ScriptPath);
				Tempstr=FindScriptHandlerForScript(Tempstr,ScriptPath);
				if (Tempstr) LogToFile(Settings.LogPath,"Execute script: %s using handler '%s'",ScriptPath,Tempstr);
				else LogToFile(Settings.LogPath,"Execute script: %s QUERY_STRING= '%s'",ScriptPath,getenv("QUERY_STRING"));

				//Only do this late! Otherwise logging won't work.
				for (i=3; i < 1000; i++) close(i);

				if (StrLen(Tempstr)) execl(Tempstr, Tempstr, ScriptPath,NULL);
				else execl(ScriptPath,ScriptPath,NULL);

				//Logging won't work after we've closed all the file descriptors!
				LogToFile(Settings.LogPath,"Cannot execute script: %s",ScriptPath);
		}
		LogFileFlushAll(TRUE);
		_exit(0);
	}
	else
	{

	}
}


HTTPSessionDestroy(Response);
DestroyString(ScriptPath);
DestroyString(Tempstr);
DestroyString(Name);
DestroyString(Value);


//Always return STREAM_CLOSED, so that pipe gets closed regardless of exit status of 
//forked helper process
return(STREAM_CLOSED);
}