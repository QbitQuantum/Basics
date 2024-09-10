void
IT_PLAYMETAFILE(ENV *envp,LONGPROC f)
{
	HDC hDC;
	WORD wSel;
	HGLOBAL hGlobal;

	hDC = GETWORD(SP+6);
	wSel = GETWORD(SP+4);
	hGlobal = GetSelectorHandle(wSel);
	envp->reg.ax = PlayMetaFile(hDC, hGlobal);
	envp->reg.sp += 2 * HANDLE_86 + RET_86;
}