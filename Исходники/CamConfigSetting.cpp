void CCamConfigSetting::ProciProcess(void *param)
{
	CCamConfigSetting* pThis = (CCamConfigSetting*)(param);
	{
		//pThis->UpdateData();
		//Calculate time difference
			
		//Image processing
		while (1)
		{
			pThis->m_genieToProci = pThis->m_imgTimeDiff.msec();
			pThis->m_prociToProci = (reinterpret_cast<ProciliCard *>(pThis->m_FirstCard))->FrameInterval();
			
			pThis->m_FirstCard->Wait();
			void *pMemBase = pThis->m_FirstCard->GetPixelMemBase();
			if(pMemBase)
			{
				if(pThis->m_FirstCard->BytesPerPixel() == 1)
				{
					PelGray8 *pGrayNew	= (PelGray8*)pThis->m_firstImg.Base();
					memcpy(pGrayNew, pMemBase, pThis->m_firstImg.Size());				
				}
				else if(pThis->m_FirstCard->BytesPerPixel() == 3)
				{
					PelRGB24 *pRGBOld		= (PelRGB24*)(pMemBase);
					PelRGB24 *pRGBNew		= (PelRGB24*)pThis->m_firstImg.Base();
					size_t	  pixelCount	= pThis->m_FirstCard->Width() * pThis->m_FirstCard->Height();
					
					for(size_t index = 0; index < pixelCount; ++index)
					{
						pRGBNew->V[0]	= pRGBOld->B;
						pRGBNew->V[1]	= pRGBOld->G;
						pRGBNew->V[2]	= pRGBOld->R;
						
						++pRGBOld;
						++pRGBNew;
					}
				}
				
				pThis->m_firstPlayer.SetImage(	pThis->m_firstImg.Base(), 
					pThis->m_FirstCard->Width(),
					pThis->m_FirstCard->Height());
				
				pThis->InvalidateRect		 (pThis->m_colorRect, FALSE);
				
			}
			
			//Display time difference	
			CString data;
			data.Format("%.3f", pThis->m_prociToProci);
			pThis->SetDlgItemText(IDC_ProciToProci, data);
			data.Format("%.3f", pThis->m_genieToProci);
			pThis->SetDlgItemText(IDC_GenieToProci, data);
			{
				if (pThis->m_genieToProci > pThis->m_maxValue)
				{
					pThis->m_maxValue = pThis->m_genieToProci;
					CString txt;
					txt.Format("%.3f", pThis->m_maxValue);
					pThis->SetDlgItemText(IDC_RECORD, txt);				
				}
			}
		}
	}
		
}