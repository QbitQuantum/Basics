/////////////////////////////////////////////////////////////////////////////
// Default constructor
//
// The default constructor extracts the adaptor "friendly name" from the
// program name in the registry (where it is put by the DECLARE_REGISTRY
// macro. 
// Function is NOT MODIFIED for the simple adaptor.
/////////////////////////////////////////////////////////////////////////////
Cadvantechadapt::Cadvantechadapt()
{
	if (ConstructorName[0]=='\0')
	{
		LPOLESTR str=NULL;
		HRESULT res = OleRegGetUserType( CLSID_advantechadapt,
			USERCLASSTYPE_SHORT, &str );
		if (SUCCEEDED(res)) // if this fails the else probaby will to..
		{
			StringToLower(str,ConstructorName);
		}
		else
		{
			wcscpy(ConstructorName,L"Constructor Name not found!!!");
		}
		CoTaskMemFree(str);
	}
} // end of default constructor