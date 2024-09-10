void PipedProcessCtrl::KillProcess()
{
    if(m_dead)
        return;
//    if(m_killlevel==0) //some process will complete if we send EOF. TODO: make sending EOF a separate option
//    {
//        m_proc->CloseOutput();
//        m_killlevel=1;
//        return;
//    }
    long pid=GetPid();
#ifdef __WXGTK__
    if(m_killlevel==0)
    {
        m_killlevel=1;
        if(wxProcess::Exists(pid))
            wxProcess::Kill(pid,wxSIGTERM);
        return;
    }
    if(m_killlevel==1)
    {
        if(wxProcess::Exists(pid))
        {
            wxProcess::Kill(pid,wxSIGKILL);
        }
    }
#else
    if(wxProcess::Exists(pid))
    {
        wxProcess::Kill(pid,wxSIGKILL);
    }
#endif //__WXGTK__
}