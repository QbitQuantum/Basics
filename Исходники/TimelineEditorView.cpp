// 操作中クリップの描画を行う
BOOL TimelineEditorView::DrawOperatingClip(const CDC& dcDC, const int& iHeight)
{
	// TODO: 元のクリップの色を変える　元々各タイミングで実施するよう変更
	m_pOperatingClipData->DrawOperatingOldRect(iHeight);

	CRect* rcOperatingRect = m_pOperatingClipData->GetOperatingRect();

	if (m_pTimelineDataOperator->IsSingleInTrim() || m_pTimelineDataOperator->IsSingleOutTrim())
	{
		m_pOperatingClipData->DrawSingleTrimRect(iHeight, m_pTimelineDataOperator->IsSingleInTrim());

#ifdef _DEBUG
		//TODO: デバッグ
		CString strText;
		double dPointX, dPointY;
		int iPoint;
		int iDuration;
		if (m_pTimelineDataOperator->IsSingleInTrim())
		{
			iPoint = m_pOperatingClipData->GetTimelineInPoint() + m_pTimelineDataOperator->GetOperatingClipFrameCount();
		}
		else
		{
			iPoint = m_pOperatingClipData->GetTimelineInPoint();
		}
		HFONT hfDrawFont;
		CreateDrawFont(13, 0, DEFAULT_FONTFACE, hfDrawFont);
		strText.Format(_T("TrimingClipInPoint  %d"), iPoint);
		ChangeScreenPointToOpenGLPoint(700, 15, iHeight, dPointX, dPointY);
		DrawTextOnGL(static_cast<PCTSTR>(strText), dcDC.GetSafeHdc(), hfDrawFont, BLACKCOLOR_BRUSH_FLOAT,
			static_cast<float>(dPointX), static_cast<float>(dPointY), TIMELINE_DEFAULTZ, 1.0f);
		strText.Format(_T("TrimingClipLeftPoint  %d"), rcOperatingRect->left);
		ChangeScreenPointToOpenGLPoint(700, 30, iHeight, dPointX, dPointY);
		DrawTextOnGL(static_cast<PCTSTR>(strText), dcDC.GetSafeHdc(), hfDrawFont, BLACKCOLOR_BRUSH_FLOAT,
			static_cast<float>(dPointX), static_cast<float>(dPointY), TIMELINE_DEFAULTZ, 1.0f);
		if (m_pTimelineDataOperator->IsSingleInTrim())
		{
			iPoint = m_pOperatingClipData->GetTimelineOutPoint();
			iDuration = m_pOperatingClipData->GetDuration() - m_pTimelineDataOperator->GetOperatingClipFrameCount();
		}
		else
		{
			iPoint = m_pOperatingClipData->GetTimelineOutPoint() + m_pTimelineDataOperator->GetOperatingClipFrameCount();
			iDuration = m_pOperatingClipData->GetDuration() + m_pTimelineDataOperator->GetOperatingClipFrameCount();
		}
		strText.Format(_T("TrimingClipOutPoint  %d"), iPoint);
		ChangeScreenPointToOpenGLPoint(700, 45, iHeight, dPointX, dPointY);
		DrawTextOnGL(static_cast<PCTSTR>(strText), dcDC.GetSafeHdc(), hfDrawFont, BLACKCOLOR_BRUSH_FLOAT,
			static_cast<float>(dPointX), static_cast<float>(dPointY), TIMELINE_DEFAULTZ, 1.0f);
		strText.Format(_T("TrimingClipRightPoint  %d"), rcOperatingRect->right);
		ChangeScreenPointToOpenGLPoint(700, 60, iHeight, dPointX, dPointY);
		DrawTextOnGL(static_cast<PCTSTR>(strText), dcDC.GetSafeHdc(), hfDrawFont, BLACKCOLOR_BRUSH_FLOAT,
			static_cast<float>(dPointX), static_cast<float>(dPointY), TIMELINE_DEFAULTZ, 1.0f);
		strText.Format(_T("TrimingClipDuration  %d"), iDuration);
		ChangeScreenPointToOpenGLPoint(700, 75, iHeight, dPointX, dPointY);
		DrawTextOnGL(static_cast<PCTSTR>(strText), dcDC.GetSafeHdc(), hfDrawFont, BLACKCOLOR_BRUSH_FLOAT,
			static_cast<float>(dPointX), static_cast<float>(dPointY), TIMELINE_DEFAULTZ, 1.0f);
		DeleteObject(hfDrawFont);
#endif

	}
	else
	{
		// ドロップ位置用
		m_pOperatingClipData->DrawMovingRect(iHeight);

#ifdef _DEBUG
		//TODO: デバッグ
		CString strText;
		double dPointX, dPointY;
		HFONT hfDrawFont;
		CreateDrawFont(13, 0, DEFAULT_FONTFACE, hfDrawFont);
		strText.Format(_T("MovingClipInPoint  %d"), m_pOperatingClipData->GetTimelineInPoint() + m_pTimelineDataOperator->GetOperatingClipFrameCount());
		ChangeScreenPointToOpenGLPoint(700, 15, iHeight, dPointX, dPointY);
		DrawTextOnGL(static_cast<PCTSTR>(strText), dcDC.GetSafeHdc(), hfDrawFont, BLACKCOLOR_BRUSH_FLOAT,
			static_cast<float>(dPointX), static_cast<float>(dPointY), TIMELINE_DEFAULTZ, 1.0f);
		strText.Format(_T("MovingClipLeftPoint  %d"), rcOperatingRect->left);
		ChangeScreenPointToOpenGLPoint(700, 30, iHeight, dPointX, dPointY);
		DrawTextOnGL(static_cast<PCTSTR>(strText), dcDC.GetSafeHdc(), hfDrawFont, BLACKCOLOR_BRUSH_FLOAT,
			static_cast<float>(dPointX), static_cast<float>(dPointY), TIMELINE_DEFAULTZ, 1.0f);
		strText.Format(_T("MovingClipRightPoint  %d"), rcOperatingRect->right);
		ChangeScreenPointToOpenGLPoint(700, 45, iHeight, dPointX, dPointY);
		DrawTextOnGL(static_cast<PCTSTR>(strText), dcDC.GetSafeHdc(), hfDrawFont, BLACKCOLOR_BRUSH_FLOAT,
			static_cast<float>(dPointX), static_cast<float>(dPointY), TIMELINE_DEFAULTZ, 1.0f);
#endif

		// マウス位置追随用
		CRect rcMousePointRect = m_pTimelineDataOperator->GetMousePointRect();
		if (!(rcMousePointRect.EqualRect(rcOperatingRect)))
		{
			m_pOperatingClipData->SetOverlappingVert(static_cast<float>(rcMousePointRect.left), static_cast<float>(iHeight - rcMousePointRect.top),
				static_cast<float>(rcMousePointRect.right), static_cast<float>(iHeight - rcMousePointRect.bottom));
			m_pOperatingClipData->DrawOverlappingRect(iHeight);

#ifdef _DEBUG
			strText.Format(_T("MouseMoveClipLeftPoint  %d"), rcMousePointRect.left);
			ChangeScreenPointToOpenGLPoint(700, 60, iHeight, dPointX, dPointY);
			DrawTextOnGL(static_cast<PCTSTR>(strText), dcDC.GetSafeHdc(), hfDrawFont, BLACKCOLOR_BRUSH_FLOAT,
				static_cast<float>(dPointX), static_cast<float>(dPointY), TIMELINE_DEFAULTZ, 1.0f);
			strText.Format(_T("MouseMoveClipRightPoint  %d"), rcMousePointRect.right);
			ChangeScreenPointToOpenGLPoint(700, 75, iHeight, dPointX, dPointY);
			DrawTextOnGL(static_cast<PCTSTR>(strText), dcDC.GetSafeHdc(), hfDrawFont, BLACKCOLOR_BRUSH_FLOAT,
				static_cast<float>(dPointX), static_cast<float>(dPointY), TIMELINE_DEFAULTZ, 1.0f);
			DeleteObject(hfDrawFont);
#endif
		}
	}
	return TRUE;
}