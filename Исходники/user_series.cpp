void Read_Parameter(int i_iArg_Count,const char * i_lpszArg_Values[], const char * i_lpszOption_Name, const double &i_dDefault_Decay, PARAMETER_SET	& o_cParameter)
{
	double dNan = nan("");
	char lpszOption_String[64];
	char	lpszType[32];

	o_cParameter.dRef25 =	xParse_Command_Line_Dbl(i_iArg_Count,i_lpszArg_Values,i_lpszOption_Name,dNan);
	sprintf(lpszOption_String,"%s-decay",i_lpszOption_Name);
	o_cParameter.dDecay =	xParse_Command_Line_Dbl(i_iArg_Count,i_lpszArg_Values,lpszOption_String,i_dDefault_Decay);
	sprintf(lpszOption_String,"%s-law",i_lpszOption_Name);
	xParse_Command_Line_String(i_iArg_Count,i_lpszArg_Values,lpszOption_String,lpszType,sizeof(lpszType),NULL);
	o_cParameter.Set_Type(lpszType);
	sprintf(lpszOption_String,"%s-extreme",i_lpszOption_Name);
	o_cParameter.dRef_Extreme =	xParse_Command_Line_Dbl(i_iArg_Count,i_lpszArg_Values,lpszOption_String,0.0);

}