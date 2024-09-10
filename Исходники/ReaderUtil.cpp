void decodeArgumentStrings( std::vector<std::string>& entity_arguments )
{
	std::vector<std::string>::iterator it = entity_arguments.begin();
	for( ; it != entity_arguments.end(); ++it )
	{
		std::string& argument_str = (*it);
		const size_t arg_length = argument_str.length();
		
		std::string arg_str_new = "";

		if( arg_length > 0 )
		{
			arg_str_new.reserve(arg_length);

			char* stream_pos = (char*)argument_str.c_str();				// ascii characters from STEP file
			//char* stream_pos_new = (char*)arg_str_new.c_str();			// ascii characters from STEP file
			{
				while( *stream_pos != '\0' )
				{
					if( *stream_pos == '\\' )
					{
						if( *(stream_pos+1) == 'S' )
						{
							if( *(stream_pos+2) == '\\' )
							{
								if( *(stream_pos+3) != '\0' )
								{
									if( *(stream_pos+4) == '\\' )
									{
										if( *(stream_pos+5) == 'S' )
										{
											if( *(stream_pos+6) == '\\' )
											{
												if( *(stream_pos+7) != '\0' )
												{
													char first = *(stream_pos+3);
													char second = *(stream_pos+7);

													//*stream_pos_new = char(125 + first + second);
													//++stream_pos_new;
													arg_str_new += char(125 + first + second);

													stream_pos += 8;
													continue;
												}
											}
										}
									}
									else 
									{
										// next characters code value v shall be interpreted as v + 128
										char char_pos = *(stream_pos+3);
										char char_pos_128 =  char_pos + 128;

										//*stream_pos_new = char_pos_128;
										//++stream_pos_new;
										arg_str_new += char_pos_128;
										stream_pos += 4;
										continue;
									}
								}
							}
						}
						else if( *(stream_pos+1) == 'X' )
						{
							if( *(stream_pos+2) == '\\' )
							{
								wchar_t wc = Hex2Wchar(*(stream_pos+3), *(stream_pos+4));
#ifdef _WIN32
								char char_ascii = wctob(wc);
										
								if( char_ascii < 0)
								{
									//we got a multibyte character here
									char buf[2];
									int len = WideCharToMultiByte(CP_UTF8, 0, &wc, 1, buf, 2, nullptr, nullptr);
									arg_str_new+= buf[0];
									arg_str_new+= buf[1];
								}
								else
								{
									arg_str_new += char_ascii;
								}
#else
								unsigned char char_ascii = wctob(wc);
								arg_str_new += char_ascii;
#endif
								stream_pos += 4;
								continue;
							}
							else if( *(stream_pos+2) == '0' )
							{
								if( *(stream_pos+3) == '\\' )
								{
									stream_pos += 4;
									continue;
								}
							}
							else if( *(stream_pos+2) == '2' )
							{
								if( *(stream_pos+3) == '\\' )
								{
									// the following sequence of multiples of four hexadecimal characters shall be interpreted as encoding the 
									// two-octet representation of characters from the BMP in ISO 10646

									bool finished = false;
									stream_pos += 4;

									do
									{
										wchar_t wc = Hex4Wchar(*(stream_pos), *(stream_pos+1), *(stream_pos+2), *(stream_pos+3));
#ifdef _WIN32
										char char_ascii = wctob(wc);

										if( char_ascii < 0 )
										{
											//we got a multibyte character here
											char buf[2];
											int len = WideCharToMultiByte(CP_UTF8, 0, &wc, 1, buf, 2, nullptr, nullptr);
											arg_str_new+= buf[0];
											arg_str_new+= buf[1];
										}
										else
										{
											arg_str_new+= char_ascii;
										}
#else
										unsigned char char_ascii = wctob(wc);
										arg_str_new+= char_ascii;
#endif
										stream_pos += 4;

									} while (( *stream_pos != '\0' ) && ( *stream_pos != '\\' ));

									continue;
								}
							}
						}
						else if( *(stream_pos+1) == 'N' )
						{
							if( *(stream_pos+2) == '\\' )
							{
								arg_str_new += "\n";
								stream_pos += 3;
								continue;
							}
						}
					}
					
					arg_str_new+= *stream_pos;
					++stream_pos;
				}
			}
		}
		argument_str.assign( arg_str_new );
	}
}