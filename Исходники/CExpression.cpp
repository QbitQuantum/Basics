INT64 CExpression::GetSingle( LPCTSTR & pszArgs )
{
	ADDTOCALLSTACK("CExpression::GetSingle");
	// Parse just a single expression without any operators or ranges.
	ASSERT(pszArgs);
	GETNONWHITESPACE( pszArgs );

	LPCTSTR orig = pszArgs;
	if (pszArgs[0]=='.') pszArgs++;

	if ( pszArgs[0] == '0' )	// leading '0' = hex value.
	{
		// A hex value.
		if ( pszArgs[1] == '.' )	// leading 0. means it really is decimal.
		{
			pszArgs += 2;
			goto try_dec;
		}

		LPCTSTR pStart = pszArgs;
		ULONGLONG val = 0;
		for (;;)
		{
			TCHAR ch = *pszArgs;
			if ( IsDigit( ch ))
				ch -= '0';
			else
			{
				ch = static_cast<TCHAR>(tolower(ch));
				if ( ch > 'f' || ch <'a' )
				{
					if ( ch == '.' && pStart[0] != '0' )	// ok i'm confused. it must be decimal.
					{
						pszArgs = pStart;
						goto try_dec;
					}
					break;
				}
				ch -= 'a' - 10;
			}
			val *= 0x10;
			val += ch;
			pszArgs ++;
		}
		return( (INT64)val );
	}
	else if ( pszArgs[0] == '.' || IsDigit(pszArgs[0]))
	{
		// A decminal number
try_dec:
		INT64 iVal = 0;
		for ( ; ; pszArgs++ )
		{
			if ( *pszArgs == '.' )
				continue;	// just skip this.
			if ( ! IsDigit( *pszArgs ))
				break;
			iVal *= 10;
			iVal += *pszArgs - '0';
		}
		return( iVal );
	}
	else if ( ! _ISCSYMF(pszArgs[0]))
	{
	#pragma region maths
		// some sort of math op ?

		switch ( pszArgs[0] )
		{
		case '{':
			pszArgs ++;
			return( GetRange( pszArgs ));
		case '[':
		case '(': // Parse out a sub expression.
			pszArgs ++;
			return(GetVal( pszArgs ));
		case '+':
			pszArgs++;
			break;
		case '-':
			pszArgs++;
			return( -GetSingle( pszArgs ));
		case '~':	// Bitwise not.
			pszArgs++;
			return( ~GetSingle( pszArgs ));
		case '!':	// boolean not.
			pszArgs++;
			if ( pszArgs[0] == '=' )  // odd condition such as (!=x) which is always true of course.
			{
				pszArgs++;		// so just skip it. and compare it to 0
				return( GetSingle( pszArgs ));
			}
			return( !GetSingle( pszArgs ));
		case ';':	// seperate field.
		case ',':	// seperate field.
		case '\0':
			return( 0 );
		}
#pragma endregion maths
	}
	else
	#pragma region intrinsics
	{
		// Symbol or intrinsinc function ?

		INTRINSIC_TYPE iIntrinsic = (INTRINSIC_TYPE) FindTableHeadSorted( pszArgs, sm_IntrinsicFunctions, COUNTOF(sm_IntrinsicFunctions)-1 );
		if ( iIntrinsic >= 0 )
		{
			size_t iLen = strlen(sm_IntrinsicFunctions[iIntrinsic]);
			if ( pszArgs[iLen] == '(' )
			{
				pszArgs += (iLen + 1);
				TCHAR * pszArgsNext;
				Str_Parse( const_cast<TCHAR*>(pszArgs), &(pszArgsNext), ")" );
	
				TCHAR * ppCmd[5];
				INT64 iResult;
				size_t iCount = 0;
	
				switch ( iIntrinsic )
				{
					case INTRINSIC_ID:
					{
						if ( pszArgs && *pszArgs )
						{
							iCount = 1;
							iResult = RES_GET_INDEX( GetVal( pszArgs )); // RES_GET_INDEX
						}
						else
						{
							iCount = 0;
							iResult = 0;
						}

					} break;

					case INTRINSIC_LOGARITHM:
					{
						iCount = 0;
						iResult = 0;

						if ( pszArgs && *pszArgs )
						{
							int iArgument = static_cast<long>(GetVal(pszArgs));
							if ( iArgument <= 0 )
							{
								DEBUG_ERR(( "Exp_GetVal: (x)Log(%d) is %s\n", iArgument, (!iArgument) ? "infinite" : "undefined" ));
							}
							else
							{
								iCount = 1;

								if ( strchr(pszArgs, ',') )
								{
									iCount++; SKIP_ARGSEP(pszArgs);
									if ( !strcmpi(pszArgs, "e") )
									{
										iResult = static_cast<INT64>(log(static_cast<double>(iArgument)));
									}
									else if ( !strcmpi(pszArgs, "pi") )
									{
										iResult = static_cast<INT64>(log(static_cast<double>(iArgument)) / log(M_PI));
									}
									else
									{
										INT64 iBase = GetVal(pszArgs);
										if ( iBase <= 0 )
										{
											DEBUG_ERR(( "Exp_GetVal: (%lld)Log(%d) is %s\n", iBase, iArgument, (!iBase) ? "infinite" : "undefined" ));
											iCount = 0;
										}
										else
										{
											iResult = static_cast<INT64>(log(static_cast<double>(iArgument)) / log(static_cast<double>(iBase)));
										}
									}
								}
								else
								{
									iResult = static_cast<INT64>(log10(static_cast<double>(iArgument)));
								}							
							}
						}

					} break;

					case INTRINSIC_NAPIERPOW:
					{
						if ( pszArgs && *pszArgs )
						{
							iCount = 1;
							iResult = static_cast<INT64>(exp(static_cast<double>(GetVal(pszArgs))));
						}
						else
						{
							iCount = 0;
							iResult = 0;
						}

					} break;

					case INTRINSIC_SQRT:
					{
						iCount = 0;
						iResult = 0;

						if ( pszArgs && *pszArgs )
						{
							int iTosquare = static_cast<long>(GetVal(pszArgs));

							if (iTosquare >= 0)
							{
								iCount++;
								iResult = static_cast<INT64>(sqrt(static_cast<double>(iTosquare)));
							}
							else
							{
								DEBUG_ERR(( "Exp_GetVal: Sqrt of negative number (%d) is impossible\n", iTosquare ));
							}
						}

					} break;

					case INTRINSIC_SIN:
					{
						if ( pszArgs && *pszArgs )
						{
							iCount = 1;
							iResult = static_cast<INT64>(sin(static_cast<double>(GetVal(pszArgs))));
						}
						else
						{
							iCount = 0;
							iResult = 0;
						}

					} break;

					case INTRINSIC_ARCSIN:
					{
						if ( pszArgs && *pszArgs )
						{
							iCount = 1;
							iResult = static_cast<INT64>(asin(static_cast<double>(GetVal(pszArgs))));
						}
						else
						{
							iCount = 0;
							iResult = 0;
						}

					} break;

					case INTRINSIC_COS:
					{
						if ( pszArgs && *pszArgs )
						{
							iCount = 1;
							iResult = static_cast<INT64>(cos(static_cast<double>(GetVal(pszArgs))));
						}
						else
						{
							iCount = 0;
							iResult = 0;
						}

					} break;

					case INTRINSIC_ARCCOS:
					{
						if ( pszArgs && *pszArgs )
						{
							iCount = 1;
							iResult = static_cast<INT64>(acos(static_cast<double>(GetVal(pszArgs))));
						}
						else
						{
							iCount = 0;
							iResult = 0;
						}

					} break;

					case INTRINSIC_TAN:
					{
						if ( pszArgs && *pszArgs )
						{
							iCount = 1;
							iResult = static_cast<INT64>(tan(static_cast<double>(GetVal(pszArgs))));
						}
						else
						{
							iCount = 0;
							iResult = 0;
						}

					} break;

					case INTRINSIC_ARCTAN:
					{
						if ( pszArgs && *pszArgs )
						{
							iCount = 1;
							iResult = static_cast<INT64>(atan(static_cast<double>(GetVal(pszArgs))));
						}
						else
						{
							iCount = 0;
							iResult = 0;
						}

					} break;

					case INTRINSIC_StrIndexOf:
					{
						iCount = Str_ParseCmds( const_cast<TCHAR*>(pszArgs), ppCmd, 3, "," );
						if ( iCount < 2 )
							iResult = -1;
						else
							iResult = Str_IndexOf(ppCmd[0],ppCmd[1],(iCount==3)?static_cast<long>(GetVal(ppCmd[2])):0);
					} break;

					case INTRINSIC_STRMATCH:
					{
						iCount = Str_ParseCmds( const_cast<TCHAR*>(pszArgs), ppCmd, 2, "," );
						if ( iCount < 2 )
							iResult = 0;
						else
							iResult = (Str_Match( ppCmd[0], ppCmd[1] ) == MATCH_VALID ) ? 1 : 0;
					} break;

					case INTRINSIC_STRREGEX:
					{
						iCount = Str_ParseCmds( const_cast<TCHAR*>(pszArgs), ppCmd, 2, "," );
						if ( iCount < 2 )
							iResult = 0;
						else
						{
							TCHAR * tLastError = Str_GetTemp();
							iResult = Str_RegExMatch( ppCmd[0], ppCmd[1], tLastError );
							if ( iResult == -1 )
							{
								DEBUG_ERR(( "STRREGEX bad function usage. Error: %s\n", tLastError ));
							}
						}
					} break;

					case INTRINSIC_RANDBELL:
					{
						iCount = Str_ParseCmds( const_cast<TCHAR*>(pszArgs), ppCmd, 2, "," );
						if ( iCount < 2 )
							iResult = 0;
						else
							iResult = Calc_GetBellCurve( static_cast<long>(GetVal( ppCmd[0] )), static_cast<long>(GetVal( ppCmd[1] )));
					} break;

					case INTRINSIC_STRASCII:
					{
						if ( pszArgs && *pszArgs )
						{
							iCount = 1;
							iResult = pszArgs[0];
						}
						else
						{
							iCount = 0;
							iResult = 0;
						}
					} break;

					case INTRINSIC_RAND:
					{
						iCount = Str_ParseCmds( const_cast<TCHAR*>(pszArgs), ppCmd, 2, "," );
						if ( iCount <= 0 )
							iResult = 0;
						else
						{
							INT64 val1 = GetVal( ppCmd[0] );
							if ( iCount == 2 )
							{
								INT64 val2 = GetVal( ppCmd[1] );
								iResult = Calc_GetRandLLVal2( val1, val2 );
							}
							else
								iResult = Calc_GetRandLLVal(val1);
						}
					} break;

					case INTRINSIC_STRCMP:
					{
						iCount = Str_ParseCmds( const_cast<TCHAR*>(pszArgs), ppCmd, 2, "," );
						if ( iCount < 2 )
							iResult = 1;
						else
							iResult = strcmp(ppCmd[0], ppCmd[1]);
					} break;

					case INTRINSIC_STRCMPI:
					{
						iCount = Str_ParseCmds( const_cast<TCHAR*>(pszArgs), ppCmd, 2, "," );
						if ( iCount < 2 )
							iResult = 1;
						else
							iResult = strcmpi(ppCmd[0], ppCmd[1]);
					} break;

					case INTRINSIC_STRLEN:
					{
						iCount = 1;
						iResult = strlen(pszArgs);
					} break;

					case INTRINSIC_ISOBSCENE:
					{
						iCount = 1;
						iResult = g_Cfg.IsObscene( pszArgs );
					} break;
					case INTRINSIC_ISNUMBER:
					{
						iCount = 1;
						{
							char z[64];
							LTOA(atol(pszArgs), z, 10);
							iResult = strcmp(pszArgs, z) ? 0 : 1;
						}
					} break;

					case INTRINSIC_QVAL:
					{
						iCount = Str_ParseCmds( const_cast<TCHAR*>(pszArgs), ppCmd, 5, "," );
						if ( iCount < 3 )
							iResult = 0;
						else
						{
							INT64 a1 = GetSingle(ppCmd[0]);
							INT64 a2 = GetSingle(ppCmd[1]);
							if ( a1 < a2 ) iResult = GetSingle(ppCmd[2]);
							else if ( a1 == a2 ) iResult = ( iCount < 4 ) ? 0 : GetSingle(ppCmd[3]);
							else iResult = ( iCount < 5 ) ? 0 : GetSingle(ppCmd[4]);
						}
					} break;

					case INTRINSIC_ABS:
					{
						iCount = 1;
						iResult = llabs(GetVal(pszArgs));
					} break;

					default:
						iCount = 0;
						iResult = 0;
						break;
				}

				pszArgs = pszArgsNext;

				if ( ! iCount )
				{
					DEBUG_ERR(( "Bad intrinsic function usage: Missing arguments\n" ));
					return 0;
				}
				else
				{
					return iResult;
				}
			}
		}

		// Must be a symbol of some sort ?
		long long lVal;
		if ( m_VarGlobals.GetParseVal( pszArgs, &lVal ) )
			return(lVal);
		if ( m_VarDefs.GetParseVal( pszArgs, &lVal ) )
			return(lVal);
	}
#pragma endregion intrinsics

	// hard end ! Error of some sort.
	TCHAR szTag[ EXPRESSION_MAX_KEY_LEN ];
	size_t i = GetIdentifierString( szTag, pszArgs );
	pszArgs += i;	// skip it.
	if (strlen(orig)> 1)
		DEBUG_ERR(("Undefined symbol '%s' ['%s']\n", szTag, orig));
	else
		DEBUG_ERR(("Undefined symbol '%s'\n", szTag));
	return( 0 );
}