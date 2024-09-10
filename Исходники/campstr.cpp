void ForeignToUpper(_TCHAR *buffer)
	{
	int i = 0;
	while (buffer[i])
		{
		if (gLangIDNum != F4LANG_ENGLISH)
			{
			// Check for special characters
			if ((uchar)(buffer[i]) >= 224 && (uchar)(buffer[i]) <=253)
				buffer[i] -= 32;
			else if (_istlower(buffer[i]))
				buffer[i] = _toupper(buffer[i]);
/*
			switch (buffer[i])
				{
				case 'è':
				case 'é':
				case 'ë':
				case 'ê':
					buffer[i] = 'E';
					break;
				case 'â':
				case 'à':
				case 'á':
				case 'ä':
					buffer[i] = 'A';
					break;
				case 'ì':
				case 'í':
				case 'î':
				case 'ï':
					buffer[i] = 'I';
					break;
				case 'û':
				case 'ú':
				case 'ù':
				case 'ü':
					buffer[i] = 'U';
					break;
				case 'ç':
					buffer[i] = 'C';
					break;
				case 'ñ':
					buffer[i] = 'N';
					break;
				case 'ô':
				case 'ö':
					buffer[i] = 'O';
					break;
				default:
					if (_istlower(buffer[i]))
						buffer[i] = _toupper(buffer[i]);
				}
*/
			}
		else if (_istlower(buffer[i]))
			buffer[i] = _toupper(buffer[i]);
		i++;
		}
	}