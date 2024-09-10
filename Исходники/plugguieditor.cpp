//-----------------------------------------------------------------------------
PluginGUIEditor::~PluginGUIEditor () 
{
	#if WINDOWS
	OleUninitialize ();
	#endif
	#if MAC
	ExitMachOLibrary ();
	#endif
}