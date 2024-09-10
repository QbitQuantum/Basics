BOOL CPictureWnd::ShowPicture(char *pBuf, int nBufLen)
{
	if (pBuf == NULL)
	{
		return FALSE;
	}

	if (m_hImageMemory != NULL)
	{
		GlobalFree(m_hImageMemory);
		m_hImageMemory = NULL;
	}

	BOOL bLock = m_csIPictrue.Lock();
	if (bLock == TRUE && m_pIPicture != NULL)
	{
		m_pIPicture->Release();
		m_pIPicture = NULL;
	}
	m_csIPictrue.Unlock();

	// 给图片分配全局内存
	m_hImageMemory = GlobalAlloc(GMEM_MOVEABLE, nBufLen); 
	if (m_hImageMemory == NULL)
	{
		return FALSE;
	}
	
	void *pImageMemory = GlobalLock(m_hImageMemory); // 锁定内存
	memcpy(pImageMemory, pBuf, nBufLen);
	GlobalUnlock(m_hImageMemory); // 解锁内存

	// 创建一个IStream接口指针，用来保存图片流
	LPSTREAM pIStream = NULL;
	HRESULT hr = CreateStreamOnHGlobal(m_hImageMemory, TRUE, &pIStream); // 用全局内存初使化IStream接口指针
	_ASSERTE(SUCCEEDED(hr) && pIStream);

	// 创建一个IPicture接口指针，表示图片对象
	try
	{
		bLock = m_csIPictrue.Lock();
		if (bLock)
		{
			hr = OleLoadPicture(pIStream, nBufLen, FALSE, IID_IPicture, (LPVOID*)&(m_pIPicture)); // 用OleLoadPicture获得IPicture接口指针
		}
		m_csIPictrue.Unlock();
	}
	catch (CMemoryException* e)
	{
		MessageBox(ConvertString("Bad bmp file"),ConvertString("Prompt"));
		return FALSE;
	}
	catch (CFileException* e)
	{
		MessageBox(ConvertString("Bad bmp file"),ConvertString("Prompt"));
		return FALSE;
	}
	catch (CException* e)
	{
		MessageBox(ConvertString("Bad bmp file"),ConvertString("Prompt"));
		return FALSE;
	}

	_ASSERTE(SUCCEEDED(hr) && m_pIPicture);
	pIStream->Release();

	m_nScale = 100;
	memset (&m_siVert, '\0', sizeof (SCROLLINFO));
	memset (&m_siHorz, '\0', sizeof (SCROLLINFO));
	m_siVert.cbSize = sizeof (SCROLLINFO);
	m_siHorz.cbSize = sizeof (SCROLLINFO);
	Invalidate();

	return TRUE;
}