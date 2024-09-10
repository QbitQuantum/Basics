/////////////////////////////////////////////////////////////////////////////
// Name:    DrawTextToDestDC
// Description:   Draws text for the CB to hDC
//         (into which one of the "m_bitmaps[???]" is selected)
//
// Entry:
//          HDC hDC - DC to which text is drawn
//                   ("m_bitmaps[???]" is selected into it)
//
//          CRect rect  - part of client area (of the CB) to which
//                    text is output
//
/////////////////////////////////////////////////////////////////////////////
void
ZCheckBox::DrawTextToDestDC( HDC hDC, CRect& rect, int nState )
{
   if ( **m_pzsText == 0 )
      return;

   int   nIndexDC = SaveDC( hDC );
   DWORD dwStyle = 0;

   SetBkMode( hDC, TRANSPARENT );
   SelectObject( hDC, *m_pFont );

   if ( m_bLeftText )
   {
      rect.right -= BOX_SIZE + 6;
      dwStyle = DT_RIGHT;
   }
   else
   {
      rect.left += BOX_SIZE + 5;
      dwStyle = DT_LEFT;
   }

   rect.bottom -= 1;            // rect = drawing rectangle inside hDC

   if ( nState == BOX_DISABLED_1 || nState == BOX_DISABLED_2 )
   {
      if ( (m_ulMapActFlags & zMAPACT_DISABLE_READONLY) == 0 )
      {
         SetTextColor( hDC, GetSysColor( COLOR_3DHILIGHT ) );

         rect.OffsetRect( 1, 1 );
         DrawText( hDC, *m_pzsText, -1, &rect,
                   DT_SINGLELINE | DT_VCENTER | dwStyle );

         SetTextColor( hDC, GetSysColor( COLOR_3DSHADOW ) );
         rect.OffsetRect( -1, -1 );
      }

      DrawText( hDC, *m_pzsText, -1, &rect,
                DT_SINGLELINE | DT_VCENTER | dwStyle );
   }
   else
   {
      DrawText( hDC, *m_pzsText, -1, &rect,
                DT_SINGLELINE | DT_VCENTER | dwStyle );
   }

   // calculate m_rectFocus
   int r_t = rect.right;           // right side of text rectangle

   DrawText( hDC, *m_pzsText, -1, &rect,
             DT_SINGLELINE | DT_VCENTER | dwStyle | DT_CALCRECT );

   CDC *pDC = CDC::FromHandle( hDC );
   CRect rectClip;
   pDC->GetClipBox( &rectClip );
   if ( rect.Width( ) > rectClip.Width( ) - BOX_SIZE -5 )
      rect.right = rect.left + rectClip.Width( ) - BOX_SIZE - 5;
   else
   if ( m_bLeftText )
   {
      int d = rect.right - rect.left; // text width
      d = r_t - d;
      rect.left  += d;
      rect.right += d;
   }

   m_rectFocus = rect;
   RestoreDC( hDC, nIndexDC );
}