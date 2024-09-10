/* This function is not used because it isn't realiable in
   some new environments */
int debug_checkremotedebuggerpresent() {
    BOOL isdebug = FALSE;
    CheckRemoteDebuggerPresent(GetCurrentProcess(), &isdebug);
    if (isdebug) {
        return 0;
    }
    else {
        return 1;
    }
}