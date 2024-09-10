int CLuaFileDefs::fileWrite ( lua_State* luaVM )
{
//  int fileWrite ( file theFile, string string1 [, string string2, string string3 ...])
    CScriptFile* pFile;

    CScriptArgReader argStream ( luaVM );
    argStream.ReadUserData ( pFile );
    
    if ( !argStream.NextIsString () )
        argStream.SetTypeError ( "string" );

    if ( !argStream.HasErrors () )
    {
        // While we're not out of string arguments
        long lBytesWritten = 0;
        long lArgBytesWritten = 0;
        
        do
        {
            // Grab argument and length
            SString strData;
            argStream.ReadString ( strData );
            unsigned long ulDataLen = strData.length ();

            // Write it and add the bytes written to our total bytes written
            lArgBytesWritten = pFile->Write ( ulDataLen, strData );
            if ( lArgBytesWritten == -1 )
            {
                m_pScriptDebugging->LogBadPointer ( luaVM, "file", 1 );
                lua_pushnil ( luaVM );
                return 1;
            }
            lBytesWritten += lArgBytesWritten;
        }
        while ( argStream.NextIsString () );
        
        // Return the number of bytes we wrote
        lua_pushnumber ( luaVM, lBytesWritten );
        return 1;
    }
    else
        m_pScriptDebugging->LogCustom ( luaVM, argStream.GetFullErrorMessage () );

    // Error
    lua_pushnil ( luaVM );
    return 1;
}