// Output a string to the debugger.
MF_API void MFDebug_Message(const char *pMessage)
{
	FujiModule *pModule = (FujiModule*)pp::Module::Get();
	Fuji *pInstance = pModule->GetInstance();
	if(pInstance)
		pInstance->PostMessage(pp::Var(pMessage));
}