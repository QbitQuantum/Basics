LRESULT CVideoRecvTestDlg::OnProceVideo(WPARAM wParam, LPARAM lParam)
{
	if(lParam == NULL) 
	{
		return E_FAIL;
	}
	VideoFrameData* TmpVideo = (VideoFrameData*)lParam;
	switch(TmpVideo->dwVideoType)
	{
	case VIDEO_TYPE_H264_NORMAL_I:
	case VIDEO_TYPE_H264_NORMAL_P:
		{
			CString strMsg;
			strMsg.Format("DataLen = %d, ExtInfo = %s",
			TmpVideo->dwVideoDataLen, TmpVideo->pszVideoExInfo);
			HDC TempDC = ::GetDC(GetDlgItem(IDC_STATIC_VIDEO)->GetSafeHwnd());
			SetBkMode(TempDC, 3);
			SetTextColor(TempDC, RGB(0, 128, 0));
			Rectangle(TempDC, 10, 20, 700, 80);
			TextOut(TempDC, 20, 20, "H264CallBack FrameInfo:", 23);
			int ilen = strMsg.GetLength();
			CString str1 = strMsg.Left(60);
			CString str2 = strMsg.Right(ilen - 60);
			TextOut(TempDC, 20, 40, str1.GetBuffer(), str1.GetLength());
			TextOut(TempDC, 20, 60, str2.GetBuffer(), str2.GetLength());
			//TextOut(TempDC, 20, 40, strMsg.GetBuffer(), strMsg.GetLength());
			::ReleaseDC(GetDlgItem(IDC_STATIC_VIDEO)->GetSafeHwnd(), TempDC);
		}
		break;
	case VIDEO_TYPE_H264_HISTORY_I:
	case VIDEO_TYPE_H264_HISTORY_P:
		{
			CString strMsg;
			strMsg.Format("DataLen = %d, ExtInfo = %s",
				TmpVideo->dwVideoDataLen, TmpVideo->pszVideoExInfo);
			HDC TempDC = ::GetDC(GetDlgItem(IDC_STATIC_VIDEO)->GetSafeHwnd());
			SetBkMode(TempDC, 3);
			SetTextColor(TempDC, RGB(0, 128, 0));
			Rectangle(TempDC, 10, 20, 700, 100);
			TextOut(TempDC, 20, 20, "H264CallBack FrameInfo:", 23);
			int ilen = strMsg.GetLength();
			CString str1 = strMsg.Left(60);
			CString str2 = strMsg.Right(ilen - 60);
			TextOut(TempDC, 20, 40, str1.GetBuffer(), str1.GetLength());
			TextOut(TempDC, 20, 60, str2.GetBuffer(), str2.GetLength());
			//TextOut(TempDC, 20, 40, strMsg.GetBuffer(), strMsg.GetLength());

			char* pszTime = strstr(TmpVideo->pszVideoExInfo, "FrameTime:");
			DWORD64 dw64TimeMS = 0;
			if(pszTime)
			{
				sscanf(pszTime, "FrameTime:%I64u", &dw64TimeMS);
				CTime cFrameTime(dw64TimeMS/1000);
				strMsg = cFrameTime.Format("%Y.%m.%d_%H:%M:%S");
				TextOut(TempDC, 400, 60, strMsg.GetBuffer(), strMsg.GetLength());
			}
			::ReleaseDC(GetDlgItem(IDC_STATIC_VIDEO)->GetSafeHwnd(), TempDC);
			if(((dw64TimeMS/1000) >= m_dwEndTime)&&m_realfinish == false)
			{
				::SendMessage(GetSafeHwnd(), WM_MESSAGE_GETFINISH, 0, 0);
			}
		}
		break;
	case VIDEO_TYPE_JPEG_HISTORY:
		{
			IStream* pStm = NULL;
			CreateStreamOnHGlobal(NULL, TRUE, &pStm);
			IPicture* picholder;
			LARGE_INTEGER liTempStar = {0};
			pStm->Seek(liTempStar, STREAM_SEEK_SET, NULL);
			ULONG iWritten = NULL;
			pStm->Write(TmpVideo->pVideoData, TmpVideo->dwVideoDataLen, &iWritten);
			pStm->Seek(liTempStar, STREAM_SEEK_SET, NULL);
			if(FAILED(OleLoadPicture(pStm, TmpVideo->dwVideoDataLen, TRUE, IID_IPicture, (void**)&picholder)))
			{
				pStm->Release();
				return 0;
			}

			HDC TempDC;
			TempDC = ::GetDC(GetDlgItem(IDC_STATIC_VIDEO)->GetSafeHwnd());
			OLE_XSIZE_HIMETRIC hmWidth;
			OLE_YSIZE_HIMETRIC hmHeight;
			picholder->get_Width(&hmWidth);
			picholder->get_Height(&hmHeight);
			int nWidth =MulDiv(hmWidth, GetDeviceCaps(TempDC, LOGPIXELSX), 2540);
			int nHeight = MulDiv(hmHeight, GetDeviceCaps(TempDC, LOGPIXELSY), 2540);
			picholder->Render(TempDC, 0, 0, m_ShowFrameRect.right-m_ShowFrameRect.left,
				m_ShowFrameRect.bottom-m_ShowFrameRect.top,
				0, hmHeight, hmWidth, -hmHeight, NULL);
			::ReleaseDC(GetDlgItem(IDC_STATIC_VIDEO)->GetSafeHwnd(), TempDC);
			picholder->Release();
			pStm->Release();

			CString strMsg;
			strMsg.Format("DataLen = %d, ExtInfo = %s",
				TmpVideo->dwVideoDataLen, TmpVideo->pszVideoExInfo);
			TempDC = ::GetDC(GetDlgItem(IDC_STATIC_VIDEO)->GetSafeHwnd());
			SetBkMode(TempDC, 3);
			SetTextColor(TempDC, RGB(0, 128, 0));
			Rectangle(TempDC, 10, 220, 700, 280);
			TextOut(TempDC, 20, 220, "HistoryVideoCallback JPEG FrameInfo:", 23);
			TextOut(TempDC, 20, 240, strMsg.GetBuffer(), strMsg.GetLength());
			char* pszTime = strstr(TmpVideo->pszVideoExInfo, "FrameTime:");
			DWORD64 dw64TimeMS = 0;
			if(pszTime)
			{
				sscanf(pszTime, "FrameTime:%I64u", &dw64TimeMS);
			}
			CTime cFrameTime(dw64TimeMS/1000);
			strMsg = cFrameTime.Format("%Y.%m.%d_%H:%M:%S");
			TextOut(TempDC, 20, 260, strMsg.GetBuffer(), strMsg.GetLength());
			::ReleaseDC(GetDlgItem(IDC_STATIC_VIDEO)->GetSafeHwnd(), TempDC);
			SetWindowText(strMsg.GetBuffer());
			if(((dw64TimeMS/1000) >= m_dwEndTime)&&m_realfinish == false)
			{
				::SendMessage(GetSafeHwnd(), WM_MESSAGE_GETFINISH, 0, 0);
			}
		}
		break;
	}
	
	return S_OK;
}