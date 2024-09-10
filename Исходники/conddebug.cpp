// Generic function to handle all infix operators but the last one in the precedence hierarchy. : '(' E ')'
Condition* InfixOperator(const char** str, Condition(*nextPart(const char**)), int(*operators)(const char**))
{
	Condition* t = nextPart(str);
	Condition* t1;
	Condition* mid;
	int op;

	while ((op = operators(str)))
	{
		scan(str);

		t1 = nextPart(str);

		if (t1 == 0)
		{
			if(t)
				freeTree(t);
			return 0;
		}

		mid = (Condition*)FCEU_dmalloc(sizeof(Condition));
		if (!mid)
			return NULL;
		memset(mid, 0, sizeof(Condition));

		mid->lhs = t;
		mid->rhs = t1;
		mid->op = op;

		t = mid;
	}

	return t;
}