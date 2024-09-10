/*
** Get the contents of the specified window handle and put
** them into the specified bitmap.  x0,y0 = upper left coordinates
** of source rectangle.
*/
static int bmp_from_icon(WILLUSBITMAP *bmp,HICON hIcon)

    {
    ICONINFO iinfo;

    if (!GetIconInfo(hIcon,&iinfo))
        return(0);
    return(bmp_to_from_winbmp(bmp,iinfo.hbmColor)!=NULL);
    }