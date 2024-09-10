void StopGemfireServer() 
{
    Log("Entering StopGemfireServer\n");

    std::string command =   gServiceLauncherCommand + " stop " + gWorkingDirectory;
    Log("StopGemfireServer Command = %s\n" ,command.c_str());

    FILE   *pPipe;
    char psBuffer[1024];
    if( (pPipe = _popen( command.c_str(), "rt" )) != NULL ) {                    
        while (fgets(psBuffer, 1024, pPipe));
        Log( "[StartGemfireServer] ==> %s\n", psBuffer);
        feof(pPipe);
    }
    Log("Exiting StopGemfireServer\n");
}