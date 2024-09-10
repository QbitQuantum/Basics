void ShowSubdiv(HWND hw)
{
	HDC	dc = GetDC	(hw);

	u32 CB = RGB(255,0,0);
	for (int z=0; z<dimZ; z++)
	{
		for (int x=0; x<dimX; x++)
		{
			Texel&	T	= texels[z*dimX+x];
			if (T.N)	{
				pixel	(dc,x,z,RGB(127,127,127));
				vertex&	N = *T.N;

				int		_x=x*3,_y=z*3;
				if		(isBorder(N,0))	{		// left
					SetPixel(dc,_x,_y+0,CB);
					SetPixel(dc,_x,_y+1,CB);
					SetPixel(dc,_x,_y+2,CB);
				}
				if		(isBorder(N,1))	{		// fwd
					SetPixel(dc,_x+0,_y,CB);
					SetPixel(dc,_x+1,_y,CB);
					SetPixel(dc,_x+2,_y,CB);
				}
				if		(isBorder(N,2))	{		// right
					SetPixel(dc,_x+2,_y+0,CB);
					SetPixel(dc,_x+2,_y+1,CB);
					SetPixel(dc,_x+2,_y+2,CB);
				}
				if		(isBorder(N,3))	{		// back
					SetPixel(dc,_x+0,_y+2,CB);
					SetPixel(dc,_x+1,_y+2,CB);
					SetPixel(dc,_x+2,_y+2,CB);
				}
			} else {
				pixel	(dc,x,z,RGB(0,127,0));
			}
		}
	}

	ReleaseDC		(hw, dc);
}