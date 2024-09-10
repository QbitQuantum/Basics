void CRegenerationDlg::ExecutingRule(int nRuleType,int nSyntacticCategory,int nGroup,int nRule)
{
	CString strRuleType,strSyncat,strGroup,strNumber;
	wchar_t c[5];
	CWnd* pWnd;

	switch (nRuleType)
	{
	case 1:
		strRuleType=L"Feature Copying";
		break;
	case 2:
		strRuleType=L"Collocation Correction";
		break;
	case 3:
		strRuleType=L"Structural Adjustment";
		break;
	case 4:
		strRuleType=L"Spellout";
		break;
	case 5:
		strRuleType=L"Word Morphophonemic";
		break;
	case 6:
		strRuleType=L"Clitic";
		break;
	case 7:
		strRuleType=L"Constituent Movmement";
		break;
	case 8:
		strRuleType=L"Phrase Structure";
		break;
	case 9:
		strRuleType=L"Find/Replace";
		break;
	case 10:
		strRuleType=L"Structural Adjustment";
		break;
	case 11:
		strRuleType=L"Affix Hopping";
		break;
	case 12:
		strRuleType=L"Theta Grid Adjustment";
		break;
	case 13:
		strRuleType=L"Pronoun and Switch Reference Identification";
		break;
	case 14:
		strRuleType=L"Pronoun and Switch Reference Spellout";
		break;
	default:
		strRuleType=L"";
		break;
	}
	switch (nSyntacticCategory)
	{
	case 1:
		strSyncat=L"Nouns";
		break;
	case 2:
		strSyncat=L"Verbs";
		break;
	case 3:
		strSyncat=L"Adjectives";
		break;
	case 4:
		strSyncat=L"Adverbs";
		break;
	case 5:
		strSyncat=L"Adpositions";
		break;
	case 6:
		strSyncat=L"Conjunctions";
		break;
	case 7:
		strSyncat=L"Pronouns";
		break;
	case 8:
		strSyncat=L"Particles";
		break;
	case 101:
		strSyncat=L"Noun Phrases";
		break;
	case 102:
		strSyncat=L"Verb Phrases";
		break;
	case 103:
		strSyncat=L"Adjective Phrases";
		break;
	case 104:
		strSyncat=L"Adverb Phrases";
		break;
	case 105:
		strSyncat=L"Clauses";
		break;
	case 106:
		strSyncat=L"User Defined";
		break;
	case 107:
		strSyncat=L"All Categories";
		break;
	default:
		strSyncat=L"";
		break;
	}
	if (nRuleType==9 || nRuleType==10 || nRuleType==13) strSyncat=L"";   //RRs and Find/Replace rules and Pronoun ID rules don't have syncats
	_itow(nGroup,c,10);
	strGroup=c;
	if (nGroup==0) strGroup=L"";
	_itow(nRule,c,10);
	strNumber=c;
	if (nRule==0) strNumber=L"";
	pWnd=GetDlgItem(IDC_EDITRULETYPE);
	pWnd->SetWindowText(strRuleType);
	pWnd->RedrawWindow();
	pWnd=GetDlgItem(IDC_EDITRULESYNCAT);
	pWnd->SetWindowText(strSyncat);
	pWnd->RedrawWindow();
	pWnd=GetDlgItem(IDC_EDITRULEGROUP);
	pWnd->SetWindowText(strGroup);
	pWnd->RedrawWindow();
	pWnd=GetDlgItem(IDC_EDITRULENUMBER);
	pWnd->SetWindowText(strNumber);
	pWnd->RedrawWindow();
}