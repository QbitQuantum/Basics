bool CFit::On_Execute(void)
{
	int i, j,  NrVars;
	vector < double> x, y, StartValue, Result;
	CSG_String	msg;	
	
	CSG_Parameters StartParameters;

	const SG_Char *formel	=	Parameters("FORMEL")->asString();

	Formel.Add_Function(SG_T("NUG"), (TSG_PFNC_Formula_1) NUG, 1, 0);
	Formel.Add_Function(SG_T("SPH"), (TSG_PFNC_Formula_1) SPH, 2, 0);
	Formel.Add_Function(SG_T("EXP"), (TSG_PFNC_Formula_1) EXP, 2, 0);
    Formel.Add_Function(SG_T("LIN"), (TSG_PFNC_Formula_1) LIN, 2, 0);
	
	
	Formel.Set_Formula(formel);
	
	
	if (Formel.Get_Error(msg))
	{
		Message_Add(msg);

		return false;
	}
	
	const SG_Char *uservars = NULL;
	
	uservars = Formel.Get_Used_Variables();
	

	NrVars	=	0;
	for (i = 0; i < SG_STR_LEN(uservars); i++)
	{
		if (uservars[i] >='a' && uservars[i] <= 'z')
		{
			if (uservars[i] != 'x')
				vars[NrVars++] = uservars[i];
		}
	}
	
	vars[NrVars] =(char) 0;
	
	StartParameters.Add_Info_String(NULL, _TL(""), _TL("Formula"), _TL("Formula"), formel);
	
	for (i = 0; i < strlen(vars); i++)
	{
		CSG_String	c(vars[i]);
		StartParameters.Add_Value(NULL, c, c, _TL("Start Value"), PARAMETER_TYPE_Double, 1.0);
	}
	
	Dlg_Parameters(&StartParameters, _TL("Start Values"));
	
	for (i = 0; i < strlen(vars); i++)
	{
		char c[3];
		sprintf(c, "%c", vars[i]);
		StartValue.push_back(StartParameters(c)->asDouble());
	}
	
	CSG_Table	*pTable	= Parameters("SOURCE")->asTable();
	int Record_Count = pTable->Get_Record_Count();
	
	int	yField		= Parameters("YFIELD")->asInt();
	int	xField		= Parameters("XFIELD")->asInt();
	bool Use_X		= Parameters("USE_X")->asBool();
	
	pTable->Add_Field(_TL("Fit")				, SG_DATATYPE_Double);	
	
	for (i = 0; i < Record_Count; i++)
	{
		CSG_Table_Record *	Record = pTable->Get_Record(i);
		if (Use_X)
		{
			x.push_back(Record->asDouble(xField));
		}
		else
		{
			x.push_back(i);
		}
		
		y.push_back(Record->asDouble(yField));
	}
	
	TLMFit *Fit;
	
	Fit = new TLMFit(x, y, StartValue,  FitFunc);
	
	int max_iter = Parameters("ITER")->asInt();
	double Max_lamda = Parameters("LAMDA")->asInt();
	
	int iter = 0; 
	
	try
	{
		Fit->Fit();
		
		while ((Fit->Alamda() < Max_lamda) &&(iter < max_iter) &&Process_Get_Okay(true))
		{
			Fit->Fit();
			iter++;
		}
	}
	catch (ESingularMatrix &E)
	{
		if (E.Type == 1 || E.Type == 2)
		{
			msg.Printf(_TL("Matrix signular\n"));
			
			Message_Add(msg);
			
			return false;
		}
	}
	
	Result    = Fit->Param();
	
	for (i = 0; i < NrVars; i++)
	{
		Formel.Set_Variable(vars[i], (double) Result[i]);
	}
	
	msg.Printf(_TL("Model Parameters:"));
	Message_Add(msg);
	for (i = 0; i < NrVars; i++)
	{
		msg.Printf(SG_T("%c = %f\n"), vars[i], Result[i]);
		Message_Add(msg);
	}
	
	msg.Printf(_TL("\nRMS  of Residuals (stdfit):\t%f\n"), sqrt(Fit->Chisq()/x.size()));
	Message_Add(msg);
	
	msg.Printf(_TL("Correlation Matrix of the Fit Parameters:\n"));
	Message_Add(msg);
	
	vector< vector < double> > covar = Fit->Covar();
	
	msg.Printf(_TL(""));
	for (j = 0; j < NrVars; j++)
		msg.Printf(SG_T("%s\t%c"), msg.c_str(), vars[j]);
	
	msg.Printf(SG_T("%s\n"), msg.c_str());
	
	Message_Add(msg);
	
	for (i = 0; i < NrVars; i++)
	{
		msg.Printf(SG_T("%c"), vars[i]);
		for (j = 0; j <= i; j++)
		{	
			msg.Printf(SG_T("%s\t%f"), msg.c_str(), covar[i][j]/covar[i][i]);
		}
		msg.Printf(SG_T("%s\n"), msg.c_str());
		
		Message_Add(msg);
	}
	
	int Field_Count  = pTable->Get_Field_Count();
	
	for (i = 0; i < Record_Count; i++)
	{
		CSG_Table_Record *	Record = pTable->Get_Record(i);
		
		Record->Set_Value(Field_Count - 1, Formel.Get_Value(x[i]));
	}

//	API_FREE (uservars);
	return (true);
}