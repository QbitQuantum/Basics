static
VOID
HandleSetHandlePrintHex(HWND handle,DWORD Msg,WPARAM wParam,LPARAM lParam)
    {
      LPVOID pMem;
      HANDLE hNewBuffer;
      int ret;

      LocalFree((HLOCAL)SendMessage(handle, EM_GETHANDLE, 0, 0L));
      if (UnicodeUsed)
          {
            hNewBuffer = LocalAlloc(LMEM_MOVEABLE | LMEM_ZEROINIT, 100);
            pMem = LocalLock(hNewBuffer);
            strcpyw_((wchar_t*)pMem,NewTextW);
          }
      else
          {
            hNewBuffer = LocalAlloc(LMEM_MOVEABLE | LMEM_ZEROINIT,50);
            pMem = LocalLock(hNewBuffer);
            strcpy_((char*)pMem,NewText);
          }

      LocalUnlock(pMem);
      hNewBuffer = LocalHandle(pMem);

	  /* Updates the buffer and displays new buffer */
      ret =  SendMessage(handle, EM_SETHANDLE, (WPARAM)hNewBuffer, 0L);

      htoa(ret,&TextBuffer[8]);
      PrintTextXY(TextBuffer,ResultX,ResultY,16);
    }