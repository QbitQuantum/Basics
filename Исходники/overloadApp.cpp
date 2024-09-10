void OverloadApp::registerFunctions(CefRefPtr<CefListValue> functionNames)
{
	if (_browser != nullptr)
	{
		CefRefPtr<CefV8Context> currentContext = _browser->GetMainFrame()->GetV8Context();
		currentContext->Enter();
		CefRefPtr<CefV8Value> object = currentContext->GetGlobal();

		for (std::size_t i = 0; i < functionNames->GetSize(); i++)
		{
			std::string functionName = functionNames->GetString(i).ToString();
			object->SetValue(functionName, CefV8Value::CreateFunction(functionName, _v8Handler.get()), V8_PROPERTY_ATTRIBUTE_NONE);
			_functionNames.push_back(functionName);
		}

		currentContext->Exit();
	}
	else
	{
		for (std::size_t i = 0; i < functionNames->GetSize(); i++)
		{
			_functionNames.push_back(functionNames->GetString(i).ToString());
		}
	}
}