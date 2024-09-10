bool WinProcessImpl::Read(wxString& buff)
{
    DWORD le1(-1);
    DWORD le2(-1);
    buff.Clear();
    
    if( !DoReadFromPipe(hChildStderrRdDup, buff) ) {
        le2 = GetLastError();
    }

    if( !DoReadFromPipe(hChildStdoutRdDup, buff) ) {
        le1 = GetLastError();
    }

    
    if( le1 == ERROR_NO_DATA && le2 == ERROR_NO_DATA) {
        if ( IsAlive() ) {
            wxThread::Sleep(15);
            return true;
        }
    }

    bool success = !buff.IsEmpty();
    if(!success) {
        DWORD dwExitCode;
        if (GetExitCodeProcess(piProcInfo.hProcess, &dwExitCode)) {
            SetProcessExitCode(GetPid(), (int)dwExitCode);
        }
    }
    return success;
}