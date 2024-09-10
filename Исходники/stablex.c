yylex(){
int nstr; extern int yyprevious;
#ifdef __cplusplus
/* to avoid CC and lint complaining yyfussy not being used ...*/
static int __lex_hack = 0;
if (__lex_hack) goto yyfussy;
#endif
while((nstr = yylook()) >= 0)
yyfussy: switch(nstr){
case 0:
if(yywrap()) return(0); break;
case 1:

# line 35 "stab.l"
MYECHO;
break;
case 2:

# line 36 "stab.l"
MYECHO;
break;
case 3:

# line 37 "stab.l"
	{
		MYECHO;
		YYDUMP();
		strcpy(yylval.string, yytext);
		if (strlen(yytext) == 1)
			return(*yytext);
		else
			return(NAME);
		}
break;
case 4:

# line 46 "stab.l"
GETTOKEN(STRING);
break;
case 5:

# line 47 "stab.l"
	GETTOKEN(REAL);
break;
case 6:

# line 48 "stab.l"
GETTOKEN(INTEGER);
break;
case 7:

# line 49 "stab.l"
GETTOKEN(HEXADECIMAL);
break;
case 8:

# line 50 "stab.l"
	{
		MYECHO;
		YYDUMP();
		strcpy(yylval.string, yytext);
		return(*yytext);
		}
break;
case -1:
break;
default:
(void)fprintf(yyout,"bad switch yylook %d",nstr);
} return(0); }