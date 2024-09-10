void DefineCommData(Symbol p)
{
	Align(p);
	GetAccessName(p);
	if (p->sclass == TK_STATIC)
	{
		Print("%s\t", p->aname);
		Space(p->ty->size);
	}
	else
	{
		Print("COMM\t%s:%d\n", p->aname, p->ty->size);
	}
}