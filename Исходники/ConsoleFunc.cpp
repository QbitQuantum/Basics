void _auto_login( )
{
    CScanner s;
    if( TRUE == s.Load( "autologin.ini" ) )
    {
        while( s.tok != FINISHED )
        {
            s.GetToken();

            if( "Account" == s.Token )
            {
                s.GetToken();
                g_Console._strAccount = s.Token;
            }
            else if( "Password" == s.Token )
            {
                s.GetToken();
                g_Console._StrPassword = s.Token;
            }
            else if( "n2ndPassword" == s.Token )
            {
                g_Console._nPasswordReal = s.GetNumber();
            }
            else if( "nServer" == s.Token )
            {
                g_Console._nServer = s.GetNumber();
            }
            else if( "nCharacter" == s.Token )
            {
                g_Console._nCharacter = s.GetNumber();
            }
        }
    }
}