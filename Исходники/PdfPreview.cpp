 void Render(HDC hdc, RectI target, int pageNo, float zoom) {
     ScopedCritSec scope(&currAccess);
     if (currBmp && currPage == pageNo && currSize == target.Size())
         currBmp->StretchDIBits(hdc, target);
     else if (!thread) {
         reqPage = pageNo;
         reqZoom = zoom;
         reqSize = target.Size();
         reqAbort = false;
         thread = CreateThread(NULL, 0, RenderThread, this, 0, 0);
     }
     else if (reqPage != pageNo || reqSize != target.Size()) {
         if (abortCookie)
             abortCookie->Abort();
         reqAbort = true;
     }
 }