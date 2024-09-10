//-------------------------------------------------------------------------
void SharedTools::ErrorMessage( const Char* message )
{
    MessageBoxA(NULL, message, APP_NAMEC, MB_OK|MB_ICONERROR);
}