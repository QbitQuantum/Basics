bool DumpProcess(DWORD pid)
{
	gMemSnap = new MemorySnapshot;
	char filename[1024];
	OPENFILENAME ofln;

	memset(&filename, 0, sizeof(filename));
	memset(&ofln, 0, sizeof(OPENFILENAME));
	ofln.lStructSize = sizeof(OPENFILENAME);
	ofln.hwndOwner = gHWND;
	ofln.lpstrFile = filename;
	ofln.nMaxFile = sizeof(filename);
	ofln.lpstrFilter = "snap\0*.snap\0All\0*.*\0";
	ofln.nFilterIndex = 1;
	ofln.lpstrFileTitle = NULL;
	ofln.nMaxFileTitle = 0;
	ofln.lpstrInitialDir = NULL;
	ofln.lpstrDefExt = ".snap";
	ofln.Flags = OFN_PATHMUSTEXIST | OFN_OVERWRITEPROMPT;
	GetSaveFileName(&ofln);
	CommDlgExtendedError();
	return gMemSnap->Dump(pid, filename);
}