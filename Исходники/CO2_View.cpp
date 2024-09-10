void CCO2_View::Get_CO2_Temperature_unit(CString &strTemp)
{
	UINT uint_temp=GetOEMCP();//get system is for chinese or english
	if(uint_temp!=936 && uint_temp!=950)
	{
		if(product_register_value[MODBUS_DEGC_OR_F]==0)	//121
		{
			strTemp.Format(_T("%cC"),176);
		}
		else
		{
			strTemp.Format(_T("%cF"),176);
		}
	}
	else
	{
		//Chinese.
		if(product_register_value[MODBUS_DEGC_OR_F]==0)//121
		{
			strTemp=_T("℃");
		}
		else
		{
			strTemp=_T("℉");
		}
	}
}