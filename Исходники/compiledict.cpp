static int compile_line(char *linebuf, char *dict_line, int *hash)
{//===============================================================
// Compile a line in the language_list file
	unsigned char  c;
	char *p;
	char *word;
	char *phonetic;
	unsigned int  ix;
	int  step;
	unsigned int  n_flag_codes = 0;
	int  flag_offset;
	int  length;
	int  multiple_words = 0;
	char *multiple_string = NULL;
	char *multiple_string_end = NULL;
	
	int len_word;
	int len_phonetic;
	int text_not_phonemes;   // this word specifies replacement text, not phonemes
	unsigned int  wc;
	int all_upper_case;
	
	char *mnemptr;
	char *comment;
	unsigned char flag_codes[100];
	char encoded_ph[200];
	unsigned char bad_phoneme[4];
static char nullstring[] = {0};

	comment = NULL;
	text_not_phonemes = 0;
	phonetic = word = nullstring;

if(memcmp(linebuf,"_-",2)==0)
{
step=1;  // TEST
}
	p = linebuf;
//	while(isspace2(*p)) p++;

#ifdef deleted
	if(*p == '$')
	{
		if(memcmp(p,"$textmode",9) == 0)
		{
			text_mode = 1;
			return(0);
		}
		if(memcmp(p,"$phonememode",12) == 0)
		{
			text_mode = 0;
			return(0);
		}
	}
#endif

	step = 0;
	
	c = 0;
	while(c != '\n')
	{
		c = *p;
	
		if((c == '?') && (step==0))
		{
			// conditional rule, allow only if the numbered condition is set for the voice
			flag_offset = 100;

			p++;
			if(*p == '!')
			{
				// allow only if the numbered condition is NOT set
				flag_offset = 132;
				p++;
			}

			ix = 0;
			if(isdigit(*p))
			{
				ix += (*p-'0');
				p++;
			}
			if(isdigit(*p))
			{
				ix = ix*10 + (*p-'0');
				p++;
			}
			flag_codes[n_flag_codes++] = ix + flag_offset;
			c = *p;
		}
		
		if((c == '$') && isalnum(p[1]))
		{
			/* read keyword parameter */
			mnemptr = p;
			while(!isspace2(c = *p)) p++;
			*p = 0;
	
			ix = LookupMnem(mnem_flags,mnemptr);
			if(ix > 0)
			{
				if(ix == 200)
				{
					text_mode = 1;
				}
				else
				if(ix == 201)
				{
					text_mode = 0;
				}
				else
				if(ix == BITNUM_FLAG_TEXTMODE)
				{
					text_not_phonemes = 1;
				}
				else
				{
					flag_codes[n_flag_codes++] = ix;
				}
			}
			else
			{
				fprintf(f_log,"%5d: Unknown keyword: %s\n",linenum,mnemptr);
				error_count++;
			}
		}
	
		if((c == '/') && (p[1] == '/') && (multiple_words==0))
		{
			c = '\n';   /* "//" treat comment as end of line */
			comment = p;
		}
	
		switch(step)
		{
		case 0:
			if(c == '(')
			{
				multiple_words = 1;
				word = p+1;
				step = 1;
			}
			else
			if(!isspace2(c))
			{
				word = p;
				step = 1;
			}
			break;
	
		case 1:
			if((c == '-') && (word[0] != '_'))
			{
				flag_codes[n_flag_codes++] = BITNUM_FLAG_HYPHENATED;
				c = ' ';
			}
			if(isspace2(c))
			{
				p[0] = 0;   /* terminate english word */

				if(multiple_words)
				{
					multiple_string = multiple_string_end = p+1;
					step = 2;
				}
				else
				{
					step = 3;
				}
			}
			else
			if((c == ')') && multiple_words)
			{
				p[0] = 0;
				step = 3;
				multiple_words = 0;
			}
			break;

		case 2:
			if(isspace2(c))
			{
				multiple_words++;
			}
			else
			if(c == ')')
			{
				p[0] = ' ';   // terminate extra string
				multiple_string_end = p+1;
				step = 3;
			}
			break;
	
		case 3:
			if(!isspace2(c))
			{
				phonetic = p;
				step = 4;
			}
			break;
	
		case 4:
			if(isspace2(c))
			{
				p[0] = 0;   /* terminate phonetic */
				step = 5;
			}
			break;
	
		case 5:
			break;
		}
		p++;
	}
	
	if(word[0] == 0)
	{
#ifdef OPT_FORMAT
		if(comment != NULL)
			fprintf(f_log,"%s",comment);
		else
			fputc('\n',f_log);
#endif
		return(0);   /* blank line */
	}

	if(text_mode)
		text_not_phonemes = 1;

	if(text_not_phonemes != translator->langopts.textmode)
	{
		flag_codes[n_flag_codes++] = BITNUM_FLAG_TEXTMODE;
	}

	if(text_not_phonemes)
	{
		// this is replacement text, so don't encode as phonemes. Restrict the length of the replacement word
		strncpy0(encoded_ph,phonetic,N_WORD_BYTES-4);
	}
	else
	{
		EncodePhonemes(phonetic,encoded_ph,bad_phoneme);
		if(strchr(encoded_ph,phonSWITCH) != 0)
		{
			flag_codes[n_flag_codes++] = BITNUM_FLAG_ONLY_S;  // don't match on suffixes (except 's') when switching languages
		}

		// check for errors in the phonemes codes
		for(ix=0; ix<sizeof(encoded_ph); ix++)
		{
			c = encoded_ph[ix];
			if(c == 0)   break;
		
			if(c == 255)
			{
				/* unrecognised phoneme, report error */
				fprintf(f_log,"%5d: Bad phoneme [%c] (0x%x) in: %s  %s\n",linenum,bad_phoneme[0],bad_phoneme[0],word,phonetic);
				error_count++;
			}
		}
	}

	if(sscanf(word,"U+%x",&wc) == 1)
	{
		// Character code
		ix = utf8_out(wc, word);
		word[ix] = 0;
	}
	else
	if(word[0] != '_')
	{
		// convert to lower case, and note if the word is all-capitals
		int c2;

		all_upper_case = 1;
		p = word;
		for(p=word;;)
		{
			// this assumes that the lower case char is the same length as the upper case char
			// OK, except for Turkish "I", but use towlower() rather than towlower2()
			ix = utf8_in(&c2,p);
			if(c2 == 0)
				break;
			if(iswupper(c2))
			{
				utf8_out(towlower(c2),p);
			}
			else
			{
				all_upper_case = 0;
			}
			p += ix;
		}
		if(all_upper_case)
		{
			flag_codes[n_flag_codes++] = BITNUM_FLAG_ALLCAPS;
		}
	}

	len_word = strlen(word);

	if(transpose_offset > 0)
	{
		len_word = TransposeAlphabet(word, transpose_offset, transpose_min, transpose_max);
	}

	*hash = HashDictionary(word);
	len_phonetic = strlen(encoded_ph);
	
	dict_line[1] = len_word;   // bit 6 indicates whether the word has been compressed
	len_word &= 0x3f;

	memcpy(&dict_line[2],word,len_word);

	if(len_phonetic == 0)
	{
		// no phonemes specified. set bit 7
		dict_line[1] |= 0x80;
		length = len_word + 2;
	}
	else
	{
		length = len_word + len_phonetic + 3;
		strcpy(&dict_line[(len_word)+2],encoded_ph);
	}
	
	for(ix=0; ix<n_flag_codes; ix++)
	{
		dict_line[ix+length] = flag_codes[ix];
	}
	length += n_flag_codes;

	if((multiple_string != NULL) && (multiple_words > 0))
	{
		if(multiple_words > 10)
		{
			fprintf(f_log,"%5d: Two many parts in a multi-word entry: %d\n",linenum,multiple_words);
		}
		else
		{
			dict_line[length++] = 80 + multiple_words;
			ix = multiple_string_end - multiple_string;
			memcpy(&dict_line[length],multiple_string,ix);
			length += ix;
		}
	}
	dict_line[0] = length;

#ifdef OPT_FORMAT
	spaces = 16;
	for(ix=0; ix<n_flag_codes; ix++)
	{
		if(flag_codes[ix] >= 100)
		{
			fprintf(f_log,"?%d ",flag_codes[ix]-100);
			spaces -= 3;
		}
	}

	fprintf(f_log,"%s",word);
	spaces -= strlen(word);
	DecodePhonemes(encoded_ph,decoded_ph);
	while(spaces-- > 0) fputc(' ',f_log);
	spaces += (14 - strlen(decoded_ph));
	
	fprintf(f_log," %s",decoded_ph);
	while(spaces-- > 0) fputc(' ',f_log);
	for(ix=0; ix<n_flag_codes; ix++)
	{
		if(flag_codes[ix] < 100)
			fprintf(f_log," %s",lookup_mnem(mnem_flags,flag_codes[ix]));
	}
	if(comment != NULL)
		fprintf(f_log," %s",comment);
	else
		fputc('\n',f_log);
#endif

	return(length);
}  /* end of compile_line */