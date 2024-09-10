bool CExcelDOMStripperStrategy::Excel2007MarkedAsFinal(IDispatchPtr spDispWorkbook)
{
	if (Excel2007(spDispWorkbook))
	{
		DISPID dispid = 0;
		LPOLESTR propertyName = L"Final";
		HRESULT hr = spDispWorkbook->GetIDsOfNames(IID_NULL, &propertyName, 1, LOCALE_SYSTEM_DEFAULT, &dispid);
		if(FAILED(hr))
		{
			std::tostringstream msg; 
			msg << _T("Failed to obtain the dispid of the [Final] property on the Workbook.") << std::ends;
			throw Workshare::Com::ComException(msg.str().c_str(), hr, spDispWorkbook);
		}

		short value = 0;
		hr = _com_dispatch_propget(spDispWorkbook, dispid, VT_BOOL, (void*)&value);
		if(FAILED(hr))
		{
			std::tostringstream msg; 
			msg << _T("Failed to obtain the [Final] property on the Workbook.") << std::ends;
			throw Workshare::Com::ComException(msg.str().c_str(), hr, spDispWorkbook);
		}
		
		if (value == -1)
			return true;
	}

	return false;
}