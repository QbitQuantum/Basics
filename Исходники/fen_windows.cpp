void DVV::flush_buf_b1(HDC hdc)
{
	SetDIBitsToDevice
	(
		hdc, 
		_last_x0,_last_y, // x,y dans cible
		(DWORD)(_last_x-_last_x0),(DWORD) (1), // larg-haut 
		_last_x0,0,          // dans src
		0, (UINT)_tyB, 
		_im, _bmi, 
		(UINT) DIB_RGB_COLORS
	);
}