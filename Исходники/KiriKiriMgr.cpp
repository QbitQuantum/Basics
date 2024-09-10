//////////////////////////////////////////////////////////////////////////
//
// 이전 버전과의 호환을 위한 옵션 마이그레이션
//
//////////////////////////////////////////////////////////////////////////
BOOL CATCodeMgr::AdjustOption(COptionNode* pRootNode)
{
	if(NULL == pRootNode) return FALSE;
	
	ResetOption();
	MigrateOption(pRootNode);

	//FORCEFONT,HOOK(0x00434343,TRANS([ESP+0x4],ANSI,ALLSAMETEXT))
	BOOL bRetVal = TRUE;

	int cnt = pRootNode->GetChildCount();
	for(int i=0; i<cnt; i++)
	{
		COptionNode* pNode = pRootNode->GetChild(i);
		CString strValue = pNode->GetValue().MakeUpper();
		
		// FORCEFONT 옵션
		if(strValue == _T("FORCEFONT"))
		{
			COptionNode* pLevelNode = pNode->GetChild(0);
			m_nFontLoadLevel = _ttoi(pLevelNode->GetValue().Trim());
		}
		// FIXFONTSIZE 옵션
		else if(strValue == _T("FIXFONTSIZE"))
		{
			m_bFixedFontSize = TRUE;
		}
		// FONT 옵션
		else if(strValue == _T("FONT") && pNode->GetChildCount() == 2)
		{
			// 폰트 페이스명
			COptionNode* pFontFaceNode = pNode->GetChild(0);
			if(pFontFaceNode && m_strFontFace != pFontFaceNode->GetValue())
			{
				// 현재 모아놓은 폰트 객체들 해제
				for(map<long, HFONT>::iterator iter = m_mapFonts.begin();
					iter != m_mapFonts.end();
					iter++)
				{
					DeleteObject(iter->second);
				}
				m_mapFonts.clear();

				// 새로운 폰트 페이스 설정
				m_strFontFace = pFontFaceNode->GetValue();
			}

			// 폰트 사이즈
			COptionNode* pFontSizeNode = pNode->GetChild(1);
			if(pFontSizeNode)
			{
				m_lFontSize = (long)_ttoi(pFontSizeNode->GetValue());
			}
		}
		// ENCODEKOR 옵션
		else if(strValue == _T("ENCODEKOR"))
		{
			m_bEncodeKorean = TRUE;
		}
		// HOOK 노드
		else if(strValue == _T("HOOK"))
		{
			BOOL bHookRes = HookFromOptionNode(pNode);
			if(FALSE == bHookRes) m_listRetryHook.push_back(pNode);
		} // HOOK 노드 끝
	}

	return bRetVal;
}