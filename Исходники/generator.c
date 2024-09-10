static void OutputValues(parsercontext *p, size_t size, size_t night, size_t density, size_t touchscreen, size_t keyboard, size_t textinput, size_t navstate, size_t navmethod)
{
	tchar_t Path[MAXPATH];
	textwriter Output, StringOutput;

	stprintf_s(Path, TSIZEOF(Path), T("values")
		T("-%s")
//		T("-%s")
		T("-%s")
//		T("-%s")
//		T("-%s")
//		T("-%s")
//		T("-%s")
//		T("-%s")
		,Size[size]
//		,Night[night]
		,Density[density]
//		,TouchScreen[touchscreen]
//		,Keyboard[keyboard]
//		,TextInput[textinput]
//		,NavigationState[navstate]
//		,NavigationMethod[navmethod]
		);

	FolderCreate((nodecontext*)p, Path);
	if (PathIsFolder((nodecontext*)p, Path))
	{
		tcscat_s(Path, TSIZEOF(Path), T("/resinfo.xml"));
		memset(&Output,0,sizeof(Output));
		Output.Stream = StreamOpen(p, Path, SFLAG_WRONLY|SFLAG_CREATE);

		TextElementXML(p, &Output, T("resources"));

		TextElementBegin(&StringOutput, &Output, T("string"));
		TextAttrib(&StringOutput, T("name"), T("res_size"), TYPE_STRING);
		TcsToUpper(Path, TSIZEOF(Path), Size[size]);
		TextElementEndData(&StringOutput, Path);

		TextElementBegin(&StringOutput, &Output, T("string"));
		TextAttrib(&StringOutput, T("name"), T("res_night"), TYPE_STRING);
		TcsToUpper(Path, TSIZEOF(Path), Night[night]);
		TextElementEndData(&StringOutput, Path);

		TextElementBegin(&StringOutput, &Output, T("string"));
		TextAttrib(&StringOutput, T("name"), T("res_density"), TYPE_STRING);
		TcsToUpper(Path, TSIZEOF(Path), Density[density]);
		TextElementEndData(&StringOutput, Path);

		TextElementBegin(&StringOutput, &Output, T("string"));
		TextAttrib(&StringOutput, T("name"), T("res_touchscreen"), TYPE_STRING);
		TcsToUpper(Path, TSIZEOF(Path), TouchScreen[touchscreen]);
		TextElementEndData(&StringOutput, Path);

		TextElementBegin(&StringOutput, &Output, T("string"));
		TextAttrib(&StringOutput, T("name"), T("res_keyboard"), TYPE_STRING);
		TcsToUpper(Path, TSIZEOF(Path), Keyboard[keyboard]);
		TextElementEndData(&StringOutput, Path);

		TextElementBegin(&StringOutput, &Output, T("string"));
		TextAttrib(&StringOutput, T("name"), T("res_textinput"), TYPE_STRING);
		TcsToUpper(Path, TSIZEOF(Path), TextInput[textinput]);
		TextElementEndData(&StringOutput, Path);

		TextElementBegin(&StringOutput, &Output, T("string"));
		TextAttrib(&StringOutput, T("name"), T("res_navstate"), TYPE_STRING);
		TcsToUpper(Path, TSIZEOF(Path), NavigationState[navstate]);
		TextElementEndData(&StringOutput, Path);

		TextElementBegin(&StringOutput, &Output, T("string"));
		TextAttrib(&StringOutput, T("name"), T("res_navmethod"), TYPE_STRING);
		TcsToUpper(Path, TSIZEOF(Path), NavigationMethod[navmethod]);
		TextElementEndData(&StringOutput, Path);

		TextElementEnd(&Output);

		StreamClose(Output.Stream);
	}
}