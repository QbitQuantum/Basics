void ManagerProcess::OnSignal(int signo, siginfo_t& info)
{
    char* sigstr = strsignal(signo);
    WARN_LOG(
            "Received signal(%s:%d) from process:%u", NULL != sigstr?sigstr:"UnknownSignal", signo, info.si_pid);
    if (signo == SIGCHLD)
    {
        while (true)
        {
            int status;
            pid_t child = waitpid(-1, &status, WNOHANG);
            if (0 == child || -1 == child)
            {
                break;
            }
            ServiceProcess* proc = GetServiceProcess(child);
            if (NULL != proc)
            {
                ServiceProcessFactory* factory =
                        proc->GetServiceProcessFactory();
                ServiceIndex idx = proc->GetProcessIndex();
                ServiceType type = proc->GetServiceType();
                factory->DeleteServiceProcess(proc);
                m_ipc_event_handler.BroadcastServiceProcessStoped(type, idx);
                //RemoveServiceProcess(child);
                if (g_proc_running)
                {
                    CreateServiceProcess(factory, idx);
                    LogPid4ProcessesInFile();
                }
                else
                {
                    TryStop();
                }
            }
        }
    }
    else if (signo == SIGPIPE)
    {
        //ignore
    }
    else if (signo == SIGQUIT)
    {
        g_proc_running = false;

        list<ServiceProcess*> proc_list;
        GetServiceProcessList(proc_list, 0);
        list<ServiceProcess*>::iterator it = proc_list.begin();
        while (it != proc_list.end())
        {
            ServiceProcess* proc = *it;
            proc->CloseIPCChannel();
            //proc->GetIPCChannel()->Close();
            kill(proc->GetPID(), SIGQUIT);
            it++;
        }
    }
    else if (signo == SIGUSR1)
    {

    }
    else if (signo == SIGUSR2)
    {

    }
}