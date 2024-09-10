static void PrvImgView(WND wnd)
{
	int fd, len;
	ruint16 i, j;
	char tmp[10];
	struct img_data *picture;
	unsigned char *p;
	COLORVAL color;

	MemSet(tmp, 0, 10);
	fd = RalOpenFile((char *)&fileList[imgfocusedList]);
	if (fd == -1 ) 
	{
		GdiTextOut(wnd, "File Not Found", StrLen("File Not Found"), 20, 300);
		return ;
	}
	//GdiTextOut(wnd, "check", StrLen("test"), 140, 10);
	picture = NULL;
	len = StrLen(fileList[imgfocusedList]);
	p = &fileList[imgfocusedList][len-3];
	if ( !StrNCmp(p, "jpg", 3) || !StrNCmp(p, "JPG", 3) )
	{
		picture = img_jpeg_read(fd, 240, 320);
	}
	else if ( !StrNCmp(p, "gif", 3) || !StrNCmp(p, "GIF", 3) )
	{
		picture = img_gif_read(fd, 240, 320);
	}
	else if ( !StrNCmp(p, "png", 3) || !StrNCmp(p, "PNG", 3) )
	{
		picture = img_png_read(fd, 240, 320);
	}
	
	if (picture == NULL)
	{
		GdiTextOut(wnd, "Image File Read fail", StrLen("Image File Read fail"), 20, 300);
		return ;
	}

	imgStateID = IMAGEVIEW_STATE_FILE_SHOW;

	GdiLockScreen(wnd);
	GdiClrScreen(wnd, COLOR_BLACK);
	StrIToA(picture->size, tmp);
	//GdiTextOut(wnd, tmp, StrLen(tmp), 100, 310);

	p = picture->data;
	for(i=0; i<picture->height; i++)
	{
		for(j=0; j<picture->width; j++)
		{
			color = *p <<8 | (*(p+1) );
			GdiSetPixel(wnd, j, i, color );
			p += 2;
		}
	}
	GdiTextOut(wnd, fileList[imgfocusedList], StrLen(fileList[imgfocusedList]), 80, 300);


	if (picture) 
	{
		if (picture->data)
			free(picture->data);
		free(picture);
	}
	GdiUnlockScreen(wnd);

}