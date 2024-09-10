/* read toc */
static int ioctl_command_toc2 (int unitnum, struct cd_toc_head *tocout, bool hide_errors)
{
	struct dev_info_ioctl *ciw = unitisopen (unitnum);
	if (!ciw)
		return 0;

	DWORD len;
	int i;
	struct cd_toc_head *th = &ciw->di.toc;
	struct cd_toc *t = th->toc;
	int cnt = 3;
	CDROM_TOC *toc = &ciw->cdromtoc;

	if (!unitisopen (unitnum))
		return 0;

	if (!open_createfile (ciw, 0))
		return 0;
	while (cnt-- > 0) {
		seterrormode (ciw);
		if (!DeviceIoControl (ciw->h, IOCTL_CDROM_READ_TOC, NULL, 0, toc, sizeof (CDROM_TOC), &len, NULL)) {
			DWORD err = GetLastError ();
			reseterrormode (ciw);
			if (!hide_errors || (hide_errors && err == ERROR_WRONG_DISK)) {
				if (win32_error (ciw, unitnum, _T("IOCTL_CDROM_READ_TOC")) < 0)
					continue;
			}
			return 0;
		}
		reseterrormode (ciw);
		break;
	}

	memset (th, 0, sizeof (struct cd_toc_head));
	th->first_track = toc->FirstTrack;
	th->last_track = toc->LastTrack;
	th->tracks = th->last_track - th->first_track + 1;
	th->points = th->tracks + 3;
	th->firstaddress = 0;
	th->lastaddress = msf2lsn ((toc->TrackData[toc->LastTrack].Address[1] << 16) | (toc->TrackData[toc->LastTrack].Address[2] << 8) |
		(toc->TrackData[toc->LastTrack].Address[3] << 0));

	t->adr = 1;
	t->point = 0xa0;
	t->track = th->first_track;
	t++;

	th->first_track_offset = 1;
	for (i = 0; i < toc->LastTrack; i++) {
		t->adr = toc->TrackData[i].Adr;
		t->control = toc->TrackData[i].Control;
		t->paddress = msf2lsn ((toc->TrackData[i].Address[1] << 16) | (toc->TrackData[i].Address[2] << 8) |
			(toc->TrackData[i].Address[3] << 0));
		t->point = t->track = i + 1;
		t++;
	}

	th->last_track_offset = toc->LastTrack;
	t->adr = 1;
	t->point = 0xa1;
	t->track = th->last_track;
	t++;

	t->adr = 1;
	t->point = 0xa2;
	t->paddress = th->lastaddress;
	t++;

	memcpy (tocout, th, sizeof (struct cd_toc_head));
	return 1;
}