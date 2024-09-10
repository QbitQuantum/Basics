	void GDIRenderTarget::Flip()
	{
		RECT client;
		HDC hDC;
		Color *FrontVPData;
		unsigned int *DIBData;
	
		Color BufferOneColor(100, 149, 237,0);
		Color BufferTwoColor(100, 149, 237,0);

		//set up pointers to destination and source
		if(m_CurrentBackBuffer == m_VPage1)
		{
			FrontVPData = m_VPage1; //Set m_VPage1 as frontbuffer we want to present.
			m_CurrentBackBuffer = m_VPage2; //Set m_VPage2 as backbuffer.
			//memset(m_VPage2,0,(sizeof(Color) * m_frameBufferLength));
			SetFrameBufferColor(BufferTwoColor,2); //Set the color of m_vPage2
			m_CurrentZbuffer = m_ZBuffer2;
			memset(m_ZBuffer2,0,(sizeof(float) * m_frameBufferLength)); //Clean ZBuffer2
		}
		else
		{
			FrontVPData = m_VPage2; //Set m_VPage2 as frontBuffer we want to present.
			m_CurrentBackBuffer = m_VPage1; //Set m_vPage2 as backbuffer
			//memset(m_VPage1,0,(sizeof(Color) * m_frameBufferLength));
			SetFrameBufferColor(BufferOneColor,1); //Set the color of m_vPage1 
			m_CurrentZbuffer = m_ZBuffer1; 
			memset(m_ZBuffer1,0,(sizeof(float) * m_frameBufferLength)); //Clean ZBuffer1
		}
	
		DIBData = (unsigned int*)FrontVPData;

		//Get the windows device context
		hDC = GetDC(*(m_hWindow));
	
		//If it's available
		if(hDC != NULL)
		{
			//Get the window dimensions 
			GetClientRect(*(m_hWindow),&client);

			SetDIBitsToDevice(
				hDC,
				client.left,
				client.top,
				m_width,
				m_height,
				0,
				0,
				0,
				m_height,
				DIBData,
				&m_bitmapInfo,
				DIB_RGB_COLORS);
		
			//release the device context.
			ReleaseDC(*(m_hWindow),hDC);
		}
		//Reset background
	}