void ExcelDOMStripper::RemoveExcelLinks(IDispatchPtr spDispatch)
{
	if (spDispatch == 0)
		throw Workshare::ArgumentNullException(_T("spDispatch"), _T("The Worksheet that we want to remove the excel links from is invalid."));

	Excel::_WorksheetPtr spWorksheet = spDispatch;
	if (spWorksheet == 0)
		throw Workshare::Com::ComException(_T("The dispatch instance passed does not implement the Excel::_Worksheet interface"), E_NOINTERFACE);

	try
	{
		_variant_t vtLinkSources(m_spWorkbook->LinkSources((long)Excel::xlLinkTypeExcelLinks));
		if (VT_EMPTY == vtLinkSources.vt)
			return;

		SAFEARRAY *psa = V_ARRAY(&vtLinkSources);
		LONG iLBound, iUBound;
		::SafeArrayGetLBound(psa, 1, &iLBound);
		::SafeArrayGetUBound(psa, 1, &iUBound);
		if (0 == (iUBound - iLBound + 1))
			return;

		Excel::NamesPtr spNames = m_spWorkbook->Names;
		Excel::NamePtr  spName = NULL;
		_variant_t vtCellFormula;
		CStdString sCellFormula, sFirstAddress;
		std::map<CStdString, int> :: iterator mapName;
		int nAddressCount = 0;
		Excel::RangePtr spUsedRange = spWorksheet->UsedRange;
		_variant_t vtWhat(_T("="));
		Excel::RangePtr spCellRange = spUsedRange->Find(vtWhat, vtMissing, (long)Excel::xlFormulas, vtMissing, vtMissing, Excel::xlNext);

		while (spCellRange != 0)
		{
			if (0 == nAddressCount)
				sFirstAddress = spCellRange->GetAddress(vtMissing, vtMissing, Excel::xlA1);

			nAddressCount++;

			vtCellFormula = spCellRange->Formula;
			sCellFormula = vtCellFormula.bstrVal;

			if (_T('=') == sCellFormula[0])
			{
				if (-1 != sCellFormula.Find(_T('[')))
				{
					spCellRange->Formula = spCellRange->Value;
					if (1 == nAddressCount)
						nAddressCount = 0;
					m_linksCount++;

				}
				else if (0 < m_mapNames.size())
				{
					sCellFormula.Delete(0, 1);

					mapName = m_mapNames.find(sCellFormula);
					if (mapName != m_mapNames.end())
					{
						try
						{
							spName = spNames->Item(sCellFormula.c_str());
						}
						catch(...)
						{
							// Should not come here. Because the name is in the map it should also be in the Names collection.
							spName = 0;
						}
						if (spName != 0)
						{
							CStdString sValue = spName->Value;
							if (-1 != sValue.Find(_T('[')))
							{
								spCellRange->Formula = spCellRange->Value;
								mapName->second = 1;
								if (1 == nAddressCount)
									nAddressCount = 0;
							}
						}
					}
				}
			}

			_variant_t vtCellRange((IDispatch*)spCellRange);
			spCellRange = spUsedRange->FindNext(vtCellRange);
			if (spCellRange == 0)
				break;
			if (sFirstAddress == spCellRange->GetAddress(vtMissing, vtMissing, Excel::xlA1))
				break;
		}

		//Links have been updated, now remove them
		CComSafeArray <VARIANT> safeArray(psa);
		for (ULONG i = 1; i <= safeArray.GetCount(); i++)
		{
			_variant_t name(safeArray.GetAt(i));
			VARIANT result;
			VariantInit(&result);
			HRESULT hr = DispatchWrapper(DISPATCH_METHOD, &result, m_spWorkbook, L"BreakLink", 2, _variant_t(Excel::xlLinkTypeExcelLinks), name);
			if (DISP_E_UNKNOWNNAME != hr)
			{
				if (0 != result.boolVal)
					throw Workshare::Com::ComException(_T("Failed to break the link on the Excel document"), E_FAIL);
			}
		}

	}
	catch(Workshare::Exception const&)
	{
		throw;
	}
	catch(...)
	{
		unexpected();
	}
}