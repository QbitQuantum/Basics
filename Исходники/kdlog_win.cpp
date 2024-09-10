void KDSystemLogDevice::doLogEncoded( KDLog::Severity severity, const QByteArray & msg ) {
    const char* strarray[1];
    strarray[0] = msg.constData();
    if ( ReportEventA( d->internal,
                       severityToEventLogType( severity ),
                       0, // category?
                       0, // Event ID
                       NULL, // user security identifier (optional)
                       1, // number of strings to merge with message
                       0, // size of raw (binary) data (in bytes)
                       strarray, // array of strings to merge with message
                       NULL ) )
        return;

    // error:

    char* lpMsgBuf;
    const int err = GetLastError();
    FormatMessageA( FORMAT_MESSAGE_ALLOCATE_BUFFER|
                    FORMAT_MESSAGE_FROM_SYSTEM|
                    FORMAT_MESSAGE_IGNORE_INSERTS,
                    NULL,
                    err,
                    MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT ),
                    (LPSTR)(&lpMsgBuf),
                    0,
                    NULL);
    fprintf( stderr, "ReportEventA() failed: %u=\"%s\" Message was \"%s\"\n",
             err, lpMsgBuf, msg.constData() );
}