void Filesets_ContinueDrag (HWND hDlg)
{
   if (l.fDragging)
      {
      LPIDENT lpi = NULL;
      HLISTITEM hItemTarget;

      DWORD dw = GetMessagePos();
      POINT pt = { LOWORD(dw), HIWORD(dw) };
      HWND hTarget = WindowFromPoint (pt);

      if (hTarget != NULL)
         {
         POINT ptClient = pt;
         ScreenToClient (hTarget, &ptClient);

         if ((lpi = IdentifyPoint (hTarget, ptClient, &hItemTarget)) != NULL)
            {
            if (!lpi->fIsServer() && !lpi->fIsAggregate())
               lpi = NULL;
            }
         }

      if (lpi != l.lpiTarget)
         {
         ImageList_DragLeave (NULL);

         if (l.hItemTarget)
            {
            LPARAM dwFlags = FastList_GetItemFlags (l.hwndTarget, l.hItemTarget);
            FastList_SetItemFlags (l.hwndTarget, l.hItemTarget, dwFlags & (~FLIF_DROPHIGHLIGHT));
            l.hItemTarget = NULL;
            l.lpiTarget = NULL;
            }

         if ((l.lpiTarget = lpi) != NULL)
            {
            l.hwndTarget = hTarget;
            l.hItemTarget = hItemTarget;
            LPARAM dwFlags = FastList_GetItemFlags (l.hwndTarget, l.hItemTarget);
            FastList_SetItemFlags (l.hwndTarget, l.hItemTarget, dwFlags | FLIF_DROPHIGHLIGHT);
            }

         ScreenToClient (NULL, &pt);
         ImageList_DragEnter (NULL, pt.x, pt.y);
         }

      ImageList_DragMove (LOWORD(dw), HIWORD(dw));
      }
}