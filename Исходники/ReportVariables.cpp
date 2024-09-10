int _tmain(int argc, _TCHAR* argv[])
{
	HRESULT hr = S_OK;
	SolidEdgeFramework::ApplicationPtr pApplication = NULL;
	SolidEdgeFramework::SolidEdgeDocumentPtr pDocument = NULL;
	SolidEdgeFramework::VariablesPtr pVariables = NULL;
	SolidEdgeFramework::VariableListPtr pVariableList = NULL;
	SolidEdgeFramework::variablePtr pVariable = NULL;
	SolidEdgeFrameworkSupport::DimensionPtr pDimension = NULL;

	// Initialize COM.
	::CoInitialize(NULL);

	// Attempt to connect to a running instance of Solid Edge.
	IfFailGo(pApplication.GetActiveObject(L"SolidEdge.Application"));

	// Get a reference to the active document.
	pDocument = pApplication->ActiveDocument;

	if (pDocument != NULL)
	{
		// Get a reference to the Variables.
		pVariables = pDocument->Variables;

		// Get a reference to the VariableList.
		pVariableList = pVariables->Query(L"*", (LONG)SolidEdgeConstants::seVariableNameByBoth, (LONG)SolidEdgeConstants::SeVariableVarTypeBoth);
		
		// Process variables.
		for (LONG i = 1; i <= pVariableList->Count; i++)
		{
			IDispatchPtr pVariableListItem = pVariableList->Item(i);

			// Use helper method to get the object type.
			SolidEdgeConstants::ObjectType objectType = GetObjectType(pVariableListItem);

			// Process the specific variable item type.
			switch (objectType)
			{
			case SolidEdgeConstants::ObjectType::igDimension:
				// Get a reference to the dimension.
				pDimension = pVariableListItem;
				wprintf(L"Dimension: '%s' = '%f'\n", pDimension->DisplayName.GetBSTR(), pDimension->Value);
				break;
			case SolidEdgeConstants::ObjectType::igVariable:
				// Get a reference to the variable.
				pVariable = pVariableList->Item(i);
				wprintf(L"Variable: '%s' = '%f'\n", pVariable->DisplayName.GetBSTR(), pVariable->Value);
				break;
			}
		}
	}
	else
	{
		wprintf(L"No active document.\n");
	}

Error:
	pDimension = NULL;
	pVariable = NULL;
	pVariableList = NULL;
	pVariables = NULL;
	pDocument = NULL;
	pApplication = NULL;

	// Uninitialize COM.
	::CoUninitialize();

	return 0;
}