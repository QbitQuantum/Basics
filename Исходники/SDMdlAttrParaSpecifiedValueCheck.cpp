// 检查开始
int CSDMdlAttrParaSpecifiedValueCheck::CheckAction(void *pData, const CheckRule &checkRule, CheckResult &checkResult)
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

	// 模型是否符合过滤器要求
	if (!IsFilterValid(checkRule.strRuleName, pMdl))
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

	//-----------------------------------------------------------------------------------

	ProModelitem mdlItem;
	ProMdlToModelitem(pMdl, &mdlItem);

	checkResult.arrErrorItems.RemoveAll();

	// 解析参数
	CStringArray arrItems;
	CStringToCStringArray(checkRule.arrRuleContent[0], arrItems, L";");
	CString strParaName;
	int nParaType;
	CString strParaValue;
	BOOL bDesignation;
	for (int i = 0; i < arrItems.GetSize(); i ++)
	{
		strParaName = arrItems[i].Left(arrItems[i].Find(L"("));
		int nCount = arrItems[i].Find(L")") - arrItems[i].Find(L"(")-1;
		CString strProperty;
		strProperty = arrItems[i].Mid(arrItems[i].Find(L"(") + 1, nCount);
		CStringArray arrPropertys;
		CStringToCStringArray(strProperty, arrPropertys, L",");
		nParaType = _wtoi(arrPropertys[0]);
		strParaValue = arrPropertys[1];
		ParseParaValue(mdlItem, strParaValue, strParaValue);
		bDesignation = _wtoi(arrPropertys[2]);
		
		ProName paraname;
		wcsncpy_s(paraname, PRO_NAME_SIZE, (LPCTSTR)strParaName, _TRUNCATE);
		ProParameter para;

		// 判断参数是否存在
		ErrorItem item;
		item.strItemName = strParaName;
		item.nID = i;
		if (GetSDParameter(&mdlItem, paraname, para))
		{
			// 检查参数类型
			ProParamvalue proval;
			ProParameterValueGet(&para, &proval);
			int nType = GetParaType(proval.type);
			if (nType != nParaType)
			{
				item.nType = PARAERROR_TYPE;
				checkResult.arrErrorItems.Add(item);
			}
			else
			{
				// 检查参数值
				if (PARAM_STRING == nParaType)
				{
					if (strParaValue.Compare(proval.value.s_val) != 0)
					{
						item.nType = PARAERROR_VALUE;
						checkResult.arrErrorItems.Add(item);
						continue;
					}
				}
				else if (PARAM_REAL == nParaType)
				{
					if (!DEQUAL(proval.value.d_val, _wtof(strParaValue)))
					{
						item.nType = PARAERROR_VALUE;
						checkResult.arrErrorItems.Add(item);
						continue;
					}
				}
				else if (PARAM_INTEGER == nParaType)
				{
					if (proval.value.i_val != _wtoi(strParaValue))
					{
						item.nType = PARAERROR_VALUE;
						checkResult.arrErrorItems.Add(item);
						continue;
					}
				}
				else if (PARAM_BOOL == nParaType)
				{
					if (proval.value.l_val != _wtoi(strParaValue))
					{
						item.nType = PARAERROR_VALUE;
						checkResult.arrErrorItems.Add(item);
						continue;
					}
				}
				// 检查是否指定
				ProBoolean designation;
				ProParameterDesignationVerify(&para, &designation);
				if (bDesignation != designation)
				{
					item.nType = PARAERROR_DESIGNATION;
					checkResult.arrErrorItems.Add(item);
				}
			}
		}
		else
		{
			item.nType = PARAERROR_NOEXIST;
			checkResult.arrErrorItems.Add(item);
		}
	}

	if (checkResult.arrErrorItems.GetCount() > 0)
		checkResult.nResultType = CHECK_RESULT_ERROR_VALUE;
	else
		checkResult.nResultType = CHECK_RESULT_NO_ERROR;

	return checkResult.nResultType;
}