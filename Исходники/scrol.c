static char*
tkscrollidentify(Tk *tk, char *arg, char **val)
{
	int gotarg;
	TkTop *t;
	char *v, buf[Tkmaxitem];
	Point p;
	TkScroll *tks = TKobj(TkScroll, tk);

	t = tk->env->top;
	arg = tkword(t, arg, buf, buf+sizeof(buf), &gotarg);
	if (!gotarg)
		return TkBadvl;
	p.x = atoi(buf);
	tkword(t, arg, buf, buf+sizeof(buf), &gotarg);
	if (!gotarg)
		return TkBadvl;
	p.y = atoi(buf);
	if (!ptinrect(p, tkrect(tk, 0)))
		return nil;
	if (tks->orient == Tkvertical)
		p.x = p.y;
	p.x += tk->borderwidth;

	v = "";
	if(p.x <= tks->a1)
		v = "arrow1";
	if(p.x > tks->a1 && p.x <= tks->t1)
		v = "trough1";
	if(p.x > tks->t1 && p.x < tks->t2)
		v = "slider";
	if(p.x >= tks->t2 && p.x < tks->a2)
		v = "trough2";
	if(p.x >= tks->a2)
		v = "arrow2";
	return tkvalue(val, "%s", v);
}