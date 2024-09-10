void CodePreview::Unregister()
{
	UnregisterClassA(s_className, _AtlModule.GetResourceInstance());
	
	if(s_normalFont)
	{
		DeleteObject(s_normalFont);
		s_normalFont = 0;
	}

	if(s_boldFont)
	{
		DeleteObject(s_boldFont);
		s_boldFont = 0;
	}
}