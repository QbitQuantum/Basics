static void DoParse(const char *filename)
{
	if (TokenMap.CountUsed() == 0)
	{
		InitTokenMap();
	}

	FScanner sc;
	void *parser;
	int tokentype;
	int lump;
	bool failed;
	ZCCToken value;

	lump = Wads.CheckNumForFullName(filename, true);
	if (lump >= 0)
	{
		sc.OpenLumpNum(lump);
	}
	else if (FileExists(filename))
	{
		sc.OpenFile(filename);
	}
	else
	{
		Printf("Could not find script lump '%s'\n", filename);
		return;
	}
	
	parser = ZCCParseAlloc(malloc);
	failed = false;
#ifdef _DEBUG
	FILE *f = fopen("trace.txt", "w");
	char prompt = '\0';
	ZCCParseTrace(f, &prompt);
#endif
	ZCCParseState state(sc);

	while (sc.GetToken())
	{
		value.SourceLoc = sc.GetMessageLine();
		switch (sc.TokenType)
		{
		case TK_StringConst:
			value.String = state.Strings.Alloc(sc.String, sc.StringLen);
			tokentype = ZCC_STRCONST;
			break;

		case TK_NameConst:
			value.Int = sc.Name;
			tokentype = ZCC_NAMECONST;
			break;

		case TK_IntConst:
			value.Int = sc.Number;
			tokentype = ZCC_INTCONST;
			break;

		case TK_UIntConst:
			value.Int = sc.Number;
			tokentype = ZCC_UINTCONST;
			break;

		case TK_FloatConst:
			value.Float = sc.Float;
			tokentype = ZCC_FLOATCONST;
			break;

		case TK_Identifier:
			value.Int = FName(sc.String);
			tokentype = ZCC_IDENTIFIER;
			break;

		case TK_NonWhitespace:
			value.Int = FName(sc.String);
			tokentype = ZCC_NWS;
			break;

		default:
			TokenMapEntry *zcctoken = TokenMap.CheckKey(sc.TokenType);
			if (zcctoken != NULL)
			{
				tokentype = zcctoken->TokenType;
				value.Int = zcctoken->TokenName;
			}
			else
			{
				sc.ScriptMessage("Unexpected token %s.\n", sc.TokenName(sc.TokenType).GetChars());
				goto parse_end;
			}
			break;
		}
		ZCCParse(parser, tokentype, value, &state);
		if (failed)
		{
			sc.ScriptMessage("Parse failed\n");
			goto parse_end;
		}
	}
parse_end:
	value.Int = -1;
	ZCCParse(parser, ZCC_EOF, value, &state);
	ZCCParse(parser, 0, value, &state);
	ZCCParseFree(parser, free);

	PSymbolTable symbols(&GlobalSymbols);
	ZCCCompiler cc(state, NULL, symbols);
	cc.Compile();
#ifdef _DEBUG
	if (f != NULL)
	{
		fclose(f);
	}
	FString ast = ZCC_PrintAST(state.TopNode);
	FString astfile = ExtractFileBase(filename, false);
	astfile << ".ast";
	f = fopen(astfile, "w");
	if (f != NULL)
	{
		fputs(ast.GetChars(), f);
		fclose(f);
	}
#endif
}