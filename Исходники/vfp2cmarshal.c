void _fastcall ReAllocHGlobal(ParamBlk *parm)
{
	HGLOBAL hMem;
	hMem = GlobalReAlloc((HGLOBAL)p1.ev_long,(SIZE_T)p2.ev_long,GMEM_MOVEABLE|GMEM_ZEROINIT);
	if (hMem)
	{
		REPLACEDEBUGALLOC(p1.ev_long,hMem,p2.ev_long);		
		RET_INTEGER(hMem);
	}
	else
	{
		SAVEWIN32ERROR(GlobalReAlloc,GetLastError());
		RAISEERROREX(0);
	}
}