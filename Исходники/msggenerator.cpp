StringBuffer& MessageGenerator::generateMessage(const char* method, const char* templatemsg, StringBuffer& message)
{
    if(!method || !*method)
        return message;

    if(http_tracelevel >= 1)
        fprintf(m_logfile, "Automatically generating message from schema for method \"%s\"%s", method, LT);
    
    initCfgDefValues(method);

    if (m_isRoxie)
        genRoxieMessage(templatemsg, message);
    else 
        genNonRoxieMessage(method, templatemsg, message);

    if (m_gfile.get())
    {
        Owned<IFile> tf = createIFile(m_gfile.get());
        {
            Owned<IFileIO> tio = tf->open(IFOcreaterw);
            tio->write(0, message.length(), message.str());
        }
    }

    else if(http_tracelevel > 0)
    {
        fprintf(stderr, "Request for method %s has been generated:\n", method);
        if(http_tracelevel >= 5)
            fprintf(stderr, "%s\n", message.str());

        char c = 'n';
        if(!(m_globals && m_globals->getPropBool("useDefault")))
        {
            fprintf(stderr, "Do you want to modify it?[n/y]");
            c = getchar();
        }

        if(c == 'y' || c == 'Y' || m_keepfile)
        {
            StringBuffer tmpfname;
            tmpfname.append(method);
            addFileTimestamp(tmpfname, false);
#ifdef _WIN32
            tmpfname.insert(0, "c:\\Temp\\");
#else
            tmpfname.insert(0, "/tmp/");
#endif
            Owned<IFile> tf = createIFile(tmpfname.str());
            {
                Owned<IFileIO> tio = tf->open(IFOcreaterw);
                tio->write(0, message.length(), message.str());
            }
            
            if(c == 'y' || c == 'Y')
            {
                StringBuffer cmdline;
#ifdef _WIN32
                cmdline.appendf("notepad.exe %s", tmpfname.str());
                STARTUPINFO sinfo;
                PROCESS_INFORMATION pinfo;
                GetStartupInfo(&sinfo);
                CreateProcess(0, (char*)cmdline.str(), 0, 0, false, 0, 0, 0, &sinfo, &pinfo);
                WaitForSingleObject(pinfo.hProcess, INFINITE);
#else
                cmdline.appendf("vi %s", tmpfname.str());
                if (system(cmdline.str()) == -1)
                    throw MakeStringException(-1, "MessageGenerator::generateMessage: could not execute command %s", cmdline.str());
#endif
                message.clear().loadFile(tmpfname.str(), true);
            }

            if(!m_keepfile)
                tf->remove();
            else
                printf("A copy is saved at %s (unless you specified another location)\n", tmpfname.str());
        }
    }

    return message;
}