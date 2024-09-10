wchar_t *sendpraatW (void *display, const wchar_t *programName, long timeOut, const wchar_t *text) {
    wchar_t nativeProgramName [100];
#if xwin
    char *home, pidFileName [256], messageFileName [256];
    FILE *pidFile;
    long pid, wid = 0;
#elif win
    wchar_t homeDirectory [256], messageFileName [256], windowName [256];
    HWND window;
    (void) display;
    (void) timeOut;
#elif mac
    AEDesc programDescriptor;
    AppleEvent event, reply;
    OSErr err;
    UInt32 signature;
    (void) display;
#endif

    /*
     * Clean up from an earlier call.
     */
    errorMessageW [0] = '\0';

    /*
     * Handle case differences.
     */
    wcscpy (nativeProgramName, programName);
#if xwin
    nativeProgramName [0] = tolower (nativeProgramName [0]);
#else
    nativeProgramName[0] = toupper (nativeProgramName [0]);
#endif

    /*
     * If the text is going to be sent in a file, create its name.
     * The file is going to be written into the preferences directory of the receiving program.
     * On X Window, the name will be something like /home/jane/.praat-dir/message.
     * On Windows, the name will be something like C:\Documents and Settings\Jane\Praat\Message.txt,
     * or C:\Windows\Praat\Message.txt on older systems.
     * On Macintosh, the text is NOT going to be sent in a file.
     */
#if xwin
    if ((home = getenv ("HOME")) == NULL) {
        swprintf (errorMessageW, 1000, L"HOME environment variable not set.");
        return errorMessageW;
    }
    sprintf (messageFileName, "%s/.%ls-dir/message", home, programName);
#elif win
    if (GetEnvironmentVariableW (L"USERPROFILE", homeDirectory, 255)) {
        ;   /* Ready. */
    } else if (GetEnvironmentVariableW (L"HOMEDRIVE", homeDirectory, 255)) {
        GetEnvironmentVariableW (L"HOMEPATH", homeDirectory + wcslen (homeDirectory), 255);
    } else {
        GetWindowsDirectoryW (homeDirectory, 255);
    }
    swprintf (messageFileName, 256, L"%ls\\%ls\\Message.txt", homeDirectory, programName);
#endif

    /*
     * Write the message file (Unix and Windows only).
     */
#if xwin
    FILE *messageFile;
    if ((messageFile = fopen (messageFileName, "w")) == NULL) {
        swprintf (errorMessageW, 1000, L"Cannot create message file \"%s\" "
                  L"(no privilege to write to directory, or disk full).\n", messageFileName);
        return errorMessageW;
    }
    if (timeOut)
        fwprintf (messageFile, L"#%ld\n", getpid ());   /* Write own process ID for callback. */
    fwprintf (messageFile, L"\ufeff%ls", text);
    fclose (messageFile);
#elif win
    {   /* 20090401 [email protected] added braces to please visual studio */
        FILE *messageFile;
        if ((messageFile = _wfopen (messageFileName, L"w")) == NULL) {
            swprintf (errorMessageW, 1000, L"Cannot create message file \"%ls\" "
                      L"(no privilege to write to directory, or disk full).\n", messageFileName);
            return errorMessageW;
        }
        fwprintf (messageFile, L"\ufeff%ls", text);
        fclose (messageFile);
    } /* 20090401 [email protected] added braces to please visual studio */
#endif

    /*
     * Where shall we send the message?
     */
#if xwin
    /*
     * Get the process ID and the window ID of a running Praat-shell program.
     */
    sprintf (pidFileName, "%s/.%ls-dir/pid", home, programName);
    if ((pidFile = fopen (pidFileName, "r")) == NULL) {
        swprintf (errorMessageW, 1000, L"Program %ls not running (or a version older than 3.6).", programName);
        return errorMessageW;
    }
    if (fscanf (pidFile, "%ld%ld", & pid, & wid) < 1) {
        fclose (pidFile);
        swprintf (errorMessageW, 1000, L"Program %ls not running, or disk has been full.", programName);
        return errorMessageW;
    }
    fclose (pidFile);
#elif win
    /*
     * Get the window handle of the "Objects" window of a running Praat-shell program.
     */
    swprintf (windowName, 256, L"PraatShell1 %ls", programName);
    window = FindWindowW (windowName, NULL);
    if (! window) {
        swprintf (errorMessageW, 1000, L"Program %ls not running (or an old version).", programName);
        return errorMessageW;
    }
#elif mac
    /*
     * Convert the program name to a Macintosh signature.
     * I know of no system routine for this, so I'll just translate the two most common names:
     */
    if (! wcscmp (programName, L"praat") || ! wcscmp (programName, L"Praat") || ! wcscmp (programName, L"PRAAT"))
        signature = 'PpgB';
    else if (! wcscmp (programName, L"als") || ! wcscmp (programName, L"Als") || ! wcscmp (programName, L"ALS"))
        signature = 'CclA';
    else
        signature = 0;
    AECreateDesc (typeApplSignature, & signature, 4, & programDescriptor);
#endif

    /*
     * Send the message.
     */
#if xwin
    /*
     * Be ready to receive notification of completion.
     */
    if (timeOut)
        signal (SIGUSR2, handleCompletion);
    /*
     * Notify running program.
     */
    if (wid != 0) {   /* Praat shell version October 21, 1998 or later? Send event to window. */
        /*
         * Notify main window.
         */
        XEvent event;
        int displaySupplied = display != NULL;
        if (! displaySupplied) {
            display = XOpenDisplay (NULL);
            if (display == NULL) {
                swprintf (errorMessageW, 1000, L"Cannot open display %s.", XDisplayName (NULL));
                return errorMessageW;
            }
        }
        event. type = ClientMessage;
        event. xclient. serial = 0;
        event. xclient. send_event = True;
        event. xclient. display = display;
        event. xclient. window = (Window) wid;
        event. xclient. message_type = XInternAtom (display, "SENDPRAAT", False);
        event. xclient. format = 8;   /* No byte swaps. */
        strcpy (& event. xclient.data.b [0], "SENDPRAAT");
        if(! XSendEvent (display, (Window) wid, True, KeyPressMask, & event)) {
            if (! displaySupplied) XCloseDisplay (display);
            swprintf (errorMessageW, 1000, L"Cannot send message to %ls (window %ld). "
                      "The program %ls may have been started by a different user, "
                      "or may have crashed.", programName, wid, programName);
            return errorMessageW;
        }
        if (! displaySupplied) XCloseDisplay (display);
    } else {
        /*
         * Use interrupt mechanism.
         */
        if (kill (pid, SIGUSR1)) {
            swprintf (errorMessageW, 1000, L"Cannot send message to %ls (process %ld). "
                      "The program %ls may have been started by a different user, "
                      "or may have crashed.", programName, pid, programName);
            return errorMessageW;
        }
    }
    /*
     * Wait for the running program to notify us of completion,
     * but do not wait for more than 'timeOut' seconds.
     */
    if (timeOut) {
        signal (SIGALRM, handleTimeOut);
        alarm (timeOut);
        theTimeOut = timeOut;   /* Hand an argument to handleTimeOut () in a static variable. */
        errorMessageW [0] = '\0';
        pause ();
        if (errorMessageW [0] != '\0') return errorMessageW;
    }
#elif win
    /*
     * Notify the running program by sending a WM_USER message to its main window.
     */
    if (SendMessage (window, WM_USER, 0, 0)) {
        swprintf (errorMessageW, 1000, L"Program %ls returns error.", programName);   /* BUG? */
        return errorMessageW;
    }
#elif mac
    /*
     * Notify the running program by sending it an Apple event of the magic class 758934755.
     */
    AECreateAppleEvent (758934755, 0, & programDescriptor, kAutoGenerateReturnID, 1, & event);
    AEPutParamPtr (& event, 1, typeUnicodeText, text, wcslen (text) + 1);
#ifdef __MACH__
    err = AESendMessage (& event, & reply,
                         ( timeOut == 0 ? kAENoReply : kAEWaitReply ) | kAECanInteract | kAECanSwitchLayer,
                         timeOut == 0 ? kNoTimeOut : 60 * timeOut);
#else
    err = AESend (& event, & reply,
                  ( timeOut == 0 ? kAENoReply : kAEWaitReply ) | kAECanInteract | kAECanSwitchLayer,
                  kAENormalPriority, timeOut == 0 ? kNoTimeOut : 60 * timeOut, NULL, NULL);
#endif
    if (err != noErr) {
        if (err == procNotFound || err == connectionInvalid)
            swprintf (errorMessageW, 1000, L"Could not send message to program \"%ls\".\n"
                      L"The program is probably not running (or an old version).", programName);
        else if (err == errAETimeout)
            swprintf (errorMessageW, 1000, L"Message to program \"%ls\" timed out "
                      L"after %ld seconds, before completion.", programName, timeOut);
        else
            swprintf (errorMessageW, 1000, L"Unexpected sendpraat error %d.\nNotify the author.", err);
    }
    AEDisposeDesc (& programDescriptor);
    AEDisposeDesc (& event);
    AEDisposeDesc (& reply);
#endif

    /*
     * Notify the caller of success (NULL pointer) or failure (string with an error message).
     */
    return errorMessageW [0] == '\0' ? NULL : errorMessageW;
}