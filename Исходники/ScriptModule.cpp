bool ScriptModule::Initialize()
{
	Uninitialize();
	mScriptBuilder = new CScriptBuilder();
	mScriptBuilder->SetIncludeCallback(OnInclude, nullptr);

	mScriptBuilder->StartNewModule(ScriptEngine::Instance().GetScriptEngine(), mName.c_str());
	mScriptModule = mScriptBuilder->GetModule();



	return true;
}