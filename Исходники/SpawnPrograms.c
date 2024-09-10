//This is the function we call in the child process for 'SpawnCommand'
int BASIC_FUNC_EXEC_COMMAND(void *Command, int Flags)
{
    int result;
    char *Token=NULL, *FinalCommand=NULL, *ExecPath=NULL;
    char **argv;
    const char *ptr;
    int i;

    if (Flags & SPAWN_TRUST_COMMAND) FinalCommand=CopyStr(FinalCommand, (char *) Command);
    else FinalCommand=MakeShellSafeString(FinalCommand, (char *) Command, 0);

    StripTrailingWhitespace(FinalCommand);
    if (Flags & SPAWN_NOSHELL)
    {
        argv=(char **) calloc(101,sizeof(char *));
        ptr=FinalCommand;
        ptr=GetToken(FinalCommand,"\\S",&Token,GETTOKEN_QUOTES);
        ExecPath=FindFileInPath(ExecPath,Token,getenv("PATH"));
        i=0;

        if (! (Flags & SPAWN_ARG0))
        {
            argv[0]=CopyStr(argv[0],ExecPath);
            i=1;
        }

        for (; i < 100; i++)
        {
            ptr=GetToken(ptr,"\\S",&Token,GETTOKEN_QUOTES);
            if (! ptr) break;
            argv[i]=CopyStr(argv[i],Token);
        }

        execv(ExecPath,argv);
    }
    else result=execl("/bin/sh","/bin/sh","-c",(char *) Command,NULL);

    RaiseError(ERRFLAG_ERRNO, "Spawn", "Failed to execute '%s'",Command);
//We'll never get to here unless something fails!
    DestroyString(FinalCommand);
    DestroyString(ExecPath);
    DestroyString(Token);

    return(result);
}