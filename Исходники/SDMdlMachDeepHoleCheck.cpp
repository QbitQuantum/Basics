int CSDMdlMachDeepHoleCheck::CheckAction(void *pData, const CheckRule &checkRule, CheckResult &checkResult) 
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

	DeepHoleFeaVisitData DeepHoleVisitData;
	DeepHoleVisitData.nDeepHoleResultType = CHECK_RESULT_NO_ERROR;
	DeepHoleVisitData.dDeepHoleRatio  = _wtof(checkRule.arrRuleContent[0]);
	ProError status;

	status = ProSolidFeatVisit((ProSolid)pMdl,
		DeepHoleFeaVisitAction,
		NULL,
		&DeepHoleVisitData);

	checkResult.arrErrorItems.RemoveAll();
	ErrorItem errItem;
	for (int i=0; i<DeepHoleVisitData.arrDeepHoleErrorIDs.GetSize(); i++)
	{
		errItem.nID = DeepHoleVisitData.arrDeepHoleErrorIDs[i];
		errItem.nType = PRO_FEATURE;
		errItem.pOwner = pMdl;
		checkResult.arrErrorItems.Add(errItem);
	}
	checkResult.nResultType = DeepHoleVisitData.nDeepHoleResultType;

	return DeepHoleVisitData.nDeepHoleResultType; 
}