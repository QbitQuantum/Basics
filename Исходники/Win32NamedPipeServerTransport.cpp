 void Win32NamedPipeImpersonator::impersonate()
 {
     HANDLE hPipe = mPipeSession.mSocketPtr->native();
     BOOL ok = ImpersonateNamedPipeClient(hPipe);
     DWORD dwErr = GetLastError();
     RCF_VERIFY(ok, RCF::Exception(_RcfError_Pipe(), dwErr));
 }