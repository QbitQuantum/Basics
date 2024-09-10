bool MCImageBitmapToPICT(MCImageBitmap *p_bitmap, MCMacSysPictHandle &r_pict)
{
#ifdef LIBGRAPHICS_BROKEN
	bool t_success = true;
	
	Pixmap drawdata = nil, drawmask = nil;
	MCBitmap *maskimagealpha = nil;
	
	t_success = MCImageSplitPixmaps(p_bitmap, drawdata, drawmask, maskimagealpha);
	
	if (!t_success)
		return false;

	Rect t_rect;
	SetRect(&t_rect, 0, 0, p_bitmap->width, p_bitmap->height);
	
	GWorldPtr t_old_gworld;
	GDHandle t_old_gdevice;
	GetGWorld(&t_old_gworld, &t_old_gdevice);

	PixMapHandle t_draw_pixmap;
	t_draw_pixmap = GetGWorldPixMap((CGrafPtr)drawdata -> handle . pixmap);
	
	GWorldPtr t_img_gworld;
	t_img_gworld = NULL;
	if (t_success)
	{
		QDErr t_err;
		t_err = NewGWorld(&t_img_gworld, 32, &t_rect, NULL, NULL, 0);
		if (t_err != noErr)
			t_success = false;
	}
	
	if (t_success)
	{
		SetGWorld(t_img_gworld, GetGDevice());
		
		PenMode(srcCopy);
		ForeColor(blackColor);
		BackColor(whiteColor);
		
		if (maskimagealpha != NULL)
		{
			GWorldPtr t_alpha_gworld;
			if (NewGWorldFromPtr(&t_alpha_gworld, 8, &t_rect, GetCTable(40), NULL, 0, maskimagealpha -> data, maskimagealpha -> bytes_per_line) == noErr)
			{
				const BitMap *t_dst_bits;
				t_dst_bits = GetPortBitMapForCopyBits(t_img_gworld);
				
				const BitMap *t_src_bits;
				t_src_bits = GetPortBitMapForCopyBits((CGrafPtr)drawdata -> handle . pixmap);
				
				const BitMap *t_mask_bits;
				t_mask_bits = GetPortBitMapForCopyBits(t_alpha_gworld);
				
				EraseRect(&t_rect);
				
				CopyDeepMask(t_src_bits, t_mask_bits, t_dst_bits, &t_rect, &t_rect, &t_rect, srcCopy, NULL);
			}
		}
		else if (drawmask != NULL)
		{
			PixMapHandle t_mask_pixmap;
			t_mask_pixmap = GetGWorldPixMap((CGrafPtr)drawmask -> handle . pixmap);
			
			EraseRect(&t_rect);
			
			const BitMap *t_dst_bits;
			t_dst_bits = GetPortBitMapForCopyBits(t_img_gworld);
			
			const BitMap *t_src_bits;
			LockPixels(t_draw_pixmap);
			t_src_bits = (BitMap *)*t_draw_pixmap;
			
			const BitMap *t_mask_bits;
			LockPixels(t_mask_pixmap);
			t_mask_bits = (BitMap *)*t_mask_pixmap;
			
			CopyMask(t_src_bits, t_mask_bits, t_dst_bits, &t_rect, &t_rect, &t_rect);
			
			UnlockPixels(t_mask_pixmap);
			
			UnlockPixels(t_draw_pixmap);
		}
		else
		{
			const BitMap *t_dst_bits;
			t_dst_bits = GetPortBitMapForCopyBits(t_img_gworld);
			
			const BitMap *t_src_bits;
			LockPixels(t_draw_pixmap);
			t_src_bits = (BitMap *)*t_draw_pixmap;
			CopyBits(t_src_bits, t_dst_bits, &t_rect, &t_rect, srcCopy, NULL);
			UnlockPixels(t_draw_pixmap);
		}
	}
	
	PicHandle t_handle;
	t_handle = NULL;
	if (t_success)
	{
		OpenCPicParams t_params;
		t_params . srcRect = t_rect;
		t_params . hRes = 72 << 16;
		t_params . vRes = 72 << 16;
		t_params . version = -2;
		t_params . reserved1 = 0;
		t_params . reserved2 = 0;
		t_handle = OpenCPicture(&t_params);
		if (t_handle == NULL)
			t_success = false;
	}

	if (t_success)
	{
		GWorldPtr t_pict_gworld;
		GDHandle t_pict_gdevice;
		GetGWorld(&t_pict_gworld, &t_pict_gdevice);
		
		PenMode(srcCopy);
		ForeColor(blackColor);
		BackColor(whiteColor);
		
		const BitMap *t_dst_bits;
		t_dst_bits = GetPortBitMapForCopyBits(t_pict_gworld);

		const BitMap *t_src_bits;
		t_src_bits = GetPortBitMapForCopyBits(t_img_gworld);
		CopyBits(t_src_bits, t_dst_bits, &t_rect, &t_rect, srcCopy, NULL);
		
		ClosePicture();
	}
	
	if (t_img_gworld != NULL)
		DisposeGWorld(t_img_gworld);
	
	SetGWorld(t_old_gworld, t_old_gdevice);

	MCscreen->freepixmap(drawdata);
	MCscreen->freepixmap(drawmask);
	if (maskimagealpha != nil)
		MCscreen->destroyimage(maskimagealpha);
	
	if (t_success)
		r_pict = (MCMacSysPictHandle)t_handle;
	
	return t_success;
#else
	return false;
#endif
}