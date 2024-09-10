// Received data event from the desktop server, now read the data
LRESULT CRDVView::OnReceiveData(WPARAM wParam,LPARAM lParam)
{
	// Receive the data
	CPacket * pPacket = NULL;

	// Receive the packet of data
	if (lParam)
	{
		// Image has been received in a thread and sent
		pPacket = (CPacket *)lParam;
	}
	else
	{
		// Read the packet from the main connection
		pPacket = new CPacket;
		CPacket & Packet = *pPacket;
		m_Socket >> Packet;
	}

	// Make it easy to work with either packet
	CPacket & Packet = *pPacket;

	// Process the data
	if (Packet.m_ucPacketType == 7)
	{
		// Create the temporary DIB
		CDIBFrame DIBPacket;
		DIBPacket.Init(Packet.m_Rect.Width(),Packet.m_Rect.Height(),m_nBitCount);

		// Point to the internal buffer of the DIB
		char * pBuffer = (LPSTR)DIBPacket;
		DWORD dwBytes = Packet.m_dwBytes;

		// Test for compression
		if (Packet.m_bUseCompression)
		{
			// Test for multi-threaded compression
			if (Packet.m_nCompThreads)
			{
				// Set the type of encoder
				m_pMTC->SetEncoder(Packet.m_bAC);

				// Multithreaded arithmetic decoding
				m_pMTC->SetBuffer(Packet.m_pBuffer,Packet.m_bAC ? Packet.m_dwBytes : Packet.m_dwSrcBytes,FALSE);
				m_pMTC->Decode();

				// Get the output buffer
				m_pMTC->GetBuffer(&pBuffer,&dwBytes,FALSE,FALSE);
			}
			else
			{
				if (Packet.m_bAC)
				{
					// Single-threaded arithmetic encoding
					m_AC.DecodeBuffer(Packet.m_pBuffer,Packet.m_dwBytes,&pBuffer,&dwBytes,FALSE);
				}
				else
				{
					// Single-threaded zlib uncompressing
					dwBytes = Packet.m_dwSrcBytes;
					m_ZLib.DecodeBuffer(Packet.m_pBuffer,Packet.m_dwBytes,pBuffer,dwBytes,FALSE);
				}
			}
		}
		else
		{
			// Copy the uncompressed DIB to the output
			memcpy(pBuffer,Packet.m_pBuffer,dwBytes);
		}

		// Get the image type
		BOOL bDIB = Packet.m_bDIB;

		// Get the reset attribute
		BOOL bXOR = Packet.m_bXOR;

		// Get the delta DIB
		CDIBFrame & XOR = m_XOR;

		// Get the viewed DIB
		CDIBFrame & DIB = m_DIB;

		// Get the rectangular coordinates
		CRect Rect = Packet.m_Rect;

		// Check for a PNG
		if (!bDIB)
		{
			// JPEG support
			COleStreamFile ImageStream;

			// Prepare the Image for memory stream serialization
			if (ImageStream.CreateMemoryStream())
			{
				// Write the packet to the stream
				ImageStream.Write(pBuffer,dwBytes);
				IStream * pImageStream = ImageStream.GetStream();

				// Load the image from the stream
				CImage ImageDIB;
				if (pImageStream && SUCCEEDED(ImageDIB.Load(pImageStream)))
				{
					// Transfer the PNG to a DIB
					ImageDIB.BitBlt(DIBPacket,0,0,SRCCOPY);

					// Release the stream
					pImageStream->Release();
				}
			}
		}

		if (bXOR)
		{
			// XOR the current desktop with the last
			BitBlt(DIB,Rect.left,Rect.top,Rect.Width(),Rect.Height(),DIBPacket,0,0,SRCINVERT);
		}
		else
		{
			// Copy over the current desktop
			BitBlt(DIB,Rect.left,Rect.top,Rect.Width(),Rect.Height(),DIBPacket,0,0,SRCCOPY);
		}

		// Update the last DIB
		BitBlt(XOR,0,0,m_cxWidth,m_cyHeight,DIB,0,0,SRCCOPY);

		// Update the screen
		InvalidateRect(NULL,FALSE);
		UpdateWindow();
	}
	else if (Packet.m_ucPacketType == 3) // Cursor
	{
		// Get the cursor data
		DWORD dwXHotSpot = Packet.m_dwXHotSpot;
		DWORD dwYHotSpot = Packet.m_dwYHotSpot;
		int nWidth = Packet.m_bmWidth;
		int nHeight = Packet.m_bmHeight;
		WORD bmMaskPlanes = Packet.m_bmMaskPlanes;
		WORD bmMaskBitsPixel = Packet.m_bmMaskBitsPixel;
		WORD bmColorPlanes = Packet.m_bmColorPlanes;
		WORD bmColorBitsPixel = Packet.m_bmColorBitsPixel;
		BYTE * pMaskBits = NULL;
		BYTE * pColorBits = NULL;
		if (Packet.m_MaskBits.size())
			pMaskBits = &(Packet.m_MaskBits[0]);
		if (Packet.m_ColorBits.size())
			pColorBits = &(Packet.m_ColorBits[0]);

		// Create a cursor
		m_Cursor.CreateCursor(dwXHotSpot,dwYHotSpot,nWidth,nHeight,bmMaskPlanes,bmMaskBitsPixel,bmColorPlanes,bmColorBitsPixel,pMaskBits,pColorBits);

		// Set the cursor
		SetClassLong(m_hWnd,-12,(LONG)(HCURSOR)m_Cursor);
		SetCursor(m_Cursor);
	}
	else if (Packet.m_ucPacketType == 2) // Display characteristics
	{
		// Free the previous multithread AC encoder
		if (m_pMTC)
		{
			delete m_pMTC;
			m_pMTC = NULL;
		}

		// Create the multithreaded AC driver
		m_pMTC = new CDriveMultiThreadedCompression(m_nCompThreads);

		// Display characteristics
		m_cxWidth = Packet.m_cxScreen;
		m_cyHeight = Packet.m_cyScreen;
		m_nBitCount = Packet.m_nBitCount;
		m_nGridThreads = Packet.m_nGridThreads;
		m_iGridThread = 0;

		// Set the new scroll sizes
		m_ViewSize.cx = m_cxWidth;
		m_ViewSize.cy = m_cyHeight;

		// Handle the initial condition
		if (m_bViewZoom)
		{
			// Provide a full view of the server with scroll bars
			SetScrollSizes(MM_TEXT,m_ViewSize);
			GetParentFrame()->RecalcLayout();
			ResizeParentToFit();
		}
		else
		{
			// Shrink to fit the server in the client window
			SetScaleToFitSize(m_ViewSize);
			GetParentFrame()->RecalcLayout();
		}

		// Setup the GDI
		SetupGDI();

		// Send the verification
		CPacket Packet2(m_nCompThreads,0);

		// Send the packet
		m_Socket << Packet2;
	}
	else if (Packet.m_ucPacketType == 10)
	{
		// Get the number of compression threads
		m_nCompThreads = Packet.m_nCompThreads;

		if (Packet.m_nSessionId == 0)
		{
			// Get the password for verification
			CString csPassword = GetDocument()->m_csPassword;

			// If the session is set then this verification to the server that the handshaking is over for the thread connection
			CPacket Packet2(csPassword,m_nSessionId);

			// Send the packet
			m_Socket << Packet2;
		}
		else
		{
			// Set the session id for the main connection and then set the timer for making the other connections
			if (!m_nSessionId)
			{
				// Get the session id
				m_nSessionId = Packet.m_nSessionId;

				// Make server connections for each update rectangle thread
				SetTimer(2,0,NULL);
			}
			else
			{
				// Close the document
				GetDocument()->OnCloseDocument();
			}
		}
	}

	// Clean up the packet if it needed to be created
	if (!lParam)
		delete pPacket;

	return 1;
}