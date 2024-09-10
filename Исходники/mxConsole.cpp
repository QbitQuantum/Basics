void mxConsole::OnProcessTerminate( wxProcessEvent &event ) {
    if (event.GetPid()==the_process_pid) {
        GetProcessOutput(false);
        want_input=false;
        Refresh();
        the_process->Detach();
        the_process=NULL;
        timer_process->Stop();
        parent->OnProcessTerminated();
    }
}