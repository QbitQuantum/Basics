//-----------------------------------------------------------------------------
// Purpose: Looks up key bindings for commands and replaces them in string.
//			%<commandname>% will get replaced with its bound control, e.g. %attack2%
//			Input buffer sizes are in bytes rather than unicode character count
//			for consistency with other APIs.  If inbufsizebytes is 0 a NULL-terminated
//			input buffer is assumed, or you can pass the size of the input buffer if
//			not NULL-terminated.
//-----------------------------------------------------------------------------
void UTIL_ReplaceKeyBindings( const wchar_t *inbuf, int inbufsizebytes, wchar_t *outbuf, int outbufsizebytes )
{
	if ( !inbuf || !inbuf[0] )
		return;

	// copy to a new buf if there are vars
	outbuf[0]=0;
	int pos = 0;
	const wchar_t *inbufend = NULL;
	if ( inbufsizebytes > 0 )
	{
		inbufend = inbuf + ( inbufsizebytes / 2 );
	}

	while( inbuf != inbufend && *inbuf != 0 )
	{
		// check for variables
		if ( *inbuf == '%' )
		{
			++inbuf;

			const wchar_t *end = wcschr( inbuf, '%' );
			if ( end && ( end != inbuf ) ) // make sure we handle %% in the string, which should be treated in the output as %
			{
				wchar_t token[64];
				wcsncpy( token, inbuf, end - inbuf );
				token[end - inbuf] = 0;

				inbuf += end - inbuf;

				// lookup key names
				char binding[64];
				g_pVGuiLocalize->ConvertUnicodeToANSI( token, binding, sizeof(binding) );

				const char *key = engine->Key_LookupBinding( *binding == '+' ? binding + 1 : binding );
				if ( !key )
				{
					key = IsX360() ? "" : "< not bound >";
				}

				//!! change some key names into better names
				char friendlyName[64];
				bool bAddBrackets = false;
				if ( IsX360() )
				{
					if ( !key || !key[0] )
					{
						Q_snprintf( friendlyName, sizeof(friendlyName), "#GameUI_None" );
						bAddBrackets = true;
					}
					else
					{
						Q_snprintf( friendlyName, sizeof(friendlyName), "#GameUI_KeyNames_%s", key );
					}
				}
				else
				{
					Q_snprintf( friendlyName, sizeof(friendlyName), "%s", key );
				}
				Q_strupr( friendlyName );

				wchar_t *locName = g_pVGuiLocalize->Find( friendlyName );
				if ( !locName || wcslen(locName) <= 0)
				{
					g_pVGuiLocalize->ConvertANSIToUnicode( friendlyName, token, sizeof(token) );

					outbuf[pos] = '\0';
					wcscat( outbuf, token );
					pos += wcslen(token);
				}
				else
				{
					outbuf[pos] = '\0';
					if ( bAddBrackets )
					{
						wcscat( outbuf, L"[" );
						pos += 1;
					}
					wcscat( outbuf, locName );
					pos += wcslen(locName);
					if ( bAddBrackets )
					{
						wcscat( outbuf, L"]" );
						pos += 1;
					}
				}
			}
			else
			{
				outbuf[pos] = *inbuf;
				++pos;
			}
		}
		else
		{
			outbuf[pos] = *inbuf;
			++pos;
		}

		++inbuf;
	}

	outbuf[pos] = '\0';
}