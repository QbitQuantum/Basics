//
// Output timestamped line into the debugger
//
void SharedUtil::OutputDebugLine ( const char* szMessage )
{
    if ( szMessage[0] == '[' )
    {
        // Filter test
        const char* szEnd = strchr ( szMessage, ']' );
        if ( szEnd && IsDebugTagHidden ( std::string ( szMessage + 1, szEnd - szMessage - 1 ) ) )
            return;
    }

    SString strMessage = GetLocalTimeString ( false, true ) + " - " + szMessage;
    if ( strMessage.length () > 0 && strMessage[ strMessage.length () - 1 ] != '\n' )
        strMessage += "\n";
#ifdef _WIN32
    OutputDebugString ( strMessage );
#else
    // Other platforms here
#endif
}