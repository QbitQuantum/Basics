__declspec(dllexport) void ShowDiscoveryDialogEx(IDispatch* pDocument, HWND hParent)
{
	try
	{
		::CoInitialize( 0 );

		try
		{
			CMWDiscovery discovery(pDocument);
			if(hParent)
			{
				discovery.m_hwnd = hParent;
			}

			discovery.SetHelpFile(CGeneral::DefaultHelpFileTitle( AppWorkshare ));
			discovery.DisplayDiscovery();	
		}
		catch(Workshare::Exception& e)
		{
			LOG_WS_ERROR_RESULT(e);
		}
		catch(_com_error& e)
		{
			LOG_WS_ERROR_RESULT(e);
		}
		catch(...)
		{
			LogUnexpected();
		}
		
		CoFreeUnusedLibraries();
		::CoUninitialize();
	}
	catch(Workshare::Exception& e)
	{
		LOG_WS_ERROR_RESULT(e);
	}
	catch(_com_error& e)
	{
		LOG_WS_ERROR_RESULT(e);
	}
	catch(...)
	{
		LogUnexpected();
	}
}