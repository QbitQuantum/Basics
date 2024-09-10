//-----------------------------------------------------------------------------
// Purpose: extracts the list of defines and includes used for this config
//-----------------------------------------------------------------------------
bool CVCProjConvert::ExtractIncludes( IXMLDOMElement *pDoc, CConfiguration & config )
{
	config.ResetDefines();
	config.ResetIncludes();
	
	if (!pDoc)
	{
		return false;
	}

#ifdef _WIN32
	CComPtr<IXMLDOMNodeList> pTools;
	pDoc->getElementsByTagName( _bstr_t("Tool"), &pTools);
	if (pTools)
	{
		long len = 0;
		pTools->get_length(&len);
		for ( int i=0; i<len; i++ )
		{
			CComPtr<IXMLDOMNode> pNode;
			pTools->get_item( i, &pNode );
			if (pNode)
			{
				CComQIPtr<IXMLDOMElement> pElem( pNode );
				CUtlSymbol toolName = GetXMLAttribValue( pElem, "Name" );
				if ( toolName == "VCCLCompilerTool" )
				{
					CUtlSymbol defines = GetXMLAttribValue( pElem, "PreprocessorDefinitions" );
					char *str = (char *)_alloca( Q_strlen( defines.String() ) + 1 );
					Assert( str );
					Q_strcpy( str, defines.String() );
					// now tokenize the string on the ";" char
					char *delim = strchr( str, ';' );
					char *curpos = str;
					while ( delim )
					{
						*delim = 0;
						delim++;
						if ( Q_stricmp( curpos, "WIN32" ) && Q_stricmp( curpos, "_WIN32" )  &&  
							 Q_stricmp( curpos, "_WINDOWS") && Q_stricmp( curpos, "WINDOWS")) // don't add WIN32 defines
						{
							config.AddDefine( curpos );
						}
						curpos = delim;
						delim = strchr( delim, ';' );
					}
					if ( Q_stricmp( curpos, "WIN32" ) && Q_stricmp( curpos, "_WIN32" )  &&  
						 Q_stricmp( curpos, "_WINDOWS") && Q_stricmp( curpos, "WINDOWS")) // don't add WIN32 defines
					{
						config.AddDefine( curpos );
					}

					CUtlSymbol includes = GetXMLAttribValue( pElem, "AdditionalIncludeDirectories" );
					char *str2 = (char *)_alloca( Q_strlen( includes.String() ) + 1 );
					Assert( str2 );
					Q_strcpy( str2, includes.String() );
					// now tokenize the string on the ";" char
					delim = strchr( str2, ',' );
					curpos = str2;
					while ( delim )
					{
						*delim = 0;
						delim++;
						config.AddInclude( curpos );
						curpos = delim;
						delim = strchr( delim, ',' );
					}
					config.AddInclude( curpos );
				}
			}
		}
	}
#elif _LINUX
	DOMNodeList *nodes= pDoc->getElementsByTagName( _bstr_t("Tool"));
	if (nodes)
	{
		int len = nodes->getLength();
		for ( int i=0; i<len; i++ )
		{
			DOMNode *node = nodes->item(i);
			if (node)
			{
				CUtlSymbol toolName = GetXMLAttribValue( node, "Name" );
				if ( toolName == "VCCLCompilerTool" )
				{
					CUtlSymbol defines = GetXMLAttribValue( node, "PreprocessorDefinitions" );
					char *str = (char *)_alloca( Q_strlen( defines.String() ) + 1 );
					Assert( str );
					Q_strcpy( str, defines.String() );
					// now tokenize the string on the ";" char
					char *delim = strchr( str, ';' );
					char *curpos = str;
					while ( delim )
					{
						*delim = 0;
						delim++;
						if ( Q_stricmp( curpos, "WIN32" ) && Q_stricmp( curpos, "_WIN32" )  &&  
							 Q_stricmp( curpos, "_WINDOWS") && Q_stricmp( curpos, "WINDOWS")) // don't add WIN32 defines
						{
							config.AddDefine( curpos );
						}
						curpos = delim;
						delim = strchr( delim, ';' );
					}
					if ( Q_stricmp( curpos, "WIN32" ) && Q_stricmp( curpos, "_WIN32" )  &&  
						 Q_stricmp( curpos, "_WINDOWS") && Q_stricmp( curpos, "WINDOWS")) // don't add WIN32 defines
					{
						config.AddDefine( curpos );
					}

					CUtlSymbol includes = GetXMLAttribValue( node, "AdditionalIncludeDirectories" );
					char *str2 = (char *)_alloca( Q_strlen( includes.String() ) + 1 );
					Assert( str2 );
					Q_strcpy( str2, includes.String() );
					// now tokenize the string on the ";" char
					char token = ',';
					delim = strchr( str2, token );
					if ( !delim )
					{
						token = ';';
						delim = strchr( str2, token );
					}
					curpos = str2;
					while ( delim )
					{
						*delim = 0;
						delim++;
						Q_FixSlashes( curpos );
						Q_strlower( curpos );
						char fullPath[ MAX_PATH ];
						Q_snprintf( fullPath, sizeof(fullPath), "%s/%s", m_BaseDir.String(), curpos );
						Q_StripTrailingSlash( fullPath );
						config.AddInclude( fullPath );
						curpos = delim;
						delim = strchr( delim, token );
					}
					Q_FixSlashes( curpos );
					Q_strlower( curpos );
					char fullPath[ MAX_PATH ];
					Q_snprintf( fullPath, sizeof(fullPath), "%s/%s", m_BaseDir.String(), curpos );
					Q_StripTrailingSlash( fullPath );
					config.AddInclude( fullPath );
				}
			}
		}
	}

#endif
	return true;
}