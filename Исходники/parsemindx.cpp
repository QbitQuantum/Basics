/*
 * DoCalc
 */
void DoCalc(char *a, char *b)
{
	if (strstr(b, "+rw1"))
	{
		for (int i=0; i<6; i++)
		{
			char tmp_a[BUFSIZE]; strcpy(tmp_a, a); strreplace(tmp_a, "rw1", rw[i]);
			char tmp_b[BUFSIZE]; strcpy(tmp_b, b); strreplacenum(tmp_b, "rw1", rwnum[i]);
			DoCalc(tmp_a, tmp_b);
		}
	}
	else
	if (strstr(b, "+rw2"))
	{
		for (int i=0; i<6; i++)
		{
			char tmp_a[BUFSIZE]; strcpy(tmp_a, a); strreplace(tmp_a, "rw2", rw[i]);
			char tmp_b[BUFSIZE]; strcpy(tmp_b, b); strreplacenum(tmp_b, "rw2", rwnum[i]);
			DoCalc(tmp_a, tmp_b);
		}
	}
	else
	if (strstr(b, "+rw"))
	{
		for (int i=0; i<6; i++)
		{
			char tmp_a[BUFSIZE]; strcpy(tmp_a, a); strreplace(tmp_a, "rw", rw[i]);
			char tmp_b[BUFSIZE]; strcpy(tmp_b, b); strreplacenum(tmp_b, "rw", rwnum[i]);
			DoCalc(tmp_a, tmp_b);
		}
	}
	else
	if (strstr(b, "+rb1"))
	{
		for (int i=0; i<4; i++)
		{
			char tmp_a[BUFSIZE]; strcpy(tmp_a, a); strreplace(tmp_a, "rb1", rb[i]);
			char tmp_b[BUFSIZE]; strcpy(tmp_b, b); strreplacenum(tmp_b, "rb1", i);
			DoCalc(tmp_a, tmp_b);
		}
	}
	else
	if (strstr(b, "+rb2"))
	{
		for (int i=0; i<4; i++)
		{
			char tmp_a[BUFSIZE]; strcpy(tmp_a, a); strreplace(tmp_a, "rb2", rb[i]);
			char tmp_b[BUFSIZE]; strcpy(tmp_b, b); strreplacenum(tmp_b, "rb2", i);
			DoCalc(tmp_a, tmp_b);
		}
	}
	else
	if (strstr(b, "+rb"))
	{
		for (int i=0; i<4; i++)
		{
			char tmp_a[BUFSIZE]; strcpy(tmp_a, a); strreplace(tmp_a, "rb", rb[i]);
			char tmp_b[BUFSIZE]; strcpy(tmp_b, b); strreplacenum(tmp_b, "rb", i);
			DoCalc(tmp_a, tmp_b);
		}
	}
	else
	{	
	//fprintf(stderr, "1 %s %s\n", a, b);
		strshift(b);
	//fprintf(stderr, "2 %s %s\n", a, b);
		stradd(b);
	//fprintf(stderr, "3 %s %s\n", a, b);
		STRUPR(a);

		strtrimtrailing(a);
		strtrimtrailing(b);

		int numargs = 0;
		if (strreplace(a, "*", "~0")) numargs++;
		if (strreplace(a, "*", "~1")) numargs++;
		if (strreplace(a, "*", "~2")) numargs++;
		// .....

		//strreplace(b, ":", "");

		instruction.fmt = a;

		//instruction.opcode = strtoul(b,0,16);
		//instruction.fixed |= strtoul(b,0,16) << ((instruction.flags & FLAG_EXTENDED) ? 1 : 0);
		unsigned int instruction_fixed = instruction.fixed | (strtoul(b,0,16) << ((instruction.flags & FLAG_EXTENDED) ? 8 : 0));

		// no continue flag
		if (!(instruction.flags & FLAG_EXTENDED)) switch (instruction.fixed & 0xFF)
		{
			case 0xF1:
			case 0xF3:
			case 0xF4:
			case 0xF8:
			case 0xF9:
				break;

			default:
				instruction.flags |= FLAG_CONT;
		}

		char s[BUFSIZE], *p = s;

		// NOTE: leading text is added later
		// see mindx_type.h for structure fields
		p += sprintf(p, "%s\"", instruction.fmt);
		//for (int i=0; i<30-(p-s); i++) { p += sprintf(p, " "); }
		p += sprintf(p, ",0x%02X,0x%02X,%d,%d", instruction.flags, instruction_fixed, instruction.size, instruction.argnum);
		for (unsigned int i=0; i<instruction.argnum; i++)
		{
			p += sprintf(p, ",%d,%d", instruction.argInfo[i].shift, instruction.argInfo[i].flags);
		}
		p += sprintf(p, "\t; %d\n", line);


/*		p += sprintf(p, "%s\",0x%02X,0x%02X,0x%02X,%d,%d,%d,{", instruction.fmt, instruction.flags, instruction.extended, instruction.opcode, instruction.size, instruction.argnum, instruction.argbytes);
		for (int i=0; i<MAX_ARGS; i++)
		{
			p += sprintf(p, "0x%03X,", instruction.argflags[i]);
		}
		//%d,%d",  flags, numargs,
		p += sprintf(p, "}},//%d\n", line);
*/
		output[outputs++] = strdup(s);		// this is going to be sorted alphabetically
	}
}