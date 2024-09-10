int CLuaFunctionDefs::Split ( lua_State* luaVM )
{
    SString strInput = "";
    unsigned int uiDelimiter = 0;
    SString strDelimiter;
    CScriptArgReader argStream ( luaVM );
    argStream.ReadString ( strInput );

    if ( argStream.NextIsNumber () )
    {
        argStream.ReadNumber ( uiDelimiter );
        wchar_t wUNICODE[2] = { uiDelimiter, '\0' };
        strDelimiter = UTF16ToMbUTF8 ( wUNICODE );
    }
    else  // It's already a string
        argStream.ReadString ( strDelimiter );

    if ( !argStream.HasErrors () )
    {
        // Copy the string
        char* strText = new char[strInput.length () + 1];
        strcpy ( strText, strInput );

        unsigned int uiCount = 0;
        char* szToken = strtok ( strText, strDelimiter );

        // Create a new table
        lua_newtable ( luaVM );

        // Add our first token
        lua_pushnumber ( luaVM, ++uiCount );
        lua_pushstring ( luaVM, szToken );
        lua_settable ( luaVM, -3 );

        // strtok until we're out of tokens
        while ( ( szToken = strtok ( NULL, strDelimiter ) ) )
        {
            // Add the token to the table
            lua_pushnumber ( luaVM, ++uiCount );
            lua_pushstring ( luaVM, szToken );
            lua_settable ( luaVM, -3 );
        }

        // Delete the text
        delete[] strText;
    }
    else
        m_pScriptDebugging->LogCustom ( luaVM, argStream.GetFullErrorMessage () );

    return 1;
}