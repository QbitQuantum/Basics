/*
 * TclSetWinError
 *
 *   Sets the interpreter's errorCode variable.
 *
 * Arguments:
 *   interp    - Current interpreter.
 *   errorCode - Windows error code.
 *
 * Returns:
 *   The message that is associated with the error code.
 */
char *
TclSetWinError(
    Tcl_Interp *interp,
    DWORD errorCode
    )
{
    char errorId[12];
    ThreadSpecificData *tsdPtr = TCL_TSD_INIT(&dataKey);

    StringCchPrintfA(errorId, ARRAYSIZE(errorId), "%lu", errorCode);

    if (FormatMessageA(FORMAT_MESSAGE_FROM_SYSTEM,
        NULL,
        errorCode,
        MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),
        tsdPtr->message,
        ARRAYSIZE(tsdPtr->message),
        NULL) == 0) {
        StringCchCopyA(tsdPtr->message, ARRAYSIZE(tsdPtr->message), "unknown error");
    } else {
        size_t length;
        StringCchLengthA(tsdPtr->message, ARRAYSIZE(tsdPtr->message), &length);

        /* Remove trailing CR/LF. */
        if (length >= 2 && tsdPtr->message[length-2] == '\r' && tsdPtr->message[length-1] == '\n') {
            tsdPtr->message[length-2] = '\0';
        }
    }

    Tcl_SetErrorCode(interp, "WINDOWS", errorId, tsdPtr->message, NULL);
    return tsdPtr->message;
}