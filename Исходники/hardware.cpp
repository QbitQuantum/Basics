void CTCSys::QSSysDisplayImage()
{
	SetDIBitsToDevice(ImageDC[0]->GetSafeHdc(), 1, 1,
		m_bitmapInfo.bmiHeader.biWidth,
		::abs(m_bitmapInfo.bmiHeader.biHeight),
		0, 0, 0,
		::abs(m_bitmapInfo.bmiHeader.biHeight),
		IR.DispBuf[0].data,
		&m_bitmapInfo, DIB_RGB_COLORS);
}