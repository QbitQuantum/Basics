int CSDMdlMachChamferAngCheck::CheckAction(void *pData, const CheckRule &checkRule, CheckResult &checkResult)
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
	if (checkRule.arrRuleContent.GetCount() < 1)
	{
		checkResult.nResultType = CHECK_RESULT_INVALID_INPUT;
		return checkResult.nResultType;
	}

	CStringArray arrChamferAng;
	CStringToCStringArray(checkRule.arrRuleContent[0], arrChamferAng);
	for (int i = 0; i < arrChamferAng.GetSize(); i++)
	{
		if (IsNumber(arrChamferAng.GetAt(i)) == FALSE || _wtof(arrChamferAng.GetAt(i)) < 0 || DEQUAL(_wtof(arrChamferAng.GetAt(i)),0.0))
		{
			checkResult.nResultType = CHECK_RESULT_INVALID_INPUT;
			return CHECK_RESULT_INVALID_INPUT;
		}
	}

	ChamferFeaVisitAngData visitData;
	visitData.nResultType = CHECK_RESULT_NO_ERROR;
	visitData.strAngle = checkRule.arrRuleContent[0];

	ProError status;

	status = ProSolidFeatVisit((ProSolid)pMdl,
		ChamferFeaVisitAction,
		ChamferFeaFilterAction,
		&visitData);

	checkResult.arrErrorItems.RemoveAll();
	ErrorItem errItem;
	for (int i=0; i<visitData.arrChamferAngErrorIDs.GetSize(); i++)
	{
		errItem.nID = visitData.arrChamferAngErrorIDs[i];
		errItem.nType = PRO_FEATURE;
		errItem.pOwner = pMdl;
		checkResult.arrErrorItems.Add(errItem);
	}
	checkResult.nResultType = visitData.nResultType;
	return visitData.nResultType;
	
}