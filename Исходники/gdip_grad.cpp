static
void gdip_delete_stencil(GF_STENCIL _this)
{
	GPSTEN();
	if (_sten->pSolid) GdipDeleteBrush(_sten->pSolid);
	if (_sten->pTexture) GdipDeleteBrush(_sten->pTexture);
	if (_sten->pLinear) GdipDeleteBrush(_sten->pLinear);
	if (_sten->pRadial) GdipDeleteBrush(_sten->pRadial);
	if (_sten->circle) GdipDeletePath(_sten->circle);
	if (_sten->pMat) GdipDeleteMatrix(_sten->pMat);
	if (_sten->pLinearMat) GdipDeleteMatrix(_sten->pLinearMat);
	if (_sten->pBitmap) GdipDisposeImage(_sten->pBitmap);
	if (_sten->conv_buf) gf_free(_sten->conv_buf);

	if (_sten->cols) delete [] _sten->cols;
	if (_sten->pos) delete [] _sten->pos;

	gf_free(_sten);
}