CImage* HTMLImageElement::GetImage()
{
	if (m_pImage == NULL)
	{
		if (false)
		{
			String src = get_src();
			if (src.GetLength())
			{
				WCHAR result[2048];
				{
					String documentUrl = m_ownerDocument->get_url();
					// documentUrl = _bstr_t(bdocumentUrl, false);

					String baseUrl = documentUrl;

					ASSERT(0);
#if 0
					DWORD resultLen = sizeof(result) - sizeof(result[0]);
					InternetCombineUrlW(baseUrl->c_str(), src->c_str(), result, &resultLen, 0);
#endif
				}

			//	StringA localfilename = DownloadFile(result);

				m_pImage = new CImage;//LXML::g_Images.OpenImage(Convert2W(result));
				m_pImage->m_url = string_copy(result);

				DWORD threadId;
				
				::CreateThread(NULL, 0, ThreadFunc, this, 0, &threadId);

			}
		}
	}

	return m_pImage;
}