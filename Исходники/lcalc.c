struct symbol *parser( )
{
register struct symbol *psym;
register char *pline;
struct varent *pvar;
struct strent *pstr;
char *cp, *plc, *pn;
long lnc;
int i;
long double tem;

/* reference for old Whitesmiths compiler: */
/*
 *extern FILE *stdout;
 */

pline = interl;		/* get current location in command string	*/


/*	If at beginning of string, must ask for more input	*/
if( pline == line )
	{

	if( maccnt > 0 )
		{
		--maccnt;
		cp = maclin;
		plc = pline;
		while( (*plc++ = *cp++) != 0 )
			;
		goto mstart;
		}
	if( takptr < 0 )
		{	/* no take file active: prompt keyboard input */
		printf("* ");
		}
/* 	Various ways of typing in a command line. */

/*
 * Old Whitesmiths call to print "*" immediately
 * use RT11 .GTLIN to get command string
 * from command file or terminal
 */

/*
 *	fflush(stdout);
 *	gtlin(line);
 */

 
	zgets( line, TRUE );	/* keyboard input for other systems: */


mstart:
	uposs = 1;	/* unary operators possible at start of line */
	}

ignore:
/* Skip over spaces */
while( *pline == ' ' )
	++pline;

/* unary minus after operator */
if( uposs && (*pline == '-') )
	{
	psym = &oprtbl[2];	/* UMINUS */
	++pline;
	goto pdon3;
	}
	/* COMP */
/*
if( uposs && (*pline == '~') )
	{
	psym = &oprtbl[3];
	++pline;
	goto pdon3;
	}
*/
if( uposs && (*pline == '+') )	/* ignore leading plus sign */
	{
	++pline;
	goto ignore;
	}

/* end of null terminated input */
if( (*pline == '\n') || (*pline == '\0') || (*pline == '\r') )
	{
	pline = line;
	goto endlin;
	}
if( *pline == ';' )
	{
	++pline;
endlin:
	psym = &oprtbl[1];	/* EOL */
	goto pdon2;
	}


/*						parser()	*/


/* Test for numeric input */
if( (ISDIGIT(*pline)) || (*pline == '.') )
	{
	lnc = 0;	/* initialize numeric input to zero */
	qnc = 0.0L;
	if( *pline == '0' )
		{ /* leading "0" may mean octal or hex radix */
		++pline;
		if( *pline == '.' )
			goto decimal; /* 0.ddd */
		/* leading "0x" means hexadecimal radix */
		if( (*pline == 'x') || (*pline == 'X') )
			{
			++pline;
			while( ISXDIGIT(*pline) )
				{
				i = *pline++ & 0xff;
				if( i >= 'a' )
					i -= 047;
				if( i >= 'A' )
					i -= 07;
				i -= 060;
				lnc = (lnc << 4) + i;
				qnc = lnc;
				}
			goto numdon;
			}
		else
			{
			while( ISOCTAL( *pline ) )
				{
				i = ((*pline++) & 0xff) - 060;
				lnc = (lnc << 3) + i;
				qnc = lnc;
				}
			goto numdon;
			}
		}
	else
		{
		/* no leading "0" means decimal radix */
/******/
decimal:
		pn = number;
		while( (ISDIGIT(*pline)) || (*pline == '.') )
			*pn++ = *pline++;
/* get possible exponent field */
		if( (*pline == 'e') || (*pline == 'E') )
			*pn++ = *pline++;
		else
			goto numcvt;
		if( (*pline == '-') || (*pline == '+') )
			*pn++ = *pline++;
		while( ISDIGIT(*pline) )
			*pn++ = *pline++;
numcvt:
		*pn++ = ' ';
		*pn++ = 0;
#if NE == 6
		asctoe64( number, &qnc );
#else
		asctoe113( number, &qnc );
#endif
/*		sscanf( number, "%le", &nc ); */
		}
/* output the number	*/
numdon:
	/* search the symbol table of constants 	*/
	pvar = &contbl[0];
	for( i=0; i<NCONST; i++ )
		{
		if( (pvar->attrib & BUSY) == 0 )
			goto confnd;
		tem = *pvar->value;
		if( tem == qnc )
			{
			psym = (struct symbol *)pvar;
			goto pdon2;
			}
		++pvar;
		}
	printf( "no room for constant\n" );
	psym = (struct symbol *)&contbl[0];
	goto pdon2;

confnd:
	pvar->spel= contbl[0].spel;
	pvar->attrib = CONST | BUSY;
	*pvar->value = qnc;
	psym = (struct symbol *)pvar;
	goto pdon2;
	}

/* check for operators */
psym = &oprtbl[3];
for( i=0; i<NOPR; i++ )
	{
	if( *pline == *(psym->spel) )
		goto pdon1;
	++psym;
	}

/* if quoted, it is a string variable */
if( *pline == '"' )
	{
	/* find an empty slot for the string */
	pstr = strtbl;	/* string table	*/
	for( i=0; i<NSTRNG-1; i++ ) 
		{
		if( (pstr->attrib & BUSY) == 0 )
			goto fndstr;
		++pstr;
		}
	printf( "No room for string\n" );
	pstr->attrib |= ILLEG;
	psym = (struct symbol *)pstr;
	goto pdon0;

fndstr:
	pstr->attrib |= BUSY;
	plc = pstr->string;
	++pline;
	for( i=0; i<39; i++ )
		{
		*plc++ = *pline;
		if( (*pline == '\n') || (*pline == '\0') || (*pline == '\r') )
			{
illstr:
			pstr = &strtbl[NSTRNG-1];
			pstr->attrib |= ILLEG;
			printf( "Missing string terminator\n" );
			psym = (struct symbol *)pstr;
			goto pdon0;
			}
		if( *pline++ == '"' )
			goto finstr;
		}

	goto illstr;	/* no terminator found */

finstr:
	--plc;
	*plc = '\0';
	psym = (struct symbol *)pstr;
	goto pdon2;
	}
/* If none of the above, search function and symbol tables:	*/

/* copy character string to array lc[] */
plc = &lc[0];
while( ISALPHA(*pline) )
	{
	/* convert to lower case characters */
	if( ISUPPER( *pline ) )
		*pline += 040;
	*plc++ = *pline++;
	}
*plc = 0;	/* Null terminate the output string */

/*						parser()	*/

psym = (struct symbol *)menstk[menptr];	/* function table	*/
plc = &lc[0];
cp = psym->spel;
do
	{
	if( strcmp( plc, cp ) == 0 )
		goto pdon3;	/* following unary minus is possible */
	++psym;
	cp = psym->spel;
	}
while( *cp != '\0' );

psym = (struct symbol *)&indtbl[0];	/* indirect symbol table */
plc = &lc[0];
cp = psym->spel;
do
	{
	if( strcmp( plc, cp ) == 0 )
		goto pdon2;
	++psym;
	cp = psym->spel;
	}
while( *cp != '\0' );

pdon0:
pline = line;	/* scrub line if illegal symbol */
goto pdon2;

pdon1:
++pline;
if( (psym->attrib & 0xf) == RPAREN )
pdon2:	uposs = 0;
else
pdon3:	uposs = 1;

interl = pline;
return( psym );
}		/* end of parser */