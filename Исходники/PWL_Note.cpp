void CPWL_Note::RePosNoteChildren()
{
	if (m_bResizing) return;

	m_bResizing = TRUE;

	if (this->IsValid())
	{
		ASSERT(m_pSubject != NULL);
		ASSERT(m_pDateTime != NULL);
		ASSERT(m_pContents != NULL);
		ASSERT(m_pAuthor != NULL);
		ASSERT(m_pCloseBox != NULL);
		ASSERT(m_pIcon != NULL);
		ASSERT(m_pLBBox != NULL);
		ASSERT(m_pRBBox != NULL);
		ASSERT(m_pContentsBar != NULL);
		ASSERT(m_pOptions != NULL);

		CPDF_Rect rcClient = GetClientRect();

		CPDF_Rect rcIcon = rcClient;
		rcIcon.top -= 2.0f;
		rcIcon.right = rcIcon.left + 14.0f;
		rcIcon.bottom = rcIcon.top - 14.0f;
		rcIcon.Normalize();
		m_pIcon->Move(rcIcon, TRUE, FALSE);
		m_pIcon->SetVisible(CPWL_Utils::ContainsRect(rcClient, rcIcon));

		CPDF_Rect rcCloseBox = rcClient;
		rcCloseBox.right -= 1.0f;
		rcCloseBox.top -= 1.0f;
		rcCloseBox.left = rcCloseBox.right - 14.0f;
		rcCloseBox.bottom = rcCloseBox.top - 14.0f;
		rcCloseBox.Normalize();
		m_pCloseBox->Move(rcCloseBox, TRUE, FALSE);
		m_pCloseBox->SetVisible(CPWL_Utils::ContainsRect(rcClient, rcCloseBox));

		CPDF_Rect rcDate = rcClient;
		rcDate.right = rcCloseBox.left - POPUP_ITEM_TEXT_INDENT;
		rcDate.left = PWL_MAX(rcDate.right - m_pDateTime->GetContentRect().Width() - 1.0f, rcIcon.right + 1.0f);
		rcDate.top = rcClient.top - 2.0f;
		rcDate.bottom = rcDate.top - m_pDateTime->GetContentRect().Height();
		rcDate.Normalize();
		m_pDateTime->Move(rcDate, TRUE, FALSE);
		m_pDateTime->SetVisible(CPWL_Utils::ContainsRect(rcClient, rcDate));

		CPDF_Rect rcSubject = rcClient;
		rcSubject.top = rcClient.top - 2.0f;
		rcSubject.left = rcIcon.right + POPUP_ITEM_TEXT_INDENT;
		rcSubject.right = PWL_MIN(rcSubject.left + m_pSubject->GetContentRect().Width() + 1.0f, rcDate.left - 1.0f);
		rcSubject.bottom = rcSubject.top - m_pSubject->GetContentRect().Height();
		rcSubject.Normalize();
		m_pSubject->Move(rcSubject, TRUE, FALSE);	
		m_pSubject->SetVisible(CPWL_Utils::ContainsRect(rcClient, rcSubject));

		CPDF_Rect rcOptions = rcClient;
		rcOptions.left = PWL_MAX(rcOptions.right - m_pOptions->GetContentRect().Width(), rcIcon.right + 1.0f);
		rcOptions.top = rcSubject.bottom - 4.0f;
		rcOptions.bottom = rcOptions.top - m_pOptions->GetContentRect().Height();
		rcOptions.Normalize();
		m_pOptions->Move(rcOptions, TRUE, FALSE);
		m_pOptions->SetVisible(CPWL_Utils::ContainsRect(rcClient, rcOptions));

		CPDF_Rect rcAuthor = rcClient;
		rcAuthor.top = rcSubject.bottom - 4.0f;
		rcAuthor.left = rcSubject.left;
		rcAuthor.right = PWL_MIN(rcSubject.left + m_pAuthor->GetContentRect().Width() + 1.0f, rcOptions.left - 1.0f);
		rcAuthor.bottom = rcAuthor.top - m_pAuthor->GetContentRect().Height();
		rcAuthor.Normalize();
		m_pAuthor->Move(rcAuthor, TRUE, FALSE);
		m_pAuthor->SetVisible(CPWL_Utils::ContainsRect(rcClient, rcAuthor));

		CPDF_Rect rcLBBox = rcClient;
		rcLBBox.top = rcLBBox.bottom + 7.0f;
		rcLBBox.right = rcLBBox.left + 7.0f;
		rcLBBox.Normalize();
		m_pLBBox->Move(rcLBBox, TRUE, FALSE);
		m_pLBBox->SetVisible(CPWL_Utils::ContainsRect(rcClient, rcLBBox));

		CPDF_Rect rcRBBox = rcClient;
		rcRBBox.top = rcRBBox.bottom + 7.0f;
		rcRBBox.left = rcRBBox.right - 7.0f;
		rcRBBox.Normalize();
		m_pRBBox->Move(rcRBBox, TRUE, FALSE);
		m_pRBBox->SetVisible(CPWL_Utils::ContainsRect(rcClient, rcRBBox));

		CPDF_Rect rcContents = rcClient;
		rcContents.top = rcAuthor.bottom - POPUP_ITEM_HEAD_BOTTOM;
		rcContents.left += 3.0f;
		rcContents.right -= 3.0f;
		if (m_pContentsBar->IsVisible())
			rcContents.right -= PWL_SCROLLBAR_WIDTH;
		rcContents.bottom += 14.0f;
		rcContents.Normalize();
		m_pContents->Move(rcContents, FALSE, FALSE);
		m_pContents->SetVisible(CPWL_Utils::ContainsRect(rcClient, rcContents));

		CPDF_Rect rcContentsBar = rcContents;
		rcContentsBar.right = rcClient.right - 3.0f;
		rcContentsBar.left = rcContentsBar.right - PWL_SCROLLBAR_WIDTH;
		rcContentsBar.Normalize();
		m_pContentsBar->Move(rcContentsBar, TRUE, FALSE);
		
		m_rcCaption = rcClient;
		m_rcCaption.bottom = rcContents.top;
	}

	m_bResizing = FALSE;
}