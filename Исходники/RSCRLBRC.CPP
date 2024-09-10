void CRScrlBarCtrl::DrawTiledBitmap(FileNum filenum,CDC* pdc,int x,int y,int length)
{
	if (m_hWnd)
	{
		CWnd* parent;
		if (m_parent)
			parent=m_parent;
		else
			parent=GetParent()->GetParent();
		BYTE* pData;
		pData = (BYTE*)parent->SendMessage(WM_GETFILE,filenum,NULL);
		if (pData && pData[0]=='B' && pData[1]=='M') // checks if its a bitmap file
		{
			// now render it...
			BITMAPFILEHEADER* pFile=(BITMAPFILEHEADER*)pData;
			BITMAPINFO* pInfo=(BITMAPINFO*)(pData+sizeof(BITMAPFILEHEADER));
			pData+=pFile->bfOffBits;
			// tiling...
			int z,width;
			if (m_bHorzAlign)
			{
				for (z=x;z<x+length;z+=pInfo->bmiHeader.biWidth)
				{
					width=min(x+length-z,pInfo->bmiHeader.biWidth);
					SetDIBitsToDevice(pdc->m_hDC,z,y,width, pInfo->bmiHeader.biHeight,
						0,0,0,pInfo->bmiHeader.biHeight,pData,pInfo,DIB_RGB_COLORS);
				}
			}
			else
			{
				for (z=y;z<y+length;z+=pInfo->bmiHeader.biHeight)
				{
					width=min(y+length-z,pInfo->bmiHeader.biHeight);
					SetDIBitsToDevice(pdc->m_hDC,x,z, pInfo->bmiHeader.biWidth, width,
						0,0,0,pInfo->bmiHeader.biHeight,pData,pInfo,DIB_RGB_COLORS);
				}
			}
		}
		parent->SendMessage(WM_RELEASELASTFILE,NULL,NULL);
	}
}