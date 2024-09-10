int CLuaCryptDefs::Hash ( lua_State* luaVM )
{
    //  string hash ( string type, string data )
    EHashFunctionType hashFunction; SString strSourceData;

    CScriptArgReader argStream ( luaVM );
    argStream.ReadEnumString ( hashFunction );
    argStream.ReadString ( strSourceData );

    if ( !argStream.HasErrors () )
    {
        SString strResult = GenerateHashHexString ( hashFunction, strSourceData );
        lua_pushstring ( luaVM, strResult.ToLower () );
        return 1;
    }
    else
        m_pScriptDebugging->LogCustom ( luaVM, argStream.GetFullErrorMessage () );

    lua_pushboolean ( luaVM, false );
    return 1;
}