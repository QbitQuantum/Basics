/*
 *                       
 *         
 *                                  ¨x¨x¨x¨x¨x¨x¨xtop_line(dark)
 *                                   ---------top_line(light)
 *                                ¨† ¨‡        ¨‡¨†
 *        left_line(dark+light)   ¨† ¨‡        ¨‡¨†right_line(light+dark)
 *                                ¨† ¨‡        ¨‡¨†
 *    base_line_left ¨{¨{¨{¨{¨{¨{¨{                ¨{¨{¨{¨{¨{¨{¨{ base_line_right
 */
static void draw_hilight_box (HWND hWnd, HDC hdc, COOL_INDICATOR_ITEMDATA* item)
{
    int  l,r,t,b; 
    WINDOWINFO *info = (WINDOWINFO*)GetWindowInfo (hWnd);
    DWORD color;
    DWORD mainc = GetWindowElementAttr (hWnd, WE_FGC_THREED_BODY);	//UI@hilight_box_color
    
	if(item == NULL)
		return;

    l = item->RcTitle.left;
    t = item->RcTitle.top + 2;
    r = item->RcTitle.right + 1;
    b = item->RcTitle.bottom + 1;

    color = info->we_rdr->calc_3dbox_color (mainc, LFRDR_3DBOX_COLOR_DARKER);
    SetPenColor (hdc, RGBA2Pixel (hdc, GetRValue (color), GetGValue (color), GetBValue (color), GetAValue (color)));
    MoveTo (hdc, l, t);
    LineTo (hdc, l, b);	//left_line_dark
    MoveTo (hdc, r, t);
    LineTo (hdc, r, b);	//right_line_dark

	MoveTo (hdc, l, t);
	LineTo (hdc, r, t);	//top_line_dark

    color = info->we_rdr->calc_3dbox_color (mainc, LFRDR_3DBOX_COLOR_LIGHTER);
    SetPenColor (hdc, RGBA2Pixel (hdc, GetRValue (color), GetGValue (color), GetBValue (color), GetAValue (color)));
    MoveTo (hdc, l + 1, t);
    LineTo (hdc, l + 1, b);	//left_line_light
    MoveTo (hdc, r - 1, t);
    LineTo (hdc, r - 1, b);	//right_line_light

	MoveTo (hdc, l, t+1);
	LineTo (hdc, r, t+1);	//top_line_light

	mainc = GetWindowElementPixelEx(hWnd, hdc, WE_FGC_THREED_BODY);	//to avoid hdc use the color as ARGB
	SetBrushColor(hdc, mainc);	//base line color

	RECT rP;
	GetWindowRect(GetParent(hWnd), &rP);
	int x, y, w, h;
	x = 0;
	y = item->RcTitle.bottom + 2;
	w = item->RcTitle.left + 2;
	h = 4;
	FillBox(hdc, x, y, w, h);	//base_line_left
	x = item->RcTitle.right + 1;
	y = item->RcTitle.bottom + 2;
	w = RECTW(rP) - x;
	h = 4;
	FillBox(hdc, x, y, w, h);	//base_line_right
}