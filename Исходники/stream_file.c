static int rar_open(char *rarname, mode_t m, stream_t *stream)
{
	stream_0day_priv_t *p;
	char RarTag[7], method, *pp, type = 0;
	WORD w, n, flag;

	int h = open(rarname, m);
	if (h < 0) return h;

	read(h, RarTag, 7);						/* Read Rar!... Tag */
	if (strncmp(RarTag, "Rar!", 4)) {
		lseek(h, 0, SEEK_SET);				/* Not a RAR */
		return h;
	}

	p = (stream_0day_priv_t*)malloc(sizeof(stream_0day_priv_t));
	memset(p, 0, sizeof(stream_0day_priv_t));
	p->headSize = 7;
	while (type != 0x74) {
		lseek(h, 2, SEEK_CUR);				/* CRC */
		read(h, &type, 1);					/* Type */
		read(h, (char*)&flag, 2);			/* Flag */
		read(h, (char*)&w, 2);				/* Size */
		p->headSize += w;
		if (type == 0x73) { /* main header */
			p->naming = flag & 0x10;
		} else
		if (type == 0x74) {	/* file header */
			read(h, (char*)&(p->packSize), 4);
			read(h, (char*)&(p->fileSize), 4);
			lseek(h, 10, SEEK_CUR);			/* Skip OS/CRC/Time/Ver */
			read(h, &method, 1);			/* Compression Method */
			read(h, (char*)&n, 2);			/* Size of rarname */
			if (w == n + 0x2D) {
				/* fileSize is 64bit */
				lseek(h, 8, SEEK_CUR);
				read(h, ((char*)&(p->fileSize))+4, 4);
			} else {
				lseek(h, 4, SEEK_CUR);		/* Attr */
			}
			p->filename = (char *)malloc(n + 1);
			read(h, p->filename, n);		/* filename */
			p->filename[n] = 0;
		} else
		if (type == 0x7A) {	/* comment header */
			read(h, (char*)&w, 2);			/* Size of comment */
			p->headSize += w;
		}
		lseek(h, p->headSize, SEEK_SET);	/* Seek to next header */
	}
	mp_msg(MSGT_STREAM,MSGL_INFO, "File Flags=%04x\tCompression Method=%x\n", flag, method);

	if (!(flag & 0x04) && (method == 0x30)) {	/* 0day stream */
		n = strlen(rarname);
		p->basename = strdup(rarname);
		if (p->naming) {
			p->naming = rarname + n - strrchr(rarname, 't') - 5;
			n -= (p->naming + 4);
		} else {
			n -= 3;
		}
		p->basename[n] = 0;

		close(h);
		h = open_0day_volume(p, 0);
		if (h < 0) {
			free(p->filename);
			free(p->basename);
			free(p);
		} else {
			/* reget packSize, avoid got the last volume's packSize */
			type = 0;
			n = 7;
			lseek(h, 7, SEEK_SET);
			while (type != 0x74) {
				lseek(h, 2, SEEK_CUR);				/* CRC */
				read(h, &type, 1);					/* Type */
				read(h, (char*)&flag, 2);			/* Flag */
				read(h, (char*)&w, 2);				/* Size */
				n += w;
				if (type == 0x74) {	/* file header */
					read(h, (char*)&(p->packSize), 4);
				} else
				if (type == 0x7A) {	/* comment header */
					read(h, (char*)&w, 2);			/* Size of comment */
					n += w;
				}
				lseek(h, n, SEEK_SET);	/* Seek to next header */
			}

			stream->priv = (void*)p;
			stream->close = close_0day;
			stream->seek = seek_0day;
			stream->fill_buffer = fill_buffer_0day;
			stream->end_pos = p->fileSize;
			stream->type = STREAMTYPE_FILE;
		}
		return h;
	}

	free(p);

	if (unrardll) {								/* rar stream */
		struct RAROpenArchiveDataEx OpenArchiveData;
		struct RARHeaderDataEx HeaderData;
		HANDLE hPipeRead, hPipeWrite;
		int hArcData;

		memset(&OpenArchiveData,0,sizeof(OpenArchiveData));
		OpenArchiveData.ArcName=rarname;
		OpenArchiveData.OpenMode=RAR_OM_EXTRACT;

		hArcData=(*RAROpenArchiveEx)(&OpenArchiveData);
		if (!OpenArchiveData.OpenResult) {
			HeaderData.CmtBuf=NULL;
			if (!(*RARReadHeaderEx)(hArcData,&HeaderData)) {
				if (HeaderData.Flags & 0x04) {
					/* Request password */
					if (DialogBox(GetModuleHandle(NULL), MAKEINTRESOURCE(IDD_PASSWORD),
						GetForegroundWindow(), unrar_pw_dlgproc) == IDOK) {
						(*RARSetPassword)(hArcData, pw);
					} else {
						close(h);
						h = -2;
						goto rar_open_break;
					}
				}
				if (CreatePipe(&hPipeRead, &hPipeWrite, 0, 0x10000)) {
					stream_rar_priv_t *p;

					(*RARSetCallback)(hArcData, unrar_callback, (int)hPipeWrite);
					p = (stream_rar_priv_t*)malloc(sizeof(stream_rar_priv_t));
					p->filename = strdup(HeaderData.FileName);
					p->hArcData = hArcData;
					p->hPipeWrite = hPipeWrite;
					if (_beginthread((void (*)())unrar_thread, 0, (void*)p) != -1) {
						stream->priv = (void*)p;
						stream->close = close_rar;
						close(h);
						return (int)hPipeRead;
					}
					else {
						free(p->filename);
						free(p);
						CloseHandle(hPipeRead);
						CloseHandle(hPipeWrite);
					}
				}
			}

rar_open_break:
			(*RARCloseArchive)(hArcData);
		}
	}

	return h;
}