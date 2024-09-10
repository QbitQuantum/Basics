ScriptThread::~ScriptThread()
{
	AtlTrace("Destroying script thread");
	if (pScript)
	{
		pScript->Release();
		pScript = NULL;
	}
}