GPrintDC::GPrintDC(void *Handle, const char *PrintJobName, const char *PrinterName)
{
	d = new GPrintDCPrivate;
	hDC = (HDC) Handle;

	SetAbortProc(hDC, LgiAbortProc);
	
	// Start document
	if (hDC)
	{
		DOCINFO Info;

		ZeroObj(Info);
		Info.cbSize = sizeof(DOCINFO); 
		Info.lpszDocName = PrintJobName ? PrintJobName : "Lgi Print Job";
		
		if (PrinterName &&
			stristr(PrinterName, "XPS"))
		{
			GFile::Path p(LSP_USER_DOCUMENTS);
			GString FileName;
			FileName.Printf("%s.xps", PrintJobName);
			p += FileName;
			if (FileExists(p.GetFull()))
			{
				for (unsigned i=1; i<1000; i++)
				{
					p.Parent();
					FileName.Printf("%s%i.xps", PrintJobName, i);
					p += FileName;
					if (!FileExists(p.GetFull()))
						break;
				}
			}
			
			Info.lpszOutput = d->OutputFileName = p.GetFull();
		}

		d->DocOpen = StartDoc(hDC, &Info) > 0;
		if (!d->DocOpen)
		{
			DeleteDC(hDC);
			hDC = 0;
		}
	}
}