static void dolist (struct arcdir **filelist, struct arcdir *adp, int entries, int parent, int level)
{
	int ii, i;

	for (ii = 0; ii < 2; ii++) {
		for (i = 0; i < entries; i++) {
			struct arcdir *ad = filelist[i];
			int j;
			TCHAR protflags[9];
			TCHAR dates[32];
			TCHAR crcs[16];
			int flags;
			struct tm *dt;

			if (ad->parent != parent)
				continue;

			if ((ii == 0 && ad->isdir) || (ii == 1 && !ad->isdir)) {

				flags = ad->flags;

				if (flags >= 0) {
					for (j = 0; j < 8; j++) {
						protflags[j] = '-';
						if (flags & (1 << (7 - j)))
							protflags[j] = prots[j];
					}
					protflags[j] = 0;
				} else {
					_tcscpy (protflags, _T("--------"));
				}

				if (ad->dt > 0) {
					dt = _gmtime64 (&ad->dt);
					_tcsftime (dates, sizeof (dates) / sizeof (TCHAR), _T("%Y/%m/%d %H:%M:%S"), dt);
				} else {
					_tcscpy (dates, _T("-------------------"));
				}

				for (j = 0; j < level; j++)
					_tprintf (_T(" "));
				if (ad->iscrc > 0)
					_stprintf (crcs, _T("%08X"), ad->crc32);
				else if (ad->iscrc < 0)
					_tcscpy (crcs, _T("????????"));
				else
					_tcscpy (crcs, _T("--------"));
				if (ad->isdir > 0)
					_tprintf (_T("     [DIR] %s %s          %s\n"), protflags, dates, ad->name);
				else if (ad->isdir < 0)
					_tprintf (_T("    [VDIR] %s %s          %s\n"), protflags, dates, ad->name);
				else
					_tprintf (_T("%10I64d %s %s %s %s\n"), ad->size, protflags, dates, crcs, ad->name);
				if (ad->comment)
					_tprintf (_T(" \"%s\"\n"), ad->comment);
				if (ad->nextlevel >= 0) {
					level++;
					dolist (filelist, adp, entries, ad - adp, level);
					level--;
				}

			}
		}
	}
}