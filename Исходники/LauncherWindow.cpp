void CLauncherWindow::LoadNullLoginPage()
{
	auto document = m_webBrowser.GetDocument();
	if(!document.IsEmpty())
	{
		auto page = GetNullLoginPage();

		HRESULT result = S_OK;

		BSTR documentText = SysAllocString(page.c_str());

		{
			SAFEARRAYBOUND documentBounds = {};
			documentBounds.cElements = 1;
			documentBounds.lLbound = 0;
			auto documentArray = SafeArrayCreate(VT_VARIANT, 1, &documentBounds);
			{
				result = SafeArrayLock(documentArray);
				assert(SUCCEEDED(result));
				auto& elementVar = reinterpret_cast<VARIANT*>(documentArray->pvData)[0];
				elementVar.vt		= VT_BSTR;
				elementVar.bstrVal	= documentText;
				result = SafeArrayUnlock(documentArray);
				assert(SUCCEEDED(result));
			}
			result = document->write(documentArray);
			assert(SUCCEEDED(result));
			SafeArrayDestroy(documentArray);
		}

		SysFreeString(documentText);

		document->close();
	}
}