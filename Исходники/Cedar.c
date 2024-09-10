// Initialize net service list
void InitNetSvcList(CEDAR *cedar)
{
	char filename[MAX_PATH] = "/etc/services";
	BUF *b;
	// Validate arguments
	if (cedar == NULL)
	{
		return;
	}

#ifdef	OS_WIN32
	Format(filename, sizeof(filename), "%s\\drivers\\etc\\services", MsGetSystem32Dir());
#endif

	cedar->NetSvcList = NewList(CompareNetSvc);

	b = ReadDump(filename);
	if (b == NULL)
	{
		return;
	}

	while (true)
	{
		char *s = CfgReadNextLine(b);
		if (s == NULL)
		{
			break;
		}

		Trim(s);
		if (s[0] != '#')
		{
			TOKEN_LIST *t = ParseToken(s, " \t/");
			if (t->NumTokens >= 3)
			{
				NETSVC *n = ZeroMalloc(sizeof(NETSVC));
				n->Name = CopyStr(t->Token[0]);
				n->Udp = (StrCmpi(t->Token[2], "udp") == 0 ? true : false);
				n->Port = ToInt(t->Token[1]);
				Add(cedar->NetSvcList, n);
			}
			FreeToken(t);
		}
		Free(s);
	}

	FreeBuf(b);
}