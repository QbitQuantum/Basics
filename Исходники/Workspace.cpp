String RemoveType(Vector<String>& conf, const char *flags)
{
	String old;
	Index<String> f(SplitFlags(flags));
	for(int i = conf.GetCount(); --i >= 0;)
		if(f.Find(conf[i]) >= 0)
		{
			old = conf[i];
			conf.Remove(i);
		}
	return old;
}