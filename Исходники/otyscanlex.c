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

# line 46 "otyscan.l"
;
break;
case 2:

# line 47 "otyscan.l"
GETTOKEN(NEWLINE);
break;
case 3:

# line 48 "otyscan.l"
	GETTOKEN(MSGID);
break;
case 4:

# line 49 "otyscan.l"
	GETTOKEN(TIME);
break;
case 5:

# line 50 "otyscan.l"
	GETTOKEN(CLASS);
break;
case 6:

# line 51 "otyscan.l"
GETTOKEN(ACTION);
break;
case 7:

# line 52 "otyscan.l"
GETTOKEN(OUTPRIOR);
break;
case 8:

# line 53 "otyscan.l"
	GETTOKEN(FREQ);
break;
case 9:

# line 54 "otyscan.l"
GETTOKEN(PROTOTYPE);
break;
case 10:

# line 55 "otyscan.l"
	GETTOKEN(FIELD);
break;
case 11:

# line 56 "otyscan.l"
GETTOKEN(FIELDUP);
break;
case 12:

# line 57 "otyscan.l"
	GETTOKEN(NPVAL);
break;
case 13:

# line 58 "otyscan.l"
	GETTOKEN(WIDTH);
break;
case 14:

# line 59 "otyscan.l"
	GETTOKEN(ENUM);
break;
case 15:

# line 60 "otyscan.l"
GETTOKEN(OUTPUT);
break;
case 16:

# line 61 "otyscan.l"
{
		YYDUMP();
		VERBOSE(stdout, "otyscan: %s", yytext+strlen("otypp: "));
		}
break;
case 17:

# line 65 "otyscan.l"
GETTOKEN(LEFTBRACE);
break;
case 18:

# line 66 "otyscan.l"
GETTOKEN(RIGHTBRACE);
break;
case -1:
break;
default:
(void)fprintf(yyout,"bad switch yylook %d",nstr);
} return(0); }