String ScriptEngine::GetErrorString()
{
	String ret = "";

	if (_ptr != NULL)
	{
		try{
			ComPtr<IScriptError> pError(_ptr->GetError());
			
			if (!pError.IsEmpty())
			{
				_bstr_t desc = _bstr_t("Error: ") + pError->GetDescription() + _bstr_t(", ");
				desc += pError->GetText() + _bstr_t("; in line ");
				desc += _bstr_t(pError->GetLine());
				ret = (LPCTSTR)desc;
				pError->Clear();
			}
		}
		catch (_com_error& e)
		{
			//TRACE((LPSTR)e.Description());
			//TRACE((LPSTR)"\n");
		}
	}
	return ret;
}