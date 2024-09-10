void _ns_subsample_dialog_draw_icons( NsSubsampleDialog *ssd )
   {
   HWND  wnd;
   HDC   dc;
   RECT  rc;


   wnd = GetDlgItem( ssd->dlg, IDS_SUB_LOCK_XY );
   dc  = GetDC( wnd );

   GetClientRect( wnd, &rc );

   if( ____ns_ssd_curr_fixed_all || ____ns_ssd_curr_fixed_width_height )
      DrawIcon( dc, 0, 0, LoadIcon( ssd->instance, "LOCK_ICON" ) );
   else
      FillRect( dc, &rc, ( HBRUSH )( COLOR_3DFACE + 1 ) );

   ReleaseDC( wnd, dc );

   wnd = GetDlgItem( ssd->dlg, IDS_SUB_LOCK_YZ );
   dc  = GetDC( wnd );

   GetClientRect( wnd, &rc );

   if( ____ns_ssd_curr_fixed_all )
      DrawIcon( dc, 0, 0, LoadIcon( ssd->instance, "LOCK_ICON" ) );
   else
      FillRect( dc, &rc, ( HBRUSH )( COLOR_3DFACE + 1 ) );

   ReleaseDC( wnd, dc );
   }