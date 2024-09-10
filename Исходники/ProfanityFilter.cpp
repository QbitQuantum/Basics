int ProfanityFilter::FilterProfanity(const char *input, char *output, bool filter)
{
	int count = 0;
	char* b = (char *) alloca(strlen(input) + 1); 
	strcpy(b, input);
	_strlwr(b);
	char *start = b;
	if (output)
		strcpy(output,input);

	start = strpbrk(start, WORDCHARS);
	while (start != 0)
	{
		size_t len = strspn(start, WORDCHARS);
		if (len > 0)
		{
			// we a have a word - let's check if it's a BAAAD one
			char saveChar = start[len];
			start[len] = '\0';

			// loop through profanity list			
			for (unsigned int i = 0, size = words.Size(); i < size; i++)
			{
				if (_stricmp(start, words[i].C_String()) == 0)
				{
					count++;

					// size_t len = words[i].size();
					if (filter && output)
					{
						for (unsigned int j = 0; j < len; j++)
						{
							output[start + j - b] = RandomBanChar();
						}
					}
					break;
				}				
			}
			start[len] = saveChar;
		}

		start += len;
		start = strpbrk(start, WORDCHARS);
	}

	return count;
}