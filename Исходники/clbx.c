VOID clbDestroyProc(PCLBOX pclb) {
   if (pclb) {
      if (pclb->hchk) WinDestroyWindow(pclb->hchk);
      WinDestroyWindow(pclb->hlbx);
      WinDestroyWindow(pclb->hentry);
      WinDestroyWindow(pclb->hadd);
      WinDestroyWindow(pclb->hrem);
      WinDestroyWindow(pclb->hfind);
      free(pclb->psz);
      free(pclb);
      _heapmin();
   } /* endif */
}