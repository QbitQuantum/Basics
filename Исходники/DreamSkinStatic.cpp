BOOL CDreamSkinStatic::InitialClass()
{
	//Get the default window proc for this class
	WNDCLASSW clsStaticDefault;
	if(!GetClassInfoW(GetModuleHandle(NULL), DEFAULT_STATIC_CLASSNAME_W, &clsStaticDefault))
	{
		//Get class info failed
		//TODO: add error handle code
		return FALSE;
	}
	s_DefaultWindowProc = clsStaticDefault.lpfnWndProc;

	GetDefaultSkin(&s_SkinStatic);

	return TRUE;
}