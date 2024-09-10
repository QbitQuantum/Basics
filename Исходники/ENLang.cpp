int _tmain(int argc, _TCHAR* argv[])
{
	if (!strcmp(wtoc(argv[1]), "-help"))
	{
		PrintHelp();
		system("pause");
		return 0;
	}
	//char* buffer = ReadFile(L"tempLang.txt");
	char* buffer = ReadFile(argv[1]);
	if (buffer == NULL) { printf("NO FILE!!"); return 1; }
	int countOfLexem = 0;
	lex* lexic = Lexer(buffer, &countOfLexem);

	errno_t err1 = fopen_s(&Fdotty, "E:\\C++\\Derivative\\Derivative\\dumpTree.gv", "w");
	fprintf(Fdotty, "graph graphname {");

	errno_t err2 = fopen_s(&ftrans, "FileForASM.txt", "w");

	for (int i = 0; i < countOfLexem; i++)
	{
		printf("lexem number %d :\n"
			"value <%s>\n"
			"type <%d>\n"
			"current pos <%s>\n\n", i, lexic[i].val, lexic[i].type, lexic[i].pos);
	}

	Var.vars = new char*[COUNTOFREGISTER];

	node* top = GetG0(lexic);
	if (!top) printf("SYNTAX ERROR!!!\n"
		"at this symbol %s \n", s->pos);
	s++;
	node* funcTop = GetG0(s);
	node* Main = new node;
	NODECTOR(Main, "main", T_op, top, funcTop);
	if (!top) printf("SYNTAX ERROR!!!\n"
		"at this symbol %s \n", s->pos);
	int count = 0;
	PrintTree(Main, &count);

	FILE* fout = NULL;
	errno_t err = fopen_s(&fout, "Expression.txt", "w");
	Print(Main, fout);
	DottyTree(Main);
	int countOfJump = 0, pop = 0, flag = 0;
	Translate(Main, countOfJump, &pop, flag);
	//fprintf(ftrans, "end");
	//reg regis = {};

	fprintf(Fdotty,"}");
	fclose(Fdotty);
	fclose(ftrans);
	/////////////////////////////////////////////////
	//char* FROM = "C:\\Users\\Vladimir\\Documents\\Visual Studio 2013\\Projects\\ENLang\Debug"

	/////////////////////////////////////////////////
	system("E:\\C++\\Graphviz2.38\\bin\\dotty.exe E:\\C++\\Derivative\\Derivative\\dumpTree.gv");
	system("pause");

	return 0;
}