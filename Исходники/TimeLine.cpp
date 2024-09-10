//----------------------------------------------------------------------------
void CTimeLine::Draw()
{
	if(!IsEnabled())
		return;

	unsigned int PrevFrame = 1 - m_CurrFrame; // draw the previously recorded frame, since the current one is still being filled
	unsigned long long FrameDuration = m_FrameEnd[PrevFrame] - m_FrameStart[PrevFrame];
	unsigned long long ClockFrequency = CTime::GetClockFrequency();
	unsigned long DurationMicroSecs = (unsigned long)(FrameDuration * 1000000 / ClockFrequency);
	unsigned int Width, Height;
	m_rRenderer->GetViewportSize(Width, Height);	

	// Draw the total frame duration	
	char FrameDurationSt[256];
	sprintf_s(FrameDurationSt, 255, "Frame %d.%dms", DurationMicroSecs / 1000, DurationMicroSecs % 1000);
	CColor White(255, 255, 255, 255);		
	m_rDebugGUI->DrawString((float)scLeftMargin, (float)scTopMargin, FrameDurationSt, White);
	
	if(m_pMaterial == NULL)
	{
		CMaterialPlainColor::CParameters Params("CTimeline.PlainColorParams", CMaterialPlainColor::eViewSpace);
		m_pMaterial = &m_rMaterialSystem->GetMaterial<CMaterialPlainColor>(&Params);
	}	
	
	unsigned int BarStart = scLeftMargin + scThreadName * 8 + 5; // 8 is the debug fonts character width
	unsigned int BarEnd = Width - scRightMargin;
	
	float PixelWidth = 2.0f / (float)Width;
	float PixelHeight = 2.0f / (float)Height;
	float ViewSpaceFrameWidth = (BarEnd - BarStart) * PixelWidth;
	float MicroSecondsToViewSpace = ViewSpaceFrameWidth / DurationMicroSecs;
			
	
	XMMATRIX LocalToWorld = XMMatrixIdentity();		
	XMFLOAT2 Uv0(0.0f, 0.0f);							
	
	m_rUtilityDraw->BeginTriangleList();	
	
	float X0;
	float X1;
	float Y0 = 1.0f - (scTopMargin + scBarHeight) * PixelHeight; // After frame duration
	float Y1 = Y0 - scBarHeight * PixelHeight;	
	
	for(unsigned int ThreadIndex = 0; ThreadIndex < scMaxThreads; ThreadIndex++)
	{
		X0 = -1.0f + BarStart * PixelWidth;
		X1 = X0; 
		const CEventDesc* pEventDesc = m_pEventDescs[ThreadIndex];
		if(pEventDesc)
		{
			if ((m_EventRead[ThreadIndex] == m_EventEnd[ThreadIndex]) && m_pActive[ThreadIndex])
			{
				CEvent* pEvent = m_pActive[ThreadIndex];
				if (pEvent->m_State == CEvent::eStarted)
				{
					DrawEvent(	pEvent,
								PrevFrame,
								ClockFrequency,
								ThreadIndex,
								MicroSecondsToViewSpace,
								X0,
								X1,
								Y0,
								Y1,
								PixelWidth,
								PixelHeight,
								pEventDesc);
				}
			}
			for ( ;(m_EventRead[ThreadIndex] != m_EventEnd[ThreadIndex]); m_EventRead[ThreadIndex] = (m_EventRead[ThreadIndex] + 1) % scMaxEvents)
			{
				unsigned int EventIndex = m_EventRead[ThreadIndex];
				CEvent* pEvent = &m_Events[ThreadIndex][EventIndex];
				DrawEvent(pEvent,
					PrevFrame,
					ClockFrequency,
					ThreadIndex,
					MicroSecondsToViewSpace,
					X0,
					X1,
					Y0,
					Y1,
					PixelWidth,
					PixelHeight,
					pEventDesc);

			}			
		}
		Y0 = Y1;
		Y1 = Y0 - scBarHeight * PixelHeight;	
	}
	m_rUtilityDraw->EndTriangleList(LocalToWorld, m_pMaterial, CRenderer::eDepthNone, CRenderer::eBlendModulate);	

	// Draw thread names	
	Y0 = scTopMargin + scBarHeight; // After frame duration, this is in pixels not view space
	X0 = scLeftMargin;
	for(unsigned int ThreadIndex = 0; ThreadIndex < scMaxThreads; ThreadIndex++)
	{
		if(m_pThreadNames[ThreadIndex])
		{
			m_rDebugGUI->DrawString(X0, Y0, m_pThreadNames[ThreadIndex], White);		
			Y0 += scBarHeight;
		}
	}			
	
	// Now draw all events for the current thread
	const CEventDesc* pEventDesc = m_pEventDescs[m_CurrentThread];
	if(pEventDesc)
	{
		while(pEventDesc->m_pName)
		{
			sprintf_s(FrameDurationSt, 255, "%-10s %d.%dms", pEventDesc->m_pName, m_Duration[pEventDesc->m_Type] / 1000, m_Duration[pEventDesc->m_Type] % 1000);
			m_rDebugGUI->DrawString(X0, Y0, FrameDurationSt, pEventDesc->m_Color);	
			Y0 += scBarHeight;	
			m_Duration[pEventDesc->m_Type] = 0;		
			pEventDesc++;
		}		
	}	
}