void Texture::Clear( const CColor4 & color )
{
	CReal Mul(255.0f);

	u8 ur = (u8) (color.GetX()*Mul);
	u8 ug = (u8) (color.GetY()*Mul);
	u8 ub = (u8) (color.GetZ()*Mul);
	u8 ua = (u8) (color.GetW()*Mul);

	U8* pu8data = (U8*) mpImageData;

	for( int ix=0; ix<miWidth; ix++ )
	{
		for( int iy=0; iy<miHeight; iy++ )
		{
			int idx = 4 * (ix*miHeight + iy);
			pu8data[idx+0] = ub;
			pu8data[idx+1] = ug;
			pu8data[idx+2] = ur;
			pu8data[idx+3] = ua;
		}
	}
	SetDirty(true);
}