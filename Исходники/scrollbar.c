BOOL FASTCALL
IntCalculateThumb(PWND Wnd, LONG idObject, PSCROLLBARINFO psbi, PSBDATA pSBData)
{
   INT Thumb, ThumbBox, ThumbPos, cxy, mx;
   RECTL ClientRect;

   switch(idObject)
   {
      case SB_HORZ:
         Thumb = UserGetSystemMetrics(SM_CXHSCROLL);
         cxy = psbi->rcScrollBar.right - psbi->rcScrollBar.left;
         break;
      case SB_VERT:
         Thumb = UserGetSystemMetrics(SM_CYVSCROLL);
         cxy = psbi->rcScrollBar.bottom - psbi->rcScrollBar.top;
         break;
      case SB_CTL:
         IntGetClientRect(Wnd, &ClientRect);
         if(Wnd->style & SBS_VERT)
         {
            Thumb = UserGetSystemMetrics(SM_CYVSCROLL);
            cxy = ClientRect.bottom - ClientRect.top;
         }
         else
         {
            Thumb = UserGetSystemMetrics(SM_CXHSCROLL);
            cxy = ClientRect.right - ClientRect.left;
         }
         break;
      default:
         return FALSE;
   }

   ThumbPos = Thumb;
   /* Calculate Thumb */
   if(cxy <= (2 * Thumb))
   {
      Thumb = cxy / 2;
      psbi->xyThumbTop = 0;
      psbi->xyThumbBottom = 0;
      ThumbPos = Thumb;
   }
   else
   {
      ThumbBox = pSBData->page ? MINTRACKTHUMB : UserGetSystemMetrics(SM_CXHTHUMB);
      cxy -= (2 * Thumb);
      if(cxy >= ThumbBox)
      {
         if(pSBData->page)
         {
            ThumbBox = max(EngMulDiv(cxy, pSBData->page, pSBData->posMax - pSBData->posMin + 1), ThumbBox);
         }

         if(cxy > ThumbBox)
         {
            mx = pSBData->posMax - max(pSBData->page - 1, 0);
            if(pSBData->posMin < mx)
               ThumbPos = Thumb + EngMulDiv(cxy - ThumbBox, pSBData->pos - pSBData->posMin, mx - pSBData->posMin);
            else
               ThumbPos = Thumb + ThumbBox;
         }

         psbi->xyThumbTop = ThumbPos;
         psbi->xyThumbBottom = ThumbPos + ThumbBox;
      }
      else
      {
         psbi->xyThumbTop = 0;
         psbi->xyThumbBottom = 0;
      }
   }
   psbi->dxyLineButton = Thumb;

   return TRUE;
}