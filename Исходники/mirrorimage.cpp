void CopyMirrored( HDC hdcDest, HDC hdcSrc, RECT drc )
{
	int border = GetSystemMetrics( SM_CXBORDER )+8;

	StretchBlt( hdcDest,	
				0,0, 
				(drc.right-drc.left),	(drc.bottom-drc.top),
				hdcSrc,		
				src_w-border,0, 
				-src_w,	src_h, SRCCOPY );
}