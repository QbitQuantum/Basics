void convert_values( extended_info **ei )
{
	extended_info *l_ei = *ei;
	column_info *t_ci = g_ci;

	int buf_count = 0;

	wchar_t *format = NULL;

	for ( unsigned long i = 0; i < g_column_count; ++i )
	{
		// Stop processing and exit the thread.
		if ( g_kill_scan == true )
		{
			break;
		}

		if ( t_ci != NULL )
		{
			// Create a shared extended info structure to share the Windows Property names across entries.
			if ( t_ci->sei == NULL )
			{
				t_ci->sei = ( shared_extended_info * )malloc( sizeof( shared_extended_info ) );
				t_ci->sei->count = 0;

				t_ci->sei->windows_property = ( wchar_t * )malloc( sizeof( char ) * ( t_ci->Name_byte_length + sizeof( wchar_t ) ) );
				memcpy_s( t_ci->sei->windows_property, sizeof( char ) * ( t_ci->Name_byte_length + sizeof( wchar_t ) ), t_ci->Name, t_ci->Name_byte_length );

				t_ci->sei->windows_property[ t_ci->Name_byte_length / sizeof( wchar_t ) ] = 0;	// Sanity.
			}

			++( t_ci->sei->count );

			extended_info *t_ei = ( extended_info * )malloc( sizeof( extended_info ) );
			t_ei->sei = t_ci->sei;
			t_ei->property_value = NULL;
			t_ei->next = NULL;

			// See if the property value was retrieved.
			if ( g_rc_array[ i ].cbActual != 0 && g_rc_array[ i ].cbActual <= t_ci->max_size )
			{
				switch ( t_ci->column_type )
				{
					case JET_coltypBit:
					{
						// Handles Type(s): VT_BOOL

						if ( t_ci->Type == VT_BOOL )	// bool (true == -1, false == 0)
						{
							buf_count = ( t_ci->data[ 0 ] != 0 ? 4 : 5 );	// "true" or "false"
							t_ei->property_value = ( wchar_t * )malloc( sizeof( wchar_t ) * ( buf_count + 1 ) );
							wcscpy_s( t_ei->property_value, buf_count + 1, ( t_ci->data[ 0 ] != 0 ? L"true" : L"false" ) );

							break;
						}

						// For anything else, fall through to JET_coltypUnsignedByte
					}

					case JET_coltypUnsignedByte:
					{
						// Handles Type(s): VT_I1, VT_UI1, anything else from JET_coltypBit

						format = ( t_ci->Type == VT_I1 ? L"%d" : L"%lu" );
						buf_count = _scwprintf( format, t_ci->data[ 0 ] );
						if ( buf_count > 0 )
						{
							t_ei->property_value = ( wchar_t * )malloc( sizeof( wchar_t ) * ( buf_count + 1 ) );
							swprintf_s( t_ei->property_value, buf_count + 1, format, t_ci->data[ 0 ] );
						}
					}
					break;

					case JET_coltypShort:
					case JET_coltypUnsignedShort:
					{
						// Handles Type(s): VT_UI2

						unsigned short val = 0;
						memcpy_s( &val, sizeof( unsigned short ), t_ci->data, sizeof( unsigned short ) );

						format = ( t_ci->column_type == JET_coltypShort ? L"%d" : L"%lu" );
						buf_count = _scwprintf( format, val );
						if ( buf_count > 0 )
						{
							t_ei->property_value = ( wchar_t * )malloc( sizeof( wchar_t ) * ( buf_count + 1 ) );
							swprintf_s( t_ei->property_value, buf_count + 1, format, val );
						}
					}
					break;

					case JET_coltypLong:
					case JET_coltypUnsignedLong:
					{
						// Handles Type(s): VT_I4, VT_UI4

						unsigned long val = 0;
						memcpy_s( &val, sizeof( unsigned long ), t_ci->data, sizeof( unsigned long ) );

						if ( t_ci->Name_byte_length == 42 && wcscmp( t_ci->Name, L"System_FileAttributes" ) == 0 )
						{
							t_ei->property_value = get_file_attributes( val );
						}
						else if ( ( t_ci->Name_byte_length == 34 && wcscmp( t_ci->Name, L"System_SFGAOFlags" ) == 0 ) ||
								  ( t_ci->Name_byte_length == 56 && wcscmp( t_ci->Name, L"System_Link_TargetSFGAOFlags" ) == 0 ) )
						{
							t_ei->property_value = get_sfgao( val );
						}
						else
						{
							format = ( t_ci->column_type == JET_coltypLong ? L"%d" : L"%lu" );
							buf_count = _scwprintf( format, val );
							if ( buf_count > 0 )
							{
								t_ei->property_value = ( wchar_t * )malloc( sizeof( wchar_t ) * ( buf_count + 1 ) );
								swprintf_s( t_ei->property_value, buf_count + 1, format, val );
							}
						}
					}
					break;

					case JET_coltypIEEEDouble:
					{
						// Handles Type(s): VT_R8

						double val = 0.0f;
						memcpy_s( &val, sizeof( double ), t_ci->data, sizeof( double ) );

						buf_count = _scwprintf( L"%f", val );
						if ( buf_count > 0 )
						{
							t_ei->property_value = ( wchar_t * )malloc( sizeof( wchar_t ) * ( buf_count + 1 ) );
							swprintf_s( t_ei->property_value, buf_count + 1, L"%f", val );
						}
					}
					break;

					case JET_coltypCurrency:
					case JET_coltypBinary:		// May be compressed. We'll fall through to JET_coltypLongBinary to handle uncompressing it.
					case JET_coltypLongLong:
					{
						// Handles Type(s): VT_FILETIME, VT_UI8, VT_LPWSTR

						unsigned long long val = 0;
						memcpy_s( &val, sizeof( unsigned long long ), t_ci->data, sizeof( unsigned long long ) );

						if ( g_use_big_endian == true )
						{
							val = ntohll( val );
						}

						if ( t_ci->Type == VT_FILETIME )	// FILETIME
						{
							SYSTEMTIME st;
							FILETIME ft;
							ft.dwLowDateTime = ( DWORD )val;
							ft.dwHighDateTime = ( DWORD )( val >> 32 );
							FileTimeToSystemTime( &ft, &st );

							buf_count = _scwprintf( L"%d/%d/%d (%02d:%02d:%02d.%d) [UTC]", st.wMonth, st.wDay, st.wYear, st.wHour, st.wMinute, st.wSecond, st.wMilliseconds );
							if ( buf_count > 0 )
							{
								t_ei->property_value = ( wchar_t * )malloc( sizeof( wchar_t ) * ( buf_count + 1 ) );
								swprintf_s( t_ei->property_value, buf_count + 1, L"%d/%d/%d (%02d:%02d:%02d.%d) [UTC]", st.wMonth, st.wDay, st.wYear, st.wHour, st.wMinute, st.wSecond, st.wMilliseconds );
							}

							break;
						}
						else
						{
							if ( t_ci->Name_byte_length == 22 && wcscmp( t_ci->Name, L"System_Size" ) == 0 )
							{
								buf_count = _scwprintf( L"%llu", val );
								if ( buf_count > 0 )
								{
									t_ei->property_value = ( wchar_t * )malloc( sizeof( wchar_t ) * ( buf_count + 6 + 1 ) );
									swprintf_s( t_ei->property_value, buf_count + 6 + 1, L"%llu bytes", val );
								}

								break;
							}
							else if ( t_ci->Name_byte_length == 46 && wcscmp( t_ci->Name, L"System_ThumbnailCacheId" ) == 0 )
							{
								t_ei->property_value = ( wchar_t * )malloc( sizeof( wchar_t ) * 17 );
								swprintf_s( t_ei->property_value, 17, L"%016llx", val );

								break;
							}
							else if ( t_ci->Name_byte_length == 30 && wcscmp( t_ci->Name, L"InvertedOnlyMD5" ) == 0 )
							{
								// Output hex values.
								unsigned long property_value_offset = 0;
								buf_count = ( ( g_rc_array[ i ].cbActual * 2 ) + 1 );
								t_ei->property_value = ( wchar_t * )malloc( sizeof( wchar_t ) * buf_count );
								for ( unsigned long h = 0; h < g_rc_array[ i ].cbActual; ++h )
								{
									property_value_offset += swprintf_s( t_ei->property_value + property_value_offset, buf_count - property_value_offset, L"%02x", t_ci->data[ h ] );
								}

								break;
							}
							else
							{
								if ( t_ci->JetCompress == false )
								{
									// Handle 8 byte values. For everything else, fall through.
									if ( g_rc_array[ i ].cbActual == sizeof( unsigned long long ) )
									{
										format = ( t_ci->column_type == JET_coltypLongLong ? L"%lld" : L"%llu" );
										buf_count = _scwprintf( format, val );
										if ( buf_count > 0 )
										{
											t_ei->property_value = ( wchar_t * )malloc( sizeof( wchar_t ) * ( buf_count + 1 ) );
											swprintf_s( t_ei->property_value, buf_count + 1, format, val );
										}

										break;
									}
								}

								// Fall through to JET_coltypLongBinary.
							}
						}
					}

					case JET_coltypText:
					case JET_coltypLongBinary:
					case JET_coltypLongText:
					case JET_coltypGUID:
					{
						// Handles Type(s): VT_NULL, VT_LPWSTR, ( VT_VECTOR | VT_LPWSTR ), VT_BLOB, anything else from JET_coltypBinary

						if ( t_ci->column_type == JET_coltypGUID )
						{
							if ( g_rc_array[ i ].cbActual == 16 )
							{
								// Output GUID formatted value.
								unsigned long val_1 = 0;
								unsigned short val_2 = 0, val_3 = 0;

								memcpy_s( &val_1, sizeof( unsigned long ), t_ci->data, sizeof( unsigned long ) );
								memcpy_s( &val_2, sizeof( unsigned short ), t_ci->data + sizeof( unsigned long ), sizeof( unsigned short ) );
								memcpy_s( &val_3, sizeof( unsigned short ), t_ci->data + sizeof( unsigned long ) + sizeof( unsigned short ), sizeof( unsigned short ) );

								buf_count = ( ( g_rc_array[ i ].cbActual * 2 ) + 6 + 1 );
								t_ei->property_value = ( wchar_t * )malloc( sizeof( wchar_t ) * buf_count );

								unsigned long property_value_offset = swprintf_s( t_ei->property_value, buf_count, L"{%04x-%02x-%02x-", val_1, val_2, val_3 );
								for ( unsigned long h = sizeof( unsigned long ) + ( sizeof( unsigned short ) * 2 ); h < g_rc_array[ i ].cbActual; ++h )
								{
									if ( h == 10 )
									{
										t_ei->property_value[ property_value_offset ] = L'-';
										++property_value_offset;
									}
									property_value_offset += swprintf_s( t_ei->property_value + property_value_offset, buf_count - property_value_offset, L"%02x", t_ci->data[ h ] );
								}
								t_ei->property_value[ buf_count - 2 ] = L'}';
								t_ei->property_value[ buf_count - 1 ] = 0;	// Sanity.

								break;
							}

							// Fall through to default.
						}
						else
						{
							// On Vista, if Type == ( VT_VECTOR | VT_LPWSTR ), then the first 2 bytes (little-endian) = array count?
							if ( t_ci->JetCompress == true )
							{
								// Make a copy first because we may need to reuse t_ci->data and don't want it modified.
								unsigned char *data_copy = ( unsigned char * )malloc( sizeof( unsigned char ) * g_rc_array[ i ].cbActual );
								memcpy_s( data_copy, sizeof( unsigned char ) * g_rc_array[ i ].cbActual, t_ci->data, g_rc_array[ i ].cbActual );

								t_ei->property_value = uncompress_value( data_copy, g_rc_array[ i ].cbActual );

								free( data_copy );

								break;
							}
							else
							{
								if ( t_ci->Name_byte_length == 32 && wcscmp( t_ci->Name, L"InvertedOnlyPids" ) == 0 )
								{
									// Output hex values.
									unsigned long property_value_offset = 0;
									buf_count = ( ( g_rc_array[ i ].cbActual * 2 ) + 1 );
									t_ei->property_value = ( wchar_t * )malloc( sizeof( wchar_t ) * buf_count );
									for ( unsigned long h = 0; h < g_rc_array[ i ].cbActual; ++h )
									{
										property_value_offset += swprintf_s( t_ei->property_value + property_value_offset, buf_count - property_value_offset, L"%02x", t_ci->data[ h ] );
									}

									break;
								}

								// Fall through to default.
							}
						}
					}

					default:
					{
						// This is usually wchar strings.

						t_ei->property_value = ( wchar_t * )malloc( sizeof( char ) * ( g_rc_array[ i ].cbActual + sizeof( wchar_t ) ) );	// Include the NULL terminator.
						memcpy_s( t_ei->property_value, sizeof( char ) * ( g_rc_array[ i ].cbActual + sizeof( wchar_t ) ), t_ci->data, g_rc_array[ i ].cbActual );

						unsigned long property_value_size = g_rc_array[ i ].cbActual / sizeof( wchar_t );
						t_ei->property_value[ property_value_size ] = 0;	// Sanity.

						// See if we have any string arrays.
						if ( wcslen( t_ei->property_value ) < property_value_size )
						{
							// Replace the NULL character at the end of each string (except the last) with a ';' separator.
							wchar_t *t_val = t_ei->property_value;
							while ( t_val < ( t_ei->property_value + property_value_size ) )
							{
								if ( *t_val == 0 )
								{
									*t_val = L';';
								}

								++t_val;
							}
						}
					}
					break;
				}
			}

			if ( l_ei != NULL )
			{
				l_ei->next = t_ei;
			}
			else
			{
				*ei = t_ei;
			}

			l_ei = t_ei;

			// Go to the next Windows property.
			t_ci = t_ci->next;
		}