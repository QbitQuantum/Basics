/** Accesses the correct visual studio instance if possible. */
bool AccessVisualStudio(CComPtr<EnvDTE::_DTE>& OutDTE, const FString& InSolutionPath, const TArray<FVSAccessorModule::VisualStudioLocation>& InLocations)
{
	bool bSuccess = false;

	// Open the Running Object Table (ROT)
	IRunningObjectTable* RunningObjectTable;
	if (SUCCEEDED(GetRunningObjectTable(0, &RunningObjectTable)) &&
		RunningObjectTable)
	{
		IEnumMoniker* MonikersTable;
		RunningObjectTable->EnumRunning(&MonikersTable);
		MonikersTable->Reset();

		// Look for all visual studio instances in the ROT
		IMoniker* CurrentMoniker;
		while (!bSuccess && MonikersTable->Next(1, &CurrentMoniker, NULL) == S_OK)
		{
			IBindCtx* BindContext;
			LPOLESTR OutName;
			CComPtr<IUnknown> ComObject;
			if (SUCCEEDED(CreateBindCtx(0, &BindContext)) &&
				SUCCEEDED(CurrentMoniker->GetDisplayName(BindContext, NULL, &OutName)) &&
				IsVisualStudioMoniker(FString(OutName), InLocations) &&
				SUCCEEDED(RunningObjectTable->GetObject(CurrentMoniker, &ComObject)))
			{
				CComPtr<EnvDTE::_DTE> TempDTE;
				TempDTE = ComObject;
				
				// Get the solution path for this instance
				// If it equals the solution we would have opened above in RunVisualStudio(), we'll take that
				CComPtr<EnvDTE::_Solution> Solution;
				LPOLESTR OutPath;
				if (SUCCEEDED(TempDTE->get_Solution(&Solution)) &&
					SUCCEEDED(Solution->get_FullName(&OutPath)))
				{
					FString Filename(OutPath);
					FPaths::NormalizeFilename(Filename);

					if( Filename == InSolutionPath )
					{
						OutDTE = TempDTE;
						bSuccess = true;
					}
				}
			}
			BindContext->Release();
			CurrentMoniker->Release();
		}
		MonikersTable->Release();
		RunningObjectTable->Release();
	}

	return bSuccess;
}