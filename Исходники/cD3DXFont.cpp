/*
=================
- Destructor.
=================
*/
cD3DXFont::~cD3DXFont()					// Destructor
{
	if(mFont != NULL)
		mFont->Release();
	RemoveFontMemResourceEx(mHFontHdle);
}