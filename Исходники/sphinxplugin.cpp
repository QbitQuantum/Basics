bool sphPluginCreate ( const char * szLib, PluginType_e eType, const char * sName, ESphAttr eUDFRetType, CSphString & sError )
{
#if !HAVE_DLOPEN
	sError = "no dlopen(), no plugins";
	return false;
#else
	if ( !g_bPluginsEnabled )
	{
		sError = "plugin support disabled (requires a valid plugin_dir)";
		return false;
	}

	// validate library name
	for ( const char * p = szLib; *p; p++ )
		if ( *p=='/' || *p=='\\' )
	{
		sError = "restricted character (path delimiter) in a library file name";
		return false;
	}

	CSphString sLib = szLib;
	sLib.ToLower();

	// FIXME? preregister known rankers instead?
	if ( eType==PLUGIN_RANKER )
	{
		for ( int i=0; i<SPH_RANK_TOTAL; i++ )
		{
			const char * r = sphGetRankerName ( ESphRankMode(i) );
			if ( r && strcasecmp ( sName, r )==0 )
			{
				sError.SetSprintf ( "%s is a reserved ranker name", r );
				return false;
			}
		}
	}

	// from here, we need a lock (we intend to update the plugin hash)
	CSphScopedLock<CSphMutex> tLock ( g_tPluginMutex );

	// validate function name
	PluginKey_t k ( eType, sName );
	if ( g_hPlugins(k) )
	{
		sError.SetSprintf ( "plugin '%s' already exists", k.m_sName.cstr() );
		return false;
	}

	// lookup or load library
	PluginLib_c * pLib = NULL;
	if ( g_hPluginLibs ( sLib ) )
	{
		pLib = g_hPluginLibs [ sLib ];
		pLib->AddRef();
	} else
	{
		pLib = LoadPluginLibrary ( sLib.cstr(), sError );
		if ( !pLib )
			return false;
	}
	assert ( pLib->GetHandle() );

	PluginDesc_c * pPlugin = NULL;
	const SymbolDesc_t * pSym = NULL;
	switch ( eType )
	{
		case PLUGIN_RANKER:					pPlugin = new PluginRanker_c ( pLib ); pSym = g_dSymbolsRanker; break;
		case PLUGIN_INDEX_TOKEN_FILTER:		pPlugin = new PluginTokenFilter_c ( pLib ); pSym = g_dSymbolsTokenFilter; break;
		case PLUGIN_QUERY_TOKEN_FILTER:		pPlugin = new PluginQueryTokenFilter_c ( pLib ); pSym = g_dSymbolsQueryTokenFilter; break;
		case PLUGIN_FUNCTION:				pPlugin = new PluginUDF_c ( pLib, eUDFRetType ); pSym = g_dSymbolsUDF; break;
		default:
			sError.SetSprintf ( "INTERNAL ERROR: unknown plugin type %d in CreatePlugin()", (int)eType );
			pLib->Release();
			return false;
	}

	// release the refcount that this very function is holding
	// or in other words, transfer the refcount to newly created plugin instance (it does its own addref)
	pLib->Release();

	if ( !PluginLoadSymbols ( pPlugin, pSym, pLib->GetHandle(), k.m_sName.cstr(), sError ) )
	{
		sError.SetSprintf ( "%s in %s", sError.cstr(), sLib.cstr() );
		pPlugin->Release();
		return false;
	}

	// add library if needed
	if ( !g_hPluginLibs ( sLib ) )
	{
		Verify ( g_hPluginLibs.Add ( pLib, pLib->GetName() ) );
		pLib->AddRef(); // the hash reference
	}

	// add function
	Verify ( g_hPlugins.Add ( pPlugin, k ) );
	pPlugin->GetLib()->m_iHashedPlugins++;
	return true;
#endif // HAVE_DLOPEN
}