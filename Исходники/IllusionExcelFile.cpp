CString IllusionExcelFile::GetCellString(long irow, long icolumn)
{

	COleVariant vResult;
	CString str;
	//字符串
	if (already_preload_ == FALSE)
	{
		excel_current_range_.ReleaseDispatch();
		excel_current_range_.AttachDispatch(excel_current_ranges_.get_Item (COleVariant((long)irow),COleVariant((long)icolumn)).pdispVal, true);
		vResult =excel_current_range_.get_Value2();
	}
	//如果数据依据预先加载了
	else
	{
		long read_address[2];
		VARIANT val;
		read_address[0] = irow;
		read_address[1] = icolumn;
		ole_safe_array_.GetElement(read_address, &val);
		vResult = val;
	}

	if(vResult.vt == VT_BSTR)
	{
		str=vResult.bstrVal;
	}
	//整数
	else if (vResult.vt==VT_INT)
	{
		str.Format(_T("%d"),vResult.pintVal);
	}
	//8字节的数字 
	else if (vResult.vt==VT_R8)     
	{
		str.Format(_T("%0.0f"),vResult.dblVal);
	}
	//时间格式
	else if(vResult.vt==VT_DATE)    
	{
		SYSTEMTIME st;
		VariantTimeToSystemTime(vResult.date, &st);
		CTime tm(st); 
		str=tm.Format(_T("%Y-%m-%d"));

	}
	//单元格空的
	else if(vResult.vt==VT_EMPTY)   
	{
		str=_T("");
	}  

	return str;
}