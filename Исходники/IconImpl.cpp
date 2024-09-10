	bool IconImpl::Create(const Image& icon)
	{
		Image windowsIcon(icon); // Vive le COW
		if (!windowsIcon.Convert(PixelFormatType_BGRA8))
		{
			NazaraError("Failed to convert icon to BGRA8");
			return false;
		}

		HBITMAP bitmap = CreateBitmap(windowsIcon.GetWidth(), windowsIcon.GetHeight(), 1, 32, windowsIcon.GetConstPixels());
		HBITMAP monoBitmap = CreateBitmap(windowsIcon.GetWidth(), windowsIcon.GetHeight(), 1, 1, nullptr);

		// http://msdn.microsoft.com/en-us/library/windows/desktop/ms648052(v=vs.85).aspx
		ICONINFO iconInfo;
		iconInfo.fIcon = TRUE;
		iconInfo.hbmMask = monoBitmap;
		iconInfo.hbmColor = bitmap;

		m_icon = CreateIconIndirect(&iconInfo);

		DeleteObject(bitmap);
		DeleteObject(monoBitmap);

		if (!m_icon)
		{
			NazaraError("Failed to create icon: " + Error::GetLastSystemError());
			return false;
		}

		return true;
	}