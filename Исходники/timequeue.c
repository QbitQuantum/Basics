void
envpropqueue(int descr, dbref player, dbref where, dbref trigger, dbref what, dbref xclude,
			 const char *propname, const char *toparg, int mlev, int mt)
{
	while (what != NOTHING) {
		propqueue(descr, player, where, trigger, what, xclude, propname, toparg, mlev, mt);
		what = getparent(what);
	}
}