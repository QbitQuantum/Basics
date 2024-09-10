	static LRESULT WndProc(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam)
	{
		// WM_INPUT data
		//
		static RAWINPUT buffer[32];
		static RAWINPUT ** pBuffer = new RAWINPUT *[32];
		static unsigned int HEADERSIZE = sizeof(RAWINPUTHEADER);

		switch (msg)
		{
				// input handling: use raw input
				//
		case WM_INPUT:
			{
				unsigned int dataRead = 32;
				GetRawInputBuffer(buffer, &dataRead, HEADERSIZE);
				if (!dataRead) {
					// error
					//
				}

				RAWINPUT * pri = buffer;
				for (unsigned int i = 0; i < dataRead; ++i) {
					pBuffer[i] = pri;
					pri = NEXTRAWINPUTBLOCK(pri);
				}
				DefRawInputProc(pBuffer, dataRead, HEADERSIZE);
			}
			return 0;
		}
		return DefWindowProc(hwnd, msg, wparam, lparam);
	}