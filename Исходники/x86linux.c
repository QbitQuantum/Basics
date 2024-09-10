void DefineFloatConstant(Symbol p)
{
	int align = p->ty->align;

	p->aname = FormatName(".flt%d", FloatNum++);
	
	Align(p);
	Print("%s:\t", p->aname);
	DefineValue(p->ty, p->val);
}