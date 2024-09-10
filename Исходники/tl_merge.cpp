//---------------------------------------------------------
CTL_Merge::CTL_Merge(void)
{
	//-----------------------------------------------------
	Set_Name		(SG_T("Merge Translation Files"));

	Set_Author		(SG_T("O. Conrad (c) 2010"));

	Set_Description	(SG_T(""));

	//-----------------------------------------------------
	CSG_String	Filter;
	
	Filter.Printf(SG_T("%s|*.lng;*.txt|%s|*.lng|%s|*.txt|%s|*.*"),
		SG_T("All recognized Files"),
		SG_T("SAGA Translation File (*.lng)"),
		SG_T("Text Files (*.txt)"),
		SG_T("All Files")
	);

	//-----------------------------------------------------
	Parameters.Add_FilePath(
		NULL	, "TARGET"	, SG_T("Target"),
		SG_T(""),
		Filter, NULL, true
	);

	Parameters.Add_FilePath(
		NULL	, "FILES"	, SG_T("Files"),
		SG_T(""),
		Filter, NULL, false, false, true
	);
}