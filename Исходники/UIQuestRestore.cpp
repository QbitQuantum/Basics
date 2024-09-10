void CUIQuestRestore::UpdateContent()
{
	CTString strTemp;
	int nCount = GAMEDATAMGR()->GetQuest()->GetRestoreCount();
	int nNum = 1;
	COLOR color = 0xFFFFFFFF;
	// 안내
	if (m_pContent != NULL)
	{
		color = m_pContent->GetTextColor();
		strTemp.PrintF( _S( 4815 , "%d 개의 포기된 퀘스트가 모두 복구 되었습니다. NPC를 통해 퀘스트를 다시 받으시기 바랍니다."), nCount);
		m_pContent->SetText(strTemp, color);
	}

	// 리스트 내용
	if (m_plistContent == NULL)
		return;

	m_plistContent->DeleteAllListItem();

	if (m_plistScroll != NULL)
		m_plistScroll->SetScrollPos(0);

	std::vector<Quest::stRestoreInfo>::const_iterator iter = GAMEDATAMGR()->GetQuest()->GetRestoreQuestList().begin();
	std::vector<Quest::stRestoreInfo>::const_iterator iter_end = GAMEDATAMGR()->GetQuest()->GetRestoreQuestList().end();

	for (; iter != iter_end; ++iter)
	{
		CQuestStaticData* pQuestDD = CQuestStaticData::getData((*iter).iQuestIndex);
		if (pQuestDD == NULL)
			continue;
		// 퀘스트 이름
		CUITextBox* pTextBox = (CUITextBox*)m_pDesign->CloneRestoreQuest();

		if (pTextBox != NULL)
		{
			color = pTextBox->GetTextColor();
			strTemp.PrintF("%d. %s", nNum, pQuestDD->GetTitle());
			pTextBox->SetText(strTemp, color, TRUE);
			m_plistContent->AddListItem(pTextBox);
		}		

		// NPC 이름
		CUIText* pText = (CUIText*)m_pDesign->CloneRestoreNpc();

		if (pText != NULL)
		{
			// Name
			if (pQuestDD->startType == QSTART_NPC)
			{
				CMobData* pNpc = CMobData::getData(pQuestDD->startData);

				strTemp.PrintF("<%s>", pNpc->GetName());
			}
			else
			{
				CTString strTemp2;
				strTemp2.PrintF(_S(457, "시스템"));
				strTemp.PrintF("<%s>", strTemp2);				
			}

			pText->SetText(strTemp);
			m_plistContent->AddListItem(pText);
		}

		nNum++;
	}

	int nMaxItem = m_plistContent->getListItemCount();
	m_plistContent->UpdateScroll(nMaxItem);
	m_plistContent->UpdateList();

	int nShowCnt = m_plistContent->GetItemShowNum();

	if (m_plistScroll != NULL)
		m_plistScroll->SetItemsPerPage(nShowCnt);
}