void EditorReplaceContent(const FunctionCallbackInfo<Value>& args)
{
	Local<Value> newContent = args[0];

	CComPtr<VirtualPoint> virtualPoint;

	long start, end = 0;

	g_Options.m_selection->get_ActivePoint(&virtualPoint);

	String::Utf8Value utf8Content(newContent);

    // As V8 always returns utf8 string we need to convert it to utf16 before it can be used.
    int contentLen = MultiByteToWideChar(CP_UTF8, NULL, *utf8Content, -1, NULL, 0);
    CAutoPtr<WCHAR> content(new WCHAR[contentLen + 1]);
    MultiByteToWideChar(CP_UTF8, NULL, *utf8Content, -1, content, contentLen + 1);

	if (args.Length() == 0) // no start/end range
	{
		g_Options.m_selection->SelectAll();
		g_Options.m_selection->Delete();
	}
	else if (args.Length() == 1) // only start point specified
	{
		start = (long)args[1].As<Integer>()->Value();
		g_Options.m_selection->MoveToAbsoluteOffset(start + 1);
	}
	else // both start / end specified
	{
		start = (long)args[1].As<Integer>()->Value();
		end = (long)args[2].As<Integer>()->Value();
		g_Options.m_selection->MoveToAbsoluteOffset(start + 1);
		g_Options.m_selection->MoveToAbsoluteOffset(end + 1, TRUE);
		g_Options.m_selection->Delete();
	}

	CComPtr<VirtualPoint> activePoint;
	CComPtr<EditPoint> editPoint;
	g_Options.m_selection->get_ActivePoint(&activePoint);
	activePoint->CreateEditPoint(&editPoint);

    BSTR bstrContent = SysAllocString(content);
    editPoint->Insert(bstrContent);
    SysFreeString(bstrContent);

	if (EmmetAction_MergeLines != g_Options.m_curAction)
	{
		g_Options.m_selection->MoveToAbsoluteOffset(start + 1, TRUE);
		if (g_Options.m_syntax == EmmetSyntax_Html)
			g_Options.m_selection->SmartFormat();
	}
}