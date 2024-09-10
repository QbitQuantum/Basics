	HRESULT STDMETHODCALLTYPE TinySmiley::LoadStream(LPSTREAM pStm)
	{
		if (!pStm) return S_FALSE;
		STATSTG pstatstg;
		if (FAILED(pStm->Stat(&pstatstg, 0)))
		{
			return S_FALSE;
		}
		INT comp = 0;
		BYTE* pData = NULL;
		//获得字节流大小
		BYTE* pv = new BYTE[(UINT)pstatstg.cbSize.QuadPart];
		if (!pv) return S_FALSE;
		ULONG bytesSaved = 0;
		if (FAILED(pStm->Read(pv, (LONG)pstatstg.cbSize.QuadPart, &bytesSaved)))
		{
			goto error;
		}
		pData = stbi_load_from_memory_ex(pv, (INT)pstatstg.cbSize.QuadPart, &m_cx, &m_cy, &comp, 4, &m_count);
		SAFE_DELETE_ARRAY(pv);
		if (!pData)
		{
			goto error;
		}
		if (m_count == 1)
		{
			BITMAPINFO bmi;
			memset(&bmi, 0, sizeof(BITMAPINFO));
			bmi.bmiHeader.biSize = sizeof(BITMAPINFOHEADER);
			bmi.bmiHeader.biWidth = m_cx;
			bmi.bmiHeader.biHeight = -m_cy;
			bmi.bmiHeader.biPlanes = 1;
			bmi.bmiHeader.biBitCount = 32;
			bmi.bmiHeader.biCompression = BI_RGB;
			bmi.bmiHeader.biSizeImage = m_cx * m_cy * 4;
			BYTE* pvBits = NULL;
			HBITMAP hBitmap = ::CreateDIBSection(NULL, &bmi, DIB_RGB_COLORS, (void**)&pvBits, NULL, 0);
			if (hBitmap)
			{
				for (INT i = 0; i < m_cx * m_cy; i++)
				{
					pvBits[i * 4 + 3] = pData[i * 4 + 3];
					if (pvBits[i * 4 + 3] < 255)
					{
						pvBits[i * 4] = (BYTE)(DWORD(pData[i * 4 + 2])*pData[i * 4 + 3] / 255);//B
						pvBits[i * 4 + 1] = (BYTE)(DWORD(pData[i * 4 + 1])*pData[i * 4 + 3] / 255);//G
						pvBits[i * 4 + 2] = (BYTE)(DWORD(pData[i * 4])*pData[i * 4 + 3] / 255);//R
					}
					else
					{
						pvBits[i * 4] = pData[i * 4 + 2];
						pvBits[i * 4 + 1] = pData[i * 4 + 1];
						pvBits[i * 4 + 2] = pData[i * 4];
					}
				}
				m_images.push_back(hBitmap);
			}
		}
		else
		{
			BYTE* seek = pData + m_count * 4 * m_cx * m_cy;
			for (size_t i = 0; i < m_count; i++)
			{
				BITMAPINFO bmi;
				memset(&bmi, 0, sizeof(BITMAPINFO));
				bmi.bmiHeader.biSize = sizeof(BITMAPINFOHEADER);
				bmi.bmiHeader.biWidth = m_cx;
				bmi.bmiHeader.biHeight = -m_cy;
				bmi.bmiHeader.biPlanes = 1;
				bmi.bmiHeader.biBitCount = 32;
				bmi.bmiHeader.biCompression = BI_RGB;
				bmi.bmiHeader.biSizeImage = m_cx * m_cy * 4;
				BYTE* pvBits = NULL;
				HBITMAP hBitmap = ::CreateDIBSection(NULL, &bmi, DIB_RGB_COLORS, (void**)&pvBits, NULL, 0);
				if (hBitmap)
				{
					BYTE* ps = pData + i * m_cx * m_cy;
					for (INT i = 0; i < m_cx * m_cy; i++)
					{
						pvBits[i * 4 + 3] = ps[i * 4 + 3];
						if (pvBits[i * 4 + 3] < 255)
						{
							pvBits[i * 4] = (BYTE)(DWORD(ps[i * 4 + 2])*ps[i * 4 + 3] / 255);//B
							pvBits[i * 4 + 1] = (BYTE)(DWORD(ps[i * 4 + 1])*ps[i * 4 + 3] / 255);//G
							pvBits[i * 4 + 2] = (BYTE)(DWORD(ps[i * 4])*ps[i * 4 + 3] / 255);//R
						}
						else
						{
							pvBits[i * 4] = ps[i * 4 + 2];
							pvBits[i * 4 + 1] = ps[i * 4 + 1];
							pvBits[i * 4 + 2] = ps[i * 4];
						}
					}
					m_images.push_back(hBitmap);
					m_delays.push_back(*(UINT*)seek);
					seek += sizeof(UINT);
				}
			}
		}
		stbi_image_free(pData);
		return m_images.size() == m_count ? S_OK : S_FALSE;
	error:
		SAFE_DELETE_ARRAY(pv);
		stbi_image_free(pData);
		return S_FALSE;
	}