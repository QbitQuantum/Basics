// Sends the bitmap extracted from the View window to a printer of your choice
// This function provides a useful reference for printing bitmaps in general
void CDoc::Print()
{
	// Get the dimensions of the View window
	CRect rcView = GetView().GetClientRect();
	int Width = rcView.Width();
	int Height = rcView.Height();

	// Copy the bitmap from the View window
	CClientDC ViewDC(GetView());
	CMemDC MemDC(ViewDC);
	CBitmap bmView;
	bmView.CreateCompatibleBitmap(ViewDC, Width, Height);
	MemDC.SelectObject(bmView);
	MemDC.BitBlt(0, 0, Width, Height, ViewDC, 0, 0, SRCCOPY);

	CPrintDialog PrintDlg;

	try
	{
		// Bring up a dialog to choose the printer
		if (PrintDlg.DoModal(GetView()) == IDOK)	// throws exception if there is no default printer
		{
			// Zero and then initialize the members of a DOCINFO structure.
			DOCINFO di;
			memset(&di, 0, sizeof(DOCINFO));
			di.cbSize = sizeof(DOCINFO);
			di.lpszDocName = _T("Scribble Printout");
			di.lpszOutput = (LPTSTR)NULL;
			di.lpszDatatype = (LPTSTR)NULL;
			di.fwType = 0;

			// Begin a print job by calling the StartDoc function.
			CDC dcPrint = PrintDlg.GetPrinterDC();
			if (SP_ERROR == StartDoc(dcPrint, &di))
				throw CUserException(_T("Failed to start print job"));

			// Inform the driver that the application is about to begin sending data.
			if (0 > StartPage(dcPrint))
				throw CUserException(_T("StartPage failed"));

			BITMAPINFOHEADER bi;
			ZeroMemory(&bi, sizeof(BITMAPINFOHEADER));
			bi.biSize = sizeof(BITMAPINFOHEADER);
			bi.biHeight = Height;
			bi.biWidth = Width;
			bi.biPlanes = 1;
			bi.biBitCount = 24;
			bi.biCompression = BI_RGB;

			// Note: BITMAPINFO and BITMAPINFOHEADER are the same for 24 bit bitmaps
			// Get the size of the image data
			MemDC.GetDIBits(bmView, 0, Height, NULL, reinterpret_cast<BITMAPINFO*>(&bi), DIB_RGB_COLORS);

			// Retrieve the image data
			std::vector<byte> vBits(bi.biSizeImage, 0);	// a vector to hold the byte array
			byte* pByteArray = &vBits.front();
			MemDC.GetDIBits(bmView, 0, Height, pByteArray, reinterpret_cast<BITMAPINFO*>(&bi), DIB_RGB_COLORS);

			// Determine the scaling factors required to print the bitmap and retain its original proportions.
			float fLogPelsX1 = (float)ViewDC.GetDeviceCaps(LOGPIXELSX);
			float fLogPelsY1 = (float)ViewDC.GetDeviceCaps(LOGPIXELSY);
			float fLogPelsX2 = (float)GetDeviceCaps(dcPrint, LOGPIXELSX);
			float fLogPelsY2 = (float)GetDeviceCaps(dcPrint, LOGPIXELSY);
			float fScaleX = MAX(fLogPelsX1, fLogPelsX2) / MIN(fLogPelsX1, fLogPelsX2);
			float fScaleY = MAX(fLogPelsY1, fLogPelsY2) / MIN(fLogPelsY1, fLogPelsY2);

			// Compute the coordinates of the upper left corner of the centered bitmap.
			int cWidthPels = GetDeviceCaps(dcPrint, HORZRES);
			int xLeft = ((cWidthPels / 2) - ((int)(((float)Width) * fScaleX)) / 2);
			int cHeightPels = GetDeviceCaps(dcPrint, VERTRES);
			int yTop = ((cHeightPels / 2) - ((int)(((float)Height) * fScaleY)) / 2);

			// Use StretchDIBits to scale the bitmap and maintain its original proportions
			if (GDI_ERROR == (UINT)StretchDIBits(dcPrint, xLeft, yTop, (int)((float)Width * fScaleX),
				(int)((float)Height * fScaleY), 0, 0, Width, Height, pByteArray, reinterpret_cast<BITMAPINFO*>(&bi), DIB_RGB_COLORS, SRCCOPY))
			{
				throw CUserException(_T("Failed to resize image for printing"));
			}

			// Inform the driver that the page is finished.
			if (0 > EndPage(dcPrint))
				throw CUserException(_T("EndPage failed"));

			// Inform the driver that document has ended.
			if (0 > EndDoc(dcPrint))
				throw CUserException(_T("EndDoc failed"));
		}
	}

	catch (const CException& e)
	{
		// Display a message box indicating why printing failed.
		CString strMsg = CString(e.GetText()) + CString("\n") + e.GetErrorString();
		CString strType = CString(e.what());
		::MessageBox(NULL, strMsg, strType, MB_ICONWARNING);
	}

}