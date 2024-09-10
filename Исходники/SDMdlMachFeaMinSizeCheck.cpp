int CSDMdlMachFeaMinSizeCheck::CheckAction(void *pData, const CheckRule &checkRule, CheckResult &checkResult) 
{
	ProMdl pMdl = (ProMdl)pData;
	if (NULL == pMdl)
	{
		checkResult.nResultType = CHECK_RESULT_INVALID_MODEL;
		return checkResult.nResultType;
	}

	if (!IsMdlTypeValid(pMdl, checkRule.dwMdlFilter))
	{
		checkResult.nResultType = CHECK_RESULT_INVALID_MODEL;
		return checkResult.nResultType;
	}

	// 检查输入值有效性
	if (checkRule.arrRuleContent.GetCount() < 1 || _wtof(checkRule.arrRuleContent[0]) <= 0 || 
		DEQUAL(_wtof(checkRule.arrRuleContent[0]),0.0))
	{
		checkResult.nResultType = CHECK_RESULT_INVALID_INPUT;
		return checkResult.nResultType;
	}

	FeaMinSizeVisitData VisitData;
	VisitData.nFeaMinSizeResultType = CHECK_RESULT_NO_ERROR;
	VisitData.dMinSizeRatio  = _wtof(checkRule.arrRuleContent[0])/100; 

	ProError status;

	status = ProSolidFeatVisit((ProSolid)pMdl,
		GeoFeaVisitAction,
		GeoFeaFilterAction,
		&VisitData);

	if (status == PRO_TK_E_NOT_FOUND)
	{
		VisitData.nFeaMinSizeResultType = CHECK_RESULT_ITEM_NOT_FOUND;
		return CHECK_RESULT_ITEM_NOT_FOUND;
	}

	checkResult.arrErrorItems.RemoveAll();
	ErrorItem errItem;
	for (int i=0; i<VisitData.arrFeaMinSizeErrorIDs.GetSize(); i++)
	{
		errItem.nID = VisitData.arrFeaMinSizeErrorIDs[i];
		errItem.nType = PRO_FEATURE;
		errItem.pOwner = pMdl;
		checkResult.arrErrorItems.Add(errItem);
	}
	checkResult.nResultType = VisitData.nFeaMinSizeResultType;

	return VisitData.nFeaMinSizeResultType; 
}