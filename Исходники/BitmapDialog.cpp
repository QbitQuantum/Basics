void CBitmapDialog::SetImage( Uint8 * image, int width, int height )
{
	Uint8 c;
	if (m_pBitmap != NULL)
		delete m_pBitmap;

	m_pBitmap = new CBitmap();
	m_pBitmap->CreateBitmap( width, height, 1, 32, NULL);

	CDC dc;
	dc.CreateCompatibleDC( this->GetDC() );

	dc.SelectObject( m_pBitmap );
	for (int x=0; x<width; x++)
	{
		for (int y=0; y<height; y++)
		{
			c = image[x + y*width];
			dc.SetPixel( x,y, RGB(c,c,c) );
		}
	}
}