int CLuaVector3Defs::GetNormalized ( lua_State* luaVM )
{
    CLuaVector3D* pVector = NULL;

    CScriptArgReader argStream ( luaVM );
    argStream.ReadUserData ( pVector );

    if ( !argStream.HasErrors () )
    {
        CVector vector ( *pVector );
        vector.Normalize ();

        lua_pushvector ( luaVM, vector );
        return 1;
    }
    else
    {
        m_pScriptDebugging->LogCustom ( luaVM, argStream.GetFullErrorMessage() );
    }

    lua_pushboolean ( luaVM, false );
    return 1;   
}