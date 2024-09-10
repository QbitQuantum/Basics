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

# line 36 "prop.l"
ECHO;
break;
case 2:

# line 37 "prop.l"
	ECHO;
break;
case 3:

# line 38 "prop.l"
GETTOKEN(NEWLINE);
break;
case 4:

# line 39 "prop.l"
	GETTOKEN(THEREFORE);
break;
case 5:

# line 40 "prop.l"
	GETTOKEN(BICONDITIONAL);
break;
case 6:

# line 41 "prop.l"
	GETTOKEN(IMPLICATION);
break;
case 7:

# line 42 "prop.l"
	GETTOKEN(OR);
break;
case 8:

# line 43 "prop.l"
	GETTOKEN(AND);
break;
case 9:

# line 44 "prop.l"
	GETTOKEN(NEGATION);
break;
case 10:

# line 45 "prop.l"
	GETTOKEN(LPAREN);
break;
case 11:

# line 46 "prop.l"
	GETTOKEN(RPAREN);
break;
case 12:

# line 47 "prop.l"
	GETTOKEN(COMMA);
break;
case 13:

# line 48 "prop.l"
	GETTOKEN(SEMICOLON);
break;
case 14:

# line 49 "prop.l"
	GETTOKEN(QUIT);
break;
case 15:

# line 50 "prop.l"
	GETTOKEN(TRUE);
break;
case 16:

# line 51 "prop.l"
	GETTOKEN(FALSE);
break;
case 17:

# line 52 "prop.l"
GETTOKEN(IDENTIFIER);
break;
case 18:

# line 53 "prop.l"
	{
		ECHO;
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