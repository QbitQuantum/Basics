BOOL _ui_init(
		HINSTANCE h_inst
	)
{
	HBITMAP undisk      = LoadBitmap( h_inst, MAKEINTRESOURCE( IDB_UNDISK ) );
	HBITMAP undisk_mask = LoadBitmap( h_inst, MAKEINTRESOURCE( IDB_UNDISK_MASK ) );

	HBITMAP disk        = LoadBitmap( h_inst, MAKEINTRESOURCE( IDB_DISK ) );
	HBITMAP disk_mask   = LoadBitmap( h_inst, MAKEINTRESOURCE( IDB_DISK_MASK ) );

	HBITMAP cdrom       = LoadBitmap( h_inst, MAKEINTRESOURCE( IDB_CDROM ) );
	HBITMAP cdrom_mask  = LoadBitmap( h_inst, MAKEINTRESOURCE( IDB_CDROM_MASK ) );

	HBITMAP disk_enb    = LoadBitmap( h_inst, MAKEINTRESOURCE( IDB_ENABLED ) );

	HBITMAP check       = LoadBitmap( h_inst, MAKEINTRESOURCE( IDB_CHECK ) );
	HBITMAP check_mask  = LoadBitmap( h_inst, MAKEINTRESOURCE( IDB_CHECK_MASK ) );

	NONCLIENTMETRICS metric = { sizeof(metric) };

	InitCommonControls( );
	if ( LoadLibrary(L"riched20.dll") == 0 ) return FALSE;

	__hinst = h_inst;
	__dlg = HWND_DESKTOP;

	metric.lfMessageFont.lfWeight = FW_BOLD;
	metric.lfMessageFont.lfHeight = -11;
	__font_bold = CreateFontIndirect( &metric.lfMessageFont );

	metric.lfMessageFont.lfWeight = FW_DONTCARE;
	metric.lfMessageFont.lfUnderline = TRUE;
	__font_link = CreateFontIndirect( &metric.lfMessageFont );

	metric.lfMessageFont.lfHeight = -9;
	metric.lfMessageFont.lfUnderline = FALSE;
	__font_small = CreateFontIndirect( &metric.lfMessageFont );

	__img = ImageList_Create( 9, 9, ILC_MASK, 2, 2 );
	__dsk_img = ImageList_Create( 15, 11, ILC_MASK | ILC_COLOR24, 5, 5 );
	
	ImageList_Add( __img, check, check_mask );

	ImageList_Add( __dsk_img, disk, disk_mask );
	ImageList_Add( __dsk_img, undisk, undisk_mask );
	ImageList_Add( __dsk_img, disk_enb, disk_mask );
	ImageList_Add( __dsk_img, cdrom, cdrom_mask );

	__cur_arrow = LoadCursor( NULL, IDC_ARROW );
	__cur_hand  = LoadCursor( NULL, IDC_HAND );
	__cur_wait  = LoadCursor( NULL, IDC_WAIT );

	return TRUE;

}