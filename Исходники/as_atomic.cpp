asDWORD asCAtomic::atomicDec()
{
	asDWORD v;
	ENTERCRITICALSECTION(cs);
	v = --value;
	LEAVECRITICALSECTION(cs);
	return v;
}