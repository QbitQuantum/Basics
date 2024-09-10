int CLuaFunctionDefs::LoadString( lua_State* luaVM )
{
//  func,err loadstring( string text[, string name] )
    SString strInput; SString strName;

    CScriptArgReader argStream( luaVM );
    argStream.ReadString( strInput );
    argStream.ReadString( strName, "" );

    if ( !argStream.HasErrors() )
    {
        const char* szChunkname = strName.empty() ? *strInput : *strName;
        const char* cpInBuffer = strInput;
        uint uiInSize = strInput.length();

        // Decrypt if required
        const char* cpBuffer;
        uint uiSize;
        if ( !g_pNet->DecryptScript( cpInBuffer, uiInSize, &cpBuffer, &uiSize, m_pResourceManager->GetResourceName( luaVM ) + "/loadstring" ) )
        {
            SString strMessage( "argument 1 is invalid. Please re-compile at http://luac.mtasa.com/", 0 ); 
            argStream.SetCustomError( strMessage );
            cpBuffer = NULL;
            g_pCore->GetConsole()->Print( argStream.GetFullErrorMessage() );
            g_pClientGame->TellServerSomethingImportant( 1004, argStream.GetFullErrorMessage(), true );
        }

        if ( !argStream.HasErrors() )
        {
            CLuaShared::CheckUTF8BOMAndUpdate ( &cpBuffer, &uiSize );
            if ( !CLuaMain::LuaLoadBuffer( luaVM, cpBuffer, uiSize, szChunkname ) )
            {
                // Ok
                return 1;
            }
            else
            {
                lua_pushnil( luaVM );
                lua_insert( luaVM, -2 );  /* put before error message */
                return 2;  /* return nil plus error message */
            }
        }
    }
    if ( argStream.HasErrors() )
        m_pScriptDebugging->LogCustom( luaVM, argStream.GetFullErrorMessage() );

    lua_pushboolean( luaVM, false );
    return 1;
}