void ScreenCapture::CustomFrame()
{
	//nbase::NAutoLock auto_lock(&lock_);
	if (IsWindow(capture_hwnd_))
	{
		// 把屏幕设备描述表拷贝到内存设备描述表中
		HDC w_dc = GetDC(capture_hwnd_);
		if (w_dc)
		{
			RECT rcDlg;
			if (cut_screen_)
			{
				rcDlg = cut_rect_;
			} 
			else
			{
				::GetClientRect(capture_hwnd_, &rcDlg);
			}
			int width = rcDlg.right - rcDlg.left;
			int height = rcDlg.bottom - rcDlg.top;
			InitHBitmap(width, height);
			if (capture_bitmap_ == nullptr)
			{
				return;
			}
			HDC mem_dc = CreateCompatibleDC(w_dc);
			HBITMAP old_hbitmap = (HBITMAP)SelectObject(mem_dc, capture_bitmap_);
			//__int64 time0 = get_time_ms();
			if (cut_screen_)
			{
				BitBlt(mem_dc, 0, 0, capture_width_, capture_height_, w_dc, cut_rect_.left, cut_rect_.top, SRCCOPY /*| CAPTUREBLT*/);
			} 
			else
			{
				BitBlt(mem_dc, 0, 0, capture_width_, capture_height_, w_dc, 0, 0, SRCCOPY /*| CAPTUREBLT*/);
			}
			//__int64 time1 = get_time_ms();
			//鼠标
			if (1)
			{
				CURSORINFO pci;
				pci.cbSize = sizeof(CURSORINFO);
				GetCursorInfo(&pci);
				POINT ptCursor = pci.ptScreenPos;
				ICONINFO IconInfo = { 0 };
				if (GetIconInfo(pci.hCursor, &IconInfo))
				{
					ptCursor.x -= IconInfo.xHotspot;
					ptCursor.y -= IconInfo.yHotspot;
					if (NULL != IconInfo.hbmMask)
						DeleteObject(IconInfo.hbmMask);
					if (NULL != IconInfo.hbmColor)
						DeleteObject(IconInfo.hbmColor);
				}
				if (capture_hwnd_ != nullptr)
				{
					//RECT rcDlg;
					//::GetWindowRect(capture_hwnd_, &rcDlg);
					//ptCursor.x -= rcDlg.left;
					//ptCursor.y -= rcDlg.top;
					ScreenToClient(capture_hwnd_, &ptCursor);
				}
				if (cut_screen_)
				{
					ptCursor.x -= cut_rect_.left;
					ptCursor.y -= cut_rect_.top;
				}
				DrawIconEx(mem_dc, ptCursor.x, ptCursor.y, pci.hCursor, 0, 0, 0, NULL, DI_NORMAL | DI_COMPAT);
			}
			SelectObject(mem_dc, old_hbitmap);
			DeleteDC(mem_dc);
			ReleaseDC(capture_hwnd_, w_dc);
			timeb time_now;
			ftime(&time_now); // 秒数
			__int64 cur_timestamp = time_now.time * 1000 + time_now.millitm; // 毫秒
			int wxh = capture_width_ * capture_height_;
			frame_.AddVideoFrame(true, cur_timestamp, (const char*)capture_data_, wxh * 4, \
				capture_width_, capture_height_, "", nim_comp::VideoFrameMng::Ft_ARGB_r);

			//VideoCaptureData(0, capture_data_, wxh * 4, capture_width_, capture_height_, "", nullptr);
			//static __int64 time_custom = get_time_ms();
			//static int num_video = 0;
			//static __int64 time_bitblt = 0; 
			//time_bitblt += time1 - time0;
			//num_video++;
			//__int64 time_cur = get_time_ms();
			//if (time_cur > time_custom + 1000)
			//{
			//	time_custom += 1000;
			//	if (time_cur > time_custom + 2000)
			//	{
			//		time_custom = time_cur;
			//	}
			//	_PRINT("custom video fps %d time %lld", num_video, time_bitblt/num_video);
			//	num_video = 0;
			//	time_bitblt = 0;
			//}
		}
	}
}