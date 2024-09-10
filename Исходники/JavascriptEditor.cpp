void FJavascriptEditorModule::StartupModule()
{
#if WITH_EDITOR	
	auto Isolate = NewObject<UJavascriptIsolate>();
	auto Context = Isolate->CreateContext();
	
	JavascriptContext = Context;
	JavascriptContext->AddToRoot();

	JavascriptContext->SetContextId(TEXT("Editor"));

	Tick = NewObject<UJavascriptEditorTick>(JavascriptContext);
	JavascriptContext->Expose(TEXT("Root"), Tick);
	Tick->AddToRoot();

	if (!IsRunningCommandlet())
	{
		FScopedTransaction Transaction(NSLOCTEXT("UnrealEd", "UnrealJS", "Javascript action"));
		FEditorScriptExecutionGuard ScriptGuard;

		Context->RunFile("editor.js");
	}

	bRegistered = true;
	
	FCoreDelegates::OnPreExit.AddRaw(this, &FJavascriptEditorModule::Unregister);
#endif
}