int XHCPcmd_CAPABILITIES (int sockd, int argc, char **argv)
{
    int s = 0;
    
    
    if ( argc>1)
    {
        toUpper (argv[1]);
        
        if ( strcmp (argv[1], "SCRIPTING") == 0 )
            s = 1;
        else
        {
            XHCP_printXHCPResponse (sockd, RES_SYNTAXERR );  // Syntax error
            return XHCP_EXE_ERROR;
        }
    }
    
    XHCP_printMessage (sockd, s?241:236, "--000U0" );
    
    if (s)
        XHCP_print (sockd, "." );
    
    
    return XHCP_EXE_SUCCESS;
}