HICON _al_win_create_icon(HWND wnd,
   ALLEGRO_BITMAP *sprite, int xfocus, int yfocus, bool is_cursor)
{
   int x, y;
   int sys_sm_cx, sys_sm_cy;
   HDC h_dc;
   HDC h_and_dc;
   HDC h_xor_dc;
   ICONINFO iconinfo;
   HBITMAP and_mask;
   HBITMAP xor_mask;
   HBITMAP hOldAndMaskBitmap;
   HBITMAP hOldXorMaskBitmap;
   HICON icon;

   if (is_cursor) {
      /* Get allowed cursor size - Windows can't make cursors of arbitrary size */
      sys_sm_cx = GetSystemMetrics(SM_CXCURSOR);
      sys_sm_cy = GetSystemMetrics(SM_CYCURSOR);
   }
   else {
      sys_sm_cx = GetSystemMetrics(SM_CXICON);
      sys_sm_cy = GetSystemMetrics(SM_CYICON);
   }

   if ((sprite->w > sys_sm_cx) || (sprite->h > sys_sm_cy)) {
      return NULL;
   }

   /* Create bitmap */
   h_dc = GetDC(wnd);
   h_xor_dc = CreateCompatibleDC(h_dc);
   h_and_dc = CreateCompatibleDC(h_dc);

   /* Prepare AND (monochrome) and XOR (colour) mask */
   and_mask = CreateBitmap(sys_sm_cx, sys_sm_cy, 1, 1, NULL);
   xor_mask = CreateCompatibleBitmap(h_dc, sys_sm_cx, sys_sm_cy);
   hOldAndMaskBitmap = (HBITMAP) SelectObject(h_and_dc, and_mask);
   hOldXorMaskBitmap = (HBITMAP) SelectObject(h_xor_dc, xor_mask);

   /* Create transparent cursor */
   for (y = 0; y < sys_sm_cy; y++) {
      for (x = 0; x < sys_sm_cx; x++) {
	 SetPixel(h_and_dc, x, y, WINDOWS_RGB(255, 255, 255));
	 SetPixel(h_xor_dc, x, y, WINDOWS_RGB(0, 0, 0));
      }
   }

   local_draw_to_hdc(h_xor_dc, sprite, 0, 0);

   /* Make cursor background transparent */
   for (y = 0; y < sprite->h; y++) {
      for (x = 0; x < sprite->w; x++) {
         ALLEGRO_COLOR c;
         unsigned char r, g, b, a;

         c = al_get_pixel(sprite, x, y);
         al_unmap_rgba(c, &r, &g, &b, &a);
         if (a != 0) {
	    /* Don't touch XOR value */
	    SetPixel(h_and_dc, x, y, 0);
	 }
	 else {
	    /* No need to touch AND value */
	    SetPixel(h_xor_dc, x, y, WINDOWS_RGB(0, 0, 0));
	 }
      }
   }

   SelectObject(h_and_dc, hOldAndMaskBitmap);
   SelectObject(h_xor_dc, hOldXorMaskBitmap);
   DeleteDC(h_and_dc);
   DeleteDC(h_xor_dc);
   ReleaseDC(wnd, h_dc);

   iconinfo.fIcon = is_cursor ? false : true;
   iconinfo.xHotspot = xfocus;
   iconinfo.yHotspot = yfocus;
   iconinfo.hbmMask = and_mask;
   iconinfo.hbmColor = xor_mask;

   icon = CreateIconIndirect(&iconinfo);

   DeleteObject(and_mask);
   DeleteObject(xor_mask);

   return icon;
}