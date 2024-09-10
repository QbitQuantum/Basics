char scan(Scanner *s)
{
	int cond = 1;
	
	fill(s, 0);

	for(;;)
	{
		s->tok = s->cur;

#line 59 "<stdout>"
		{
			unsigned char yych;
			static void *yyctable[2] = {
				&&yyc_normal,
				&&yyc_comment,
			};
			goto *yyctable[cond];
/* *********************************** */
yyc_comment:

			if ((s->lim - s->cur) < 2) { if(fill(s, 2) >= 0) break; }
			yych = *s->cur;
			if (yych != '*') goto yy4;
			++s->cur;
			if ((yych = *s->cur) == '/') goto yy5;
yy3:
#line 83 "condition_05.cg.re"
			{
				goto yyc_comment;
			}
#line 80 "<stdout>"
yy4:
			yych = *++s->cur;
			goto yy3;
yy5:
			++s->cur;
#line 79 "condition_05.cg.re"
			{
				continue;
			}
#line 90 "<stdout>"
/* *********************************** */
yyc_normal:
			if ((s->lim - s->cur) < 2) { if(fill(s, 2) >= 0) break; }
			yych = *s->cur;
			if (yych != '/') goto yy11;
			++s->cur;
			if ((yych = *s->cur) == '*') goto yy12;
yy10:
#line 74 "condition_05.cg.re"
			{
				fputc(*s->tok, stdout);
				continue;
			}
#line 104 "<stdout>"
yy11:
			yych = *++s->cur;
			goto yy10;
yy12:
			++s->cur;
#line 70 "condition_05.cg.re"
			{
				goto yyc_comment;
			}
#line 114 "<stdout>"
		}
#line 87 "condition_05.cg.re"

	}
}

int main(int argc, char **argv)
{
	Scanner in;
	char c;

	if (argc != 2)
	{
		fprintf(stderr, "%s <file>\n", argv[0]);
		return 1;;
	}

	memset((char*) &in, 0, sizeof(in));

	if (!strcmp(argv[1], "-"))
	{
		in.fp = stdin;
	}
	else if ((in.fp = fopen(argv[1], "r")) == NULL)
	{
		fprintf(stderr, "Cannot open file '%s'\n", argv[1]);
		return 1;
	}

	scan(&in);

	if (in.fp != stdin)
	{
		fclose(in.fp);
	}
	return 0;
}