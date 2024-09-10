//-----------------------------------------------------------------------------
// AEffGUIEditor Implementation
//-----------------------------------------------------------------------------
AEffGUIEditor::AEffGUIEditor (void* pEffect) 
: AEffEditor ((AudioEffect*)pEffect)
, inIdleStuff (false)
{
	((AudioEffect*)pEffect)->setEditor (this);
	systemWindow = 0;
	lLastTicks   = getTicks ();

	#if WINDOWS
	OleInitialize (0);
	#endif
	#if MAC
	InitMachOLibrary ();
	#endif
}