int
readSyms(void)
{
	int i;
	int count = 0;
	int	firstSym = 0;			/* First symbol this module */
	byte b, c, type;
	word w, len;

	codeLNAMES = NONE;			/* Invalidate indexes for code segment */
	codeSEGDEF = NONE;			/* Else won't be assigned */

    offset = 0;                 /* For diagnostics, really */

	if ((keys = (HASHENTRY *)malloc(SYMALLOC * sizeof(HASHENTRY))) == 0)
	{
		printf("Could not malloc the initial %d entries for keys[]\n");
		exit(10);
	}

	if ((leData = (byte *)malloc(0xFF80)) == 0)
	{
		printf("Could not malloc 64k bytes for LEDATA\n"); 
		exit(10);
	}
#if 0
	switch(_heapchk())
	{
		case _HEAPBADBEGIN:
			printf("Bad begin\n");
			break;
		case _HEAPBADNODE:
			printf("Bad node\n");
			break;
		case _HEAPEMPTY:
			printf("Bad empty\n");
			break;
		case _HEAPOK:
			printf("Heap OK\n");
			break;
	}
#endif

	while (!feof(f))
	{
		type = readByte();
		len = readWord();
/* Note: uncommenting the following generates a *lot* of output */
/*printf("Offset %05lX: type %02X len %d\n", offset-3, type, len);/**/
		switch (type)
		{

			case 0x96:				/* LNAMES */
				while (len > 1)
				{
				 	readString();
					++lnum;
					if (strcmp(buf, "CODE") == 0)
					{
						/* This is the class name we're looking for */
						codeLNAMES= lnum;
					}
					len -= strlen(buf)+1;
				}
				b = readByte();		/* Checksum */
				break;

			case 0x98:				/* Segment definition */
				b = readByte();		/* Segment attributes */
				if ((b & 0xE0) == 0)
				{
					/* Alignment field is zero. Frame and offset follow */
					readWord();
					readByte();
				}

				w = readWord();		/* Segment length */

				b = readByte();		/* Segment name index */
				++segnum;

				b = readByte();		/* Class name index */
				if ((b == codeLNAMES) && (codeSEGDEF == NONE))
				{
					/* This is the segment defining the code class */
					codeSEGDEF = segnum;
				}

				b = readByte();		/* Overlay index */
				b = readByte();		/* Checksum */
				break;

			case 0x90:				/* PUBDEF: public symbols */
				b = readByte();		/* Base group */
				c = readByte();		/* Base segment */
				len -= 2;
				if (c == 0)
				{
					w = readWord();
					len -= 2;
				}
				while (len > 1)
				{
					readString();
					w = readWord();		/* Offset */
					b = readByte();		/* Type index */
					if (c == codeSEGDEF)
					{
						byte *p;

						allocSym(count);
						p = buf;
						if (buf[0] == '_')	/* Leading underscore? */
						{
							p++; 			/* Yes, remove it*/
						}
						i = MIN(SYMLEN-1, strlen(p));
						memcpy(keys[count].name, p, i);
						keys[count].name[i] = '\0';
						keys[count].offset = w;
/*printf("%04X: %s is sym #%d\n", w, keys[count].name, count);/**/
						count++;
					}
					len -= strlen(buf) + 1 + 2 + 1;
				}
				b = readByte();		/* Checksum */
				break;


			case 0xA0:				/* LEDATA */
			{
				b = readByte();		/* Segment index */
				w = readWord();		/* Offset */
				len -= 3;
/*printf("LEDATA seg %d off %02X len %Xh, looking for %d\n", b, w, len-1, codeSEGDEF);/**/

				if (b != codeSEGDEF)
				{
					readNN(len);	/* Skip the data */
					break;			/* Next record */
				}


				if (fread(&leData[w], 1, len-1, f) != len-1)
				{
					printf("Could not read LEDATA length %d\n", len-1);
					exit(2);
				}
				offset += len-1;
				maxLeData = MAX(maxLeData, w+len-1);

			 	readByte();				/* Checksum */
				break;
			}

			default:
				readNN(len);			/* Just skip the lot */

				if (type == 0x8A)	/* Mod end */
				{
				/* Now find all the patterns for public code symbols that
					we have found */
					for (i=firstSym; i < count; i++)
					{
						word off = keys[i].offset;
						if (off == (word)-1)
						{
							continue;			/* Ignore if already done */
						}
						if (keys[i].offset > maxLeData)
						{
							printf(
							"Warning: no LEDATA for symbol #%d %s "
							"(offset %04X, max %04X)\n",
							i, keys[i].name, off, maxLeData);
							/* To make things consistant, we set the pattern for
								this symbol to nulls */
							memset(&keys[i].pat, 0, PATLEN);
							continue;
						}
						/* Copy to temp buffer so don't overrun later patterns.
							(e.g. when chopping a short pattern).
							Beware of short patterns! */
						if (off+PATLEN <= maxLeData)
						{
							/* Available pattern is >= PATLEN */
							memcpy(buf, &leData[off], PATLEN);
						}
						else
						{
							/* Short! Only copy what is available (and malloced!) */
							memcpy(buf, &leData[off], maxLeData-off);
							/* Set rest to zeroes */
							memset(&buf[maxLeData-off], 0, PATLEN-(maxLeData-off));
						}
						fixWildCards(buf);
						/* Save into the hash entry. */
						memcpy(keys[i].pat, buf, PATLEN);
						keys[i].offset = (word)-1;	/* Flag it as done */
/*printf("Saved pattern for %s\n", keys[i].name);/**/
					}


					while (readByte() == 0);
					readNN(-1);			/* Unget the last byte (= type) */
					lnum = 0;			/* Reset index into lnames */
					segnum = 0;			/* Reset index into snames */
					firstSym = count;	/* Remember index of first sym this mod */
					codeLNAMES = NONE;	/* Invalidate indexes for code segment */
					codeSEGDEF = NONE;
					memset(leData, 0, maxLeData);	/* Clear out old junk */
					maxLeData = 0;		/* No data read this module */
				}

				else if (type == 0xF1)
				{
					/* Library end record */
					return count;
				}

		}
	}


	free(leData);
	free(keys);

	return count;
}