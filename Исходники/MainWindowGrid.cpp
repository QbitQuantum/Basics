void MainWindowGrid::Handlers::operator()(TCellData &l)
{
#pragma warning(disable : 4996)
	Log::TData *d = NULL;
	if(Log::IsRow(l.row, d))
	{
		switch(l.col)
		{
		case 0: 
			{
				Log::TData *d0 = NULL;
				if(Log::IsRow(l.row + 1, d0))
				{
					_itow(d->time - d0->time, l.data, 10);
				}
				else
				{
					l.data[0] = '0';
					l.data[1] = '\0';
				}
			//	dprint("row %d", l.row);
			}
			break;
		case 1:
			char buf[1024];
			LogMess::FactoryMessages::Instance().Text(d->id, buf, d->value);
			
			int len = 1 + strlen(buf);
			MultiByteToWideChar(1251, 0, buf, len, l.data, len);			
			break;
		}
	}
}