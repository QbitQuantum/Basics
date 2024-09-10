static void initialize_file_info(PFileVar fv, PYVar yv)
{
	if (yv->YMode == IdYSend) {
		if (fv->FileOpen) {
			_lclose(fv->FileHandle);

			if (fv->FileMtime > 0) {
				SetFMtime(fv->FullName, fv->FileMtime);
			}
		}
		fv->FileHandle = _lopen(fv->FullName,OF_READ);
		fv->FileSize = GetFSize(fv->FullName);
	} else {
		fv->FileHandle = -1;
		fv->FileSize = 0;
		fv->FileMtime = 0;
		yv->RecvFilesize = FALSE;
	}
	fv->FileOpen = fv->FileHandle>0;

	if (yv->YMode == IdYSend) {
		InitDlgProgress(fv->HWin, IDC_PROTOPROGRESS, &fv->ProgStat);
	} else {
		fv->ProgStat = -1;
	}
	fv->StartTime = GetTickCount();
	SetDlgItemText(fv->HWin, IDC_PROTOFNAME, &(fv->FullName[fv->DirLen]));

	yv->PktNumOffset = 0;
	yv->PktNum = 0;
	yv->PktNumSent = 0;
	yv->PktBufCount = 0;
	yv->CRRecv = FALSE;
	fv->ByteCount = 0;
	yv->SendFileInfo = 0;
	yv->SendEot = 0;
	yv->LastSendEot = 0;
	yv->LastMessage = 0;
}