void
LaunchService::Launch(const stringVector &origLaunchArgs, bool doBridge, 
    SocketConnection **conn)
{
    const char *mName = "LaunchService::LaunchProcess: ";
    debug1 << mName << "start" << endl;

    stringVector launchArgs(origLaunchArgs);
    bool readOutput = conn != NULL;
    if(readOutput)
        *conn = NULL;

    if(launchArgs.empty())
        return;

    // Set up a socket bridge if we need one.
    if(doBridge)
        SetupGatewaySocketBridgeIfNeeded(launchArgs);

    std::string remoteProgram(launchArgs[0]);
    debug1 << mName << "LaunchRPC command = " << remoteProgram.c_str() << ", args=(";

    // Make a command line array for the exec functions.
    char **args = new char *[launchArgs.size() + 1];
    memset(args, 0, (launchArgs.size() + 1) * sizeof(char *));
    for(size_t i = 0; i < launchArgs.size(); ++i)
    {
        args[i] = new char[launchArgs[i].size() + 1];
        strcpy(args[i], launchArgs[i].c_str());
        if(i > 0) {
            debug1 << launchArgs[i].c_str() << " ";
        }
    }
    debug1 << ")" << endl;

    // We have command line arguments for a command to launch.

    int remoteProgramPid = 0;
#if defined(_WIN32)
    // Do it the WIN32 way where we use the _spawnvp system call.
    remoteProgramPid = _spawnvp(_P_NOWAIT, remoteProgram.c_str(), args);
#else
    // Watch for a process who died
    childDied[remoteProgramPid] = false;
    signal(SIGCHLD, DeadChildHandler);

#ifdef CAPTURE_CHILD_OUTPUT
    // Create a pipe.
    int f_des[2];
    if(pipe(f_des) == -1)
        readOutput = false;
#endif

    switch (remoteProgramPid = fork())
    {
    case -1:
        // Could not fork.
        exit(-1); // HOOKS_IGNORE
        break;
    case 0:
        // Close stdin and any other file descriptors.
        fclose(stdin);
#ifdef CAPTURE_CHILD_OUTPUT
        // Send the process' stdout/stderr to our pipe.
        if(readOutput)
        {
            dup2(f_des[1], fileno(stdout));
            dup2(f_des[1], fileno(stderr));
            close(f_des[0]);
            close(f_des[1]);
        }
#endif
        for (int k = 3 ; k < 32 ; ++k)
        {
            close(k);
        }
        // Execute the process on the local machine.
        remoteProgram = FileFunctions::ExpandPath(remoteProgram);
        execvp(remoteProgram.c_str(), args);
        exit(-1); // HOOKS_IGNORE
        break;   // OCD
    default:
#ifdef CAPTURE_CHILD_OUTPUT
        if(readOutput)
            close(f_des[1]);
#endif
        break;
    }

    // Stop watching for dead children
    signal(SIGCHLD, SIG_DFL);

    // If we had a dead child, try and connect back to the client that
    // wanted to connect to the dead child.
    if(childDied[remoteProgramPid])
    {
        // Create a temp array of pointers to the strings that we
        // created and pass the temp array to the TerminateConnectionRequest
        // method because it creates a ParentProcess object that will
        // rearrange the pointers in the array.
        char **args2 = new char *[launchArgs.size() + 1];
        for(size_t i = 0; i < launchArgs.size(); ++i)
            args2[i] = args[i];

        // Tell the client that we could not connect.
        TerminateConnectionRequest(launchArgs.size(), args2);

        delete [] args2;
    }
#ifdef CAPTURE_CHILD_OUTPUT
    else if(readOutput)
    {
        // Add the child's output pipe to the list of descriptors that
        // we will check. We add the pipe file descriptor as a 
        // SocketConnection object.
        *conn = new SocketConnection(f_des[0]);
    }
#endif
#endif

    // Free the command line storage.
    for(size_t i = 0; i < launchArgs.size(); ++i)
        delete [] args[i];
    delete [] args;
    debug1 << mName << "end" << endl;
}