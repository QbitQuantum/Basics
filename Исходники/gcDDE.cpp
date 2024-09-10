HDDEDATA gcDDEConnection::handlePoke(HSZ hszItem, HDDEDATA hData)
{
	char item_name[255];
	GetDDEManager()->stringFromAtom(hszItem, item_name, 255);

	if (!hData)
	{
		onPoke(item_name, nullptr, 0);
		return (HDDEDATA)DDE_FACK;
	}

	DWORD len = DdeGetData(hData, nullptr, 0, 0);

	if (len == 0)
	{
		onPoke(item_name, nullptr, 0);
		return (HDDEDATA)DDE_FACK;
	}

	char *data = new char[len+1];

	DdeGetData(hData, (LPBYTE)data, len, 0);
	data[len] = '\0';

	DdeFreeDataHandle(hData);

	if (len > 0)
	{
		int x = len-1;
		while ( x+1 )
		{
			if (data[x] == '\r' || data[x] == '\n')
			{
				data[x] = '\0'; 
				len--;
			}
			else
			{
				break;
			}

			x--;
		}
	}

	char f = data[0];
	char l = data[len-1];

	//if it has " " around it remove them
	if (f == 34 && l == 34)
	{
		for (size_t x=0; x<(len-2); x++)
		{
			data[x]=data[x+1];
		}

		data[len-2]='\0';
	}

	size_t size = strlen((char*)data);
	onPoke(item_name, (char*)data, size);

	safe_delete(data);
	return (HDDEDATA)DDE_FACK;
}