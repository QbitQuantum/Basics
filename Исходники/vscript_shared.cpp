HSCRIPT VScriptCompileScript( const char *pszScriptName, bool bWarnMissing )
{
    if ( !g_pScriptVM )
    {
        return NULL;
    }

    static const char *pszExtensions[] =
    {
        "",		// SL_NONE
        ".gm",	// SL_GAMEMONKEY
        ".nut",	// SL_SQUIRREL
        ".lua", // SL_LUA
        ".py",  // SL_PYTHON
    };

    const char *pszVMExtension = pszExtensions[g_pScriptVM->GetLanguage()];
    const char *pszIncomingExtension = V_strrchr( pszScriptName , '.' );
    if ( pszIncomingExtension && V_strcmp( pszIncomingExtension, pszVMExtension ) != 0 )
    {
        Log_Warning( LOG_VScript, "Script file type does not match VM type\n" );
        return NULL;
    }

    CFmtStr scriptPath;
    if ( pszIncomingExtension )
    {
        scriptPath.sprintf( "scripts/vscripts/%s", pszScriptName );
    }
    else
    {
        scriptPath.sprintf( "scripts/vscripts/%s%s", pszScriptName,  pszVMExtension );
    }

    const char *pBase;
    CUtlBuffer bufferScript;

    if ( g_pScriptVM->GetLanguage() == SL_PYTHON )
    {
        // python auto-loads raw or precompiled modules - don't load data here
        pBase = NULL;
    }
    else
    {
        bool bResult = filesystem->ReadFile( scriptPath, "GAME", bufferScript );

        if( !bResult )
        {
            Log_Warning( LOG_VScript, "Script not found (%s) \n", scriptPath.operator const char *() );
            Assert( "Error running script" );
        }

        pBase = (const char *) bufferScript.Base();

        if ( !pBase || !*pBase )
        {
            return NULL;
        }
    }


    const char *pszFilename = V_strrchr( scriptPath, '/' );
    pszFilename++;
    HSCRIPT hScript = g_pScriptVM->CompileScript( pBase, pszFilename );
    if ( !hScript )
    {
        Log_Warning( LOG_VScript, "FAILED to compile and execute script file named %s\n", scriptPath.operator const char *() );
        Assert( "Error running script" );
    }
    return hScript;
}