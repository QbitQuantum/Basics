int CExpressionCaculator::AddVariable(const char * VarName,int type, double value,const char * StrValue)
{	
	CVariable * pVar=m_VarList.GetObject(VarName);
	if(pVar==NULL)
	{
		UINT ID=m_VarList.NewObject(&pVar,VarName);
		if(ID)
		{
			pVar->ID=ID;
			strncpy_0(pVar->name,MAX_IDENTIFIER_LENGTH+1,VarName,MAX_IDENTIFIER_LENGTH);
			_strupr_s(pVar->name,MAX_IDENTIFIER_LENGTH);
			pVar->type=type;
			pVar->value=value;
			if(StrValue)
				pVar->StrValue=StrValue;
			return 0;
		}

		return 2;
	}	
	return 1;
}