void CDlgPanel::OnBnClickedButtonStart()
{
	if (m_pManager)
	{
		int nType = m_pCmbType->GetCurSel();
		if (nType == 0)
		{
			//采集
			CWnd* pCapWnd = GetDlgVideo();
			BOOL bInCap = m_pManager->IsInCapture();
			if (!bInCap)
			{
				CComboBox* pComboxMediaSource = m_pCmbSourceType;
				CComboBox* pVideoCombo = m_pCmbCamera ;
				CComboBox* pAudioCombo = m_pCmbMic ;
				CEdit* pEdtRtspSource = m_pEdtRtspStream;

				SOURCE_TYPE eType = (SOURCE_TYPE)pComboxMediaSource->GetCurSel();
				int nCamId = 0;
				int nAudioId = 0;
				char szURL[128] = {0,};
				CString strTemp = _T("");

				//视频参数设置
				int nWidth = m_sAVCapParamInfo.nVWidth;
				int nHeight = m_sAVCapParamInfo.nVHeight;
				int nFps = m_sAVCapParamInfo.nFps;
				int nBitrate = m_sAVCapParamInfo.nBitrate;
				char  szDataType[64];
				strcpy_s(szDataType, m_sAVCapParamInfo.strColorFormat )	;
				//音频参数设置
				int nASampleRate = m_sAVCapParamInfo.nASampleRate;
				int nAChannels =m_sAVCapParamInfo.nAChannels;

				if (eType == SOURCE_LOCAL_CAMERA)
				{
					nCamId = pVideoCombo->GetCurSel();
					nAudioId = pAudioCombo->GetCurSel();
					strTemp = _T("本地音视频采集");

				}
				else if ((eType == SOURCE_SCREEN_CAPTURE))
				{
					nCamId = -1;
					nAudioId = pAudioCombo->GetCurSel();
					strTemp = _T("屏幕采集");
					strcpy_s(szDataType , "RGB24");

					int nRet =m_pManager->GetScreenCapSize(nWidth, nHeight);
					if (nRet<1)
					{
						m_pManager->LogErr(_T("屏幕采集获取长宽失败，本地预览失败！"));
						return;
					}
				}
				else
				{
					//Start
					wchar_t wszURL[128] = {0,};
					if (NULL != pEdtRtspSource)
						pEdtRtspSource->GetWindowTextW(wszURL, sizeof(wszURL));
					if (wcslen(wszURL) < 1)		return;

					CString strURL = wszURL;
					CString strRTSP = strURL.Mid(0,4);
					if (strRTSP!=_T("rtsp")&&strRTSP!=_T("RTSP"))
					{
						strURL = _T("rtsp://")+strURL;
					}

					__WCharToMByte(strURL, szURL, sizeof(szURL)/sizeof(szURL[0]));
					strTemp = _T("网络音视频流采集");
				}

				int nRet = m_pManager->StartCapture( eType,  nCamId, nAudioId, pCapWnd->GetSafeHwnd(), szURL, nWidth, nHeight, nFps,nBitrate, szDataType, nASampleRate , nAChannels );
				if (nRet>0)
				{
					strTemp +=_T("成功！"); 
					m_pManager->LogErr(strTemp);
				} 
				else
				{
					strTemp +=_T("失败！"); 
					m_pManager->LogErr(strTemp);
					return;
				}

				//推送
				//获取服务器流地址信息
				ServerURLInfo URLInfo;
				memset(&URLInfo, 0, sizeof(ServerURLInfo));
				if (m_pMainDlg)
				{
					m_pMainDlg->	GetPushServerInfo(&URLInfo);
				}

				bool bPushRtmp = false;
				//流名称格式化
				FormatStreamName(URLInfo.sdpName);
				nRet = m_pManager->StartPush(URLInfo.pushServerAddr, URLInfo.pushServerPort,URLInfo.sdpName, URLInfo.nPushBufferLenth, bPushRtmp);
				CString strMsg = _T("");
				CString strIp;
				CString strName;
				strIp = URLInfo.pushServerAddr;
				strName = URLInfo.sdpName;
				if (nRet>=0)
				{
					strMsg.Format(_T("推送EasyDarwin服务器URL：rtsp://%s:%d/%s 成功！"), strIp , URLInfo.pushServerPort, strName);
					m_pManager->LogErr(strMsg);
					m_btnStart.SetWindowText(TEXT("Stop"));
					if (bPushRtmp)
					{
						strMsg.Format(_T("连接RTMP服务器成功，推送RTMP服务器URL：rtmp://%s:1935/live/%s 成功！"), strIp , strName);
						m_pManager->LogErr(strMsg);
					}
				} 
				else
				{
					strMsg.Format(_T("推送EasyDarwin服务器URL：rtsp://%s:%d/%s 失败！"), strIp, URLInfo.pushServerPort,strName);
					m_pManager->LogErr(strMsg);
					if (bPushRtmp)
					{
						if (nRet == -1)
							strMsg.Format(_T("连接RTMP服务器失败!"), strIp , strName);
						else
							strMsg.Format(_T("推送RTMP服务器URL：rtmp://%s:1935/live/%s 失败！"), strIp , strName);
						m_pManager->LogErr(strMsg);
					}
				}
			}
			else
			{
				m_pManager->LogErr(_T("停止推送！"));
				m_pManager->StopPush();

				m_pManager->StopCapture();
				m_btnStart.SetWindowText(TEXT("Start"));
				m_pManager->LogErr(_T("本地预览停止"));

				pCapWnd->Invalidate();	
			}
		} 
		else //直播
		{
			//RTSP
			CWnd* pPlayWnd = GetDlgVideo();
			BOOL bInPlay = m_pManager->IsInPlaying();
			if (!bInPlay)
			{
				char szIp[128] = {0,};
				wchar_t wszIp[128] = {0,};

				if (NULL != m_pEdtRtspStream)	
					m_pEdtRtspStream->GetWindowTextW(wszIp, sizeof(wszIp));
				if (wcslen(wszIp) < 1)		
					return;
				__WCharToMByte(wszIp, szIp, sizeof(szIp)/sizeof(szIp[0]));

				int nRet = m_pManager->StartPlay(szIp, pPlayWnd->GetSafeHwnd());
				m_btnStart.SetWindowText(TEXT("Stop"));
				CString strMsg = _T("");
				if (nRet>0)
				{
					strMsg.Format(_T("直播预览URL：%s 成功！"), wszIp);
				} 
				else
				{
					strMsg.Format(_T("直播预览URL：%s 失败！"), wszIp);
				}
				m_pManager->LogErr(strMsg);
			}
			else
			{
				m_pManager->StopPlay();
				m_btnStart.SetWindowText(TEXT("Start"));
				pPlayWnd->Invalidate();	
				m_pManager->LogErr(_T("停止直播"));
			}
		}
	}
}