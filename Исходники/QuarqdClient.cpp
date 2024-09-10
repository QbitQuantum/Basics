int
QuarqdClient::quit(int code)
{
    // event code goes here!
    closePort();
    exit(code);
    return 0; // never gets here obviously but shuts up the compiler!
}