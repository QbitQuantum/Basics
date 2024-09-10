int CLuaFunctionDefs::ShowCursor ( lua_State* luaVM )
{
    bool bShow = false, bToggleControls = true;
    CScriptArgReader argStream ( luaVM );
    argStream.ReadBool ( bShow );
    argStream.ReadBool ( bToggleControls, true );

    if ( !argStream.HasErrors ( ) )
    {
        // Get the VM
        CLuaMain* pLuaMain = m_pLuaManager->GetVirtualMachine ( luaVM );
        if ( pLuaMain )
        {
            // Grab the resource belonging to this VM
            CResource* pResource = pLuaMain->GetResource ();
            if ( pResource )
            {
                // Show/hide it inside that resource
                pResource->ShowCursor ( bShow, bToggleControls );
                lua_pushboolean ( luaVM, true );
                return 1;
            }
        }
    }
    else
        m_pScriptDebugging->LogCustom ( luaVM, argStream.GetFullErrorMessage() );

    // Fail
    lua_pushboolean ( luaVM, false );
    return 1;
}