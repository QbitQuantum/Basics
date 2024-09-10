Arg *
parse(Rune *s)
{
	Arg *a;
	Rune *p;

	p = Strchr(s, ':');
	if (p == nil)
		sysfatal("`%S' no colon", s);
	*p = '\0';
	a = emalloc(sizeof(*a));
	a->name = convert(s);
	a->val = convert(p+1);
	a->next = nil;
	return a;
}