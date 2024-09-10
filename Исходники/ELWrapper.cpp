// edit line initalise
EditLine *
el_init (const char *, FILE *, FILE *, FILE *)
{
    //
    SetConsoleTitleA( "lldb" );
    // return dummy handle
    return (EditLine*) -1;
}