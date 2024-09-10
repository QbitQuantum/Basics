void
IT_REGSERVERDOC (ENV *envp, LONGPROC f)
{
    LHSERVER lhHandle;
    LPSTR lpString1;
    LPOLESERVERDOC lpdoc;
    LPBYTE lpStr;
    LHSERVERDOC lhdoc;
    DWORD retcode;

    lhHandle = (LHSERVER)GETDWORD(SP+16);
    lpString1 = (LPSTR)GetAddress(GETWORD(SP+14),GETWORD(SP+12));
#ifdef	LATER
    translate the LPOLESERVERDOC and the structures behind it
#endif
    lpdoc = (LPOLESERVERDOC)GETDWORD(SP+8);
    lpStr = (LPBYTE)GetAddress(GETWORD(SP+6),GETWORD(SP+4));
    retcode = OleRegisterServerDoc(lhHandle,
                                   lpString1,
                                   lpdoc,
                                   &lhdoc);
    PUTDWORD(lpStr,lhdoc);
    envp->reg.sp += 2*DWORD_86 + 2*LP_86 + RET_86;
    envp->reg.ax = LOWORD(retcode);
    envp->reg.dx = HIWORD(retcode);
}