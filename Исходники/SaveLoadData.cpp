void LoadData::Do(HWND h)
{
	OpenData o(h);
	if(o())
	{
		FILE *f = _wfopen(o.sFile, L"rb");
		close_file c_f(f);
		if(NULL != f)
		{
			HeadStoredData head;
			if(1 == fread(&head, sizeof(head), 1, f))
			{
				primaryData.countZones = head.countZones;
				fread(primaryData.realOffsetTime, sizeof(primaryData.realOffsetTime), 1, f);
				int count = fread(primaryData.indexOffsetZone, sizeof(primaryData.indexOffsetZone), 1, f);
				primaryData.frameStartTime = head.frameStartTime;
				char buf[1024 * 16];
				int k = 0;
				for(;;)
				{
					int count = fread(buf, 1, sizeof(buf), f);
					if(0 == count) break;
					{
						for(int i = 0; i < count; ++i)
						{
							primaryData.buffer[k++] = buf[i];
						}
					}
				}
				primaryData.SetCurrentOffset(k);
				if(k)
				{					
					Recalculation::Do(NULL);
					return;
				}
			}
		}
		MessageBox(0, L"‘айл не загружен", L"ќшибка !!!", MB_ICONERROR);
	}	
}