BOOL DFUSheet::OnInitDialog() 
{
	// Pass on to the base class first
	BOOL result = CPropertySheet::OnInitDialog();
	
	// Modified behaviour for development mode
	if (developmentMode)
	{
		// Add a minimize icon
		ModifyStyle(0, WS_MINIMIZEBOX, 0);
		GetSystemMenu(false)->AppendMenu(MF_STRING, SC_MINIMIZE, _T("Minimize"));
	}
	
	// Return the result
	return result;
}