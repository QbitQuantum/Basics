static BOOL GRPFILE_DoWriteGroupFile(HFILE file, PROGGROUP *group)
{
  CHAR buffer[34];
  HLOCAL hProgram;
  INT    NumProg, Title, Progs, Icons, Extension;
  INT    CurrProg, CurrIcon, nCmdShow, ptr, seqnum;
  DWORD  sizeAnd, sizeXor;
  BOOL   need_extension;
  LPCSTR lpszTitle = LocalLock(group->hName);

  UINT16 checksum;

  GRPFILE_InitChecksum();

  /* Calculate offsets */
  NumProg = 0;
  Icons   = 0;
  Extension = 0;
  need_extension = FALSE;
  hProgram = group->hPrograms;
  while(hProgram)
    {
      PROGRAM *program = LocalLock(hProgram);
      LPCSTR lpszWorkDir = LocalLock(program->hWorkDir);

      NumProg++;
      GRPFILE_CalculateSizes(program, &Icons, &Extension, &sizeAnd, &sizeXor);

      /* Set a flag if an extension is needed */
      if (lpszWorkDir[0] || program->nHotKey ||
	  program->nCmdShow != SW_SHOWNORMAL) need_extension = TRUE;

      hProgram = program->hNext;
    }
  Title      = 34 + NumProg * 2;
  Progs      = Title + strlen(lpszTitle) + 1;
  Icons     += Progs;
  Extension += Icons;

  /* Header */
  buffer[0] = 'P';
  buffer[1] = 'M';
  buffer[2] = 'C';
  buffer[3] = 'C';

  PUT_SHORT(buffer,  4, 0); /* Checksum zero for now, written later */
  PUT_SHORT(buffer,  6, Extension);
  /* Update group->nCmdShow */
  if (IsIconic(group->hWnd))      nCmdShow = SW_SHOWMINIMIZED;
  else if (IsZoomed(group->hWnd)) nCmdShow = SW_SHOWMAXIMIZED;
  else                            nCmdShow = SW_SHOWNORMAL;
  PUT_SHORT(buffer,  8, nCmdShow);
  PUT_SHORT(buffer, 10, group->x);
  PUT_SHORT(buffer, 12, group->y);
  PUT_SHORT(buffer, 14, group->width);
  PUT_SHORT(buffer, 16, group->height);
  PUT_SHORT(buffer, 18, group->iconx);
  PUT_SHORT(buffer, 20, group->icony);
  PUT_SHORT(buffer, 22, Title);
  PUT_SHORT(buffer, 24, 0x0020); /* unknown */
  PUT_SHORT(buffer, 26, 0x0020); /* unknown */
  PUT_SHORT(buffer, 28, 0x0108); /* unknown */
  PUT_SHORT(buffer, 30, 0x0000); /* unknown */
  PUT_SHORT(buffer, 32, NumProg);

  if ((UINT)HFILE_ERROR == GRPFILE_WriteWithChecksum(file, buffer, 34)) return FALSE;

  /* Program table */
  CurrProg = Progs;
  CurrIcon = Icons;
  hProgram = group->hPrograms;
  while(hProgram)
    {
      PROGRAM *program = LocalLock(hProgram);

      PUT_SHORT(buffer, 0, CurrProg);
      if ((UINT)HFILE_ERROR == GRPFILE_WriteWithChecksum(file, buffer, 2))
	      return FALSE;

      GRPFILE_CalculateSizes(program, &CurrProg, &CurrIcon, &sizeAnd, &sizeXor);
      hProgram = program->hNext;
    }

  /* Title */
  if ((UINT)HFILE_ERROR == GRPFILE_WriteWithChecksum(file, lpszTitle, strlen(lpszTitle) + 1))
    return FALSE;

  /* Program entries */
  CurrProg = Progs;
  CurrIcon = Icons;
  hProgram = group->hPrograms;
  while(hProgram)
    {
      PROGRAM *program = LocalLock(hProgram);
      LPCSTR Name     = LocalLock(program->hName);
      LPCSTR CmdLine  = LocalLock(program->hCmdLine);
      LPCSTR IconFile = LocalLock(program->hIconFile);
      INT next_prog = CurrProg;
      INT next_icon = CurrIcon;

      GRPFILE_CalculateSizes(program, &next_prog, &next_icon, &sizeAnd, &sizeXor);
      PUT_SHORT(buffer,  0, program->x);
      PUT_SHORT(buffer,  2, program->y);
      PUT_SHORT(buffer,  4, program->nIconIndex);
      PUT_SHORT(buffer,  6, 0x048c);            /* unknown */
      PUT_SHORT(buffer,  8, sizeXor);
      PUT_SHORT(buffer, 10, sizeAnd * 8);
      PUT_SHORT(buffer, 12, CurrIcon);
      PUT_SHORT(buffer, 14, CurrIcon + 12 + sizeAnd);
      PUT_SHORT(buffer, 16, CurrIcon + 12);
      ptr = CurrProg + 24;
      PUT_SHORT(buffer, 18, ptr);
      ptr += strlen(Name) + 1;
      PUT_SHORT(buffer, 20, ptr);
      ptr += strlen(CmdLine) + 1;
      PUT_SHORT(buffer, 22, ptr);

      if ((UINT)HFILE_ERROR == GRPFILE_WriteWithChecksum(file, buffer, 24) ||
	  (UINT)HFILE_ERROR == GRPFILE_WriteWithChecksum(file, Name, strlen(Name) + 1) ||
	  (UINT)HFILE_ERROR == GRPFILE_WriteWithChecksum(file, CmdLine, strlen(CmdLine) + 1) ||
	  (UINT)HFILE_ERROR == GRPFILE_WriteWithChecksum(file, IconFile, strlen(IconFile) + 1))
	return FALSE;

      CurrProg = next_prog;
      CurrIcon = next_icon;
      hProgram = program->hNext;
    }

  /* Icons */
#if 0  /* FIXME: this is broken anyway */
  hProgram = group->hPrograms;
  while(hProgram)
    {
      PROGRAM *program = LocalLock(hProgram);
      CURSORICONINFO *iconinfo = LocalLock(program->hIcon);
      LPVOID XorBits, AndBits;
      INT sizeXor = iconinfo->nHeight * iconinfo->nWidthBytes;
      INT sizeAnd = iconinfo->nHeight * ((iconinfo->nWidth + 15) / 16 * 2);
      /* DumpIcon16(LocalLock(program->hIcon), 0, &XorBits, &AndBits);*/

      PUT_SHORT(buffer, 0, iconinfo->ptHotSpot.x);
      PUT_SHORT(buffer, 2, iconinfo->ptHotSpot.y);
      PUT_SHORT(buffer, 4, iconinfo->nWidth);
      PUT_SHORT(buffer, 6, iconinfo->nHeight);
      PUT_SHORT(buffer, 8, iconinfo->nWidthBytes);
      buffer[10] = iconinfo->bPlanes;
      buffer[11] = iconinfo->bBitsPerPixel;

      if ((UINT)HFILE_ERROR == GRPFILE_WriteWithChecksum(file, buffer, 12) ||
	  (UINT)HFILE_ERROR == GRPFILE_WriteWithChecksum(file, AndBits, sizeAnd) ||
	  (UINT)HFILE_ERROR == GRPFILE_WriteWithChecksum(file, XorBits, sizeXor)) return FALSE;

      hProgram = program->hNext;
    }
#endif

  if (need_extension)
    {
      /* write `PMCC' extension */
      PUT_SHORT(buffer, 0, 0x8000);
      PUT_SHORT(buffer, 2, 0xffff);
      PUT_SHORT(buffer, 4, 0x000a);
      buffer[6] = 'P', buffer[7] = 'M';
      buffer[8] = 'C', buffer[9] = 'C';
      if ((UINT)HFILE_ERROR == GRPFILE_WriteWithChecksum(file, buffer, 10))
	      return FALSE;

      seqnum = 0;
      hProgram = group->hPrograms;
      while(hProgram)
	{
	  PROGRAM *program = LocalLock(hProgram);
	  LPCSTR lpszWorkDir = LocalLock(program->hWorkDir);

	  /* Working directory */
	  if (lpszWorkDir[0])
	    {
	      PUT_SHORT(buffer, 0, 0x8101);
	      PUT_SHORT(buffer, 2, seqnum);
	      PUT_SHORT(buffer, 4, 7 + strlen(lpszWorkDir));
	      if ((UINT)HFILE_ERROR == GRPFILE_WriteWithChecksum(file, buffer, 6) ||
		  (UINT)HFILE_ERROR == GRPFILE_WriteWithChecksum(file, lpszWorkDir, strlen(lpszWorkDir) + 1))
		return FALSE;
	    }

	  /* Hot key */
	  if (program->nHotKey)
	    {
	      PUT_SHORT(buffer, 0, 0x8102);
	      PUT_SHORT(buffer, 2, seqnum);
	      PUT_SHORT(buffer, 4, 8);
	      PUT_SHORT(buffer, 6, program->nHotKey);
	      if ((UINT)HFILE_ERROR == GRPFILE_WriteWithChecksum(file, buffer, 8)) return FALSE;
	    }

	  /* Show command */
	  if (program->nCmdShow)
	    {
	      PUT_SHORT(buffer, 0, 0x8103);
	      PUT_SHORT(buffer, 2, seqnum);
	      PUT_SHORT(buffer, 4, 8);
	      PUT_SHORT(buffer, 6, program->nCmdShow);
	      if ((UINT)HFILE_ERROR == GRPFILE_WriteWithChecksum(file, buffer, 8)) return FALSE;
	    }

	  seqnum++;
	  hProgram = program->hNext;
	}

      /* Write `End' extension */
      PUT_SHORT(buffer, 0, 0xffff);
      PUT_SHORT(buffer, 2, 0xffff);
      PUT_SHORT(buffer, 4, 0x0000);
      if ((UINT)HFILE_ERROR == GRPFILE_WriteWithChecksum(file, buffer, 6)) return FALSE;
    }

  checksum = GRPFILE_GetChecksum();
  _llseek(file, 4, SEEK_SET);
  PUT_SHORT(buffer, 0, checksum);
  _lwrite(file, buffer, 2);

  return TRUE;
}