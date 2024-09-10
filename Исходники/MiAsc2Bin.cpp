void * Asc2Bin(const char *source,const MiI32 count,const char *spec,void *dest)
{

	MiI32   cnt = 0;
	MiI32   size  = 0;

	Atype types[MAXARG];

	const char *ctype = spec;

	while ( *ctype )
	{
		switch ( ToLower(*ctype) )
		{
			case 'f': size+= sizeof(MiF32); types[cnt] = AT_FLOAT; cnt++;  break;
			case 'd': size+= sizeof(MiI32);   types[cnt] = AT_INT;   cnt++;  break;
			case 'c': size+=sizeof(char);   types[cnt] = AT_CHAR;  cnt++;  break;
			case 'b': size+=sizeof(char);   types[cnt] = AT_BYTE;  cnt++;  break;
			case 'h': size+=sizeof(short);  types[cnt] = AT_SHORT; cnt++;  break;
			case 'p': size+=sizeof(const char *);  types[cnt] = AT_STR; cnt++;  break;
			case 'x':
				{
					Atype type = AT_HEX4;
					MiI32 sz = 4;
					switch ( ctype[1] )
					{
						case '1':  type = AT_HEX1; sz   = 1; ctype++;  break;
						case '2':  type = AT_HEX2; sz   = 2; ctype++;  break;
						case '4':  type = AT_HEX4; sz   = 4; ctype++;  break;
					}
					types[cnt] = type;
					size+=sz;
					cnt++;
				}
				break;
		}
		if ( cnt == MAXARG ) return 0; // over flowed the maximum specification!
		ctype++;
	}

	bool myalloc = false;

	if ( dest == 0 )
	{
		myalloc = true;
		dest = (char *) MI_ALLOC(sizeof(char)*count*size);
	}

	// ok...ready to parse lovely data....
	memset(dest,0,size_t(count*size)); // zero out memory

	char *dst = (char *) dest; // where we are storing the results
	for (MiI32 i=0; i<count; i++)
	{
		for (MiI32 j=0; j<cnt; j++)
		{
			source = SkipWhitespace(source); // skip white spaces.

			if (source == NULL ||  *source == 0 ) // we hit the end of the input data before we successfully parsed all input!
			{
				if ( myalloc )
				{
					MI_FREE(dest);
				}
				return 0;
			}

			switch ( types[j] )
			{
				case AT_FLOAT:
					{
						MiF32 *v = (MiF32 *) dst;
						*v = GetFloatValue(source,&source);
						dst+=sizeof(MiF32);
					}
					break;
				case AT_INT:
					{
						MiI32 *v = (MiI32 *) dst;
						*v = GetIntValue( source, &source );
						dst+=sizeof(MiI32);
					}
					break;
				case AT_CHAR:
					{
						*dst++ = *source++;
					}
					break;
				case AT_BYTE:
					{
						char *v = (char *) dst;
						*v = (char)GetIntValue(source,&source);
						dst+=sizeof(char);
					}
					break;
				case AT_SHORT:
					{
						short *v = (short *) dst;
						*v = (short)(unsigned short)GetIntValue( source,&source );
						dst+=sizeof(short);
					}
					break;
				case AT_STR:
					{
						const char **ptr = (const char **) dst;
						*ptr = source;
						dst+=sizeof(const char *);
						while ( *source && !IsWhitespace(*source) ) source++;
					}
					break;
				case AT_HEX1:
					{
						MiU32 hex = GetHEX1(source,&source);
						MiU8 *v = (MiU8 *) dst;
						*v = (MiU8)hex;
						dst+=sizeof(MiU8);
					}
					break;
				case AT_HEX2:
					{
						MiU32 hex = GetHEX2(source,&source);
						unsigned short *v = (unsigned short *) dst;
						*v = (unsigned short)hex;
						dst+=sizeof(unsigned short);
					}
					break;
				case AT_HEX4:
					{
						MiU32 hex = GetHEX4(source,&source);
						MiU32 *v = (MiU32 *) dst;
						*v = hex;
						dst+=sizeof(MiU32);
					}
					break;
				case AT_LAST: // Make compiler happy
					break;
			}
		}
	}

	return dest;
}