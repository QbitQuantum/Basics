static unsigned mbModalFlag(void)
{
  BOOL has = FALSE;
  if (!(HIWORD(GetVersion()) & 0x8000))   // NT can always open task modal
	  return MB_TASKMODAL;
  EnumThreadWindows(GetCurrentThreadId(), (WNDENUMPROC)threadHasWnd,
                    (LPARAM)&has);
  return has ? MB_TASKMODAL : MB_SYSTEMMODAL;
}