int __stdcall debugeventplugin(LPDEBUG_EVENT DebugEvent)
{
	//Note, because this is called from a different thread than the mainthread, the thread un-safe ShowMessage is better not used.
	MessageBoxA(0,"A debug event has happened. You could do some editing of the context here...","Debug Event Plugin Example", MB_OK);
	return 0; //If you return 1 you will have to call ContinueDebugEvent yourself.
}