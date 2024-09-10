// Interface comparison function
int CmpL3If(void *p1, void *p2)
{
	L3IF *f1, *f2;
	if (p1 == NULL || p2 == NULL)
	{
		return 0;
	}
	f1 = *(L3IF **)p1;
	f2 = *(L3IF **)p2;
	if (f1 == NULL || f2 == NULL)
	{
		return 0;
	}

	return StrCmpi(f1->HubName, f2->HubName);
}