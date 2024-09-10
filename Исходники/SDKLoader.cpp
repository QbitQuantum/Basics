void SDKLoader::LoadSDK(queue<Task*>* taskQueue)
{
	JsValueRef global;
	JsGetGlobalObject(&global);

	JsValueRef game;
	JsCreateObject(&game);
	Js::AddPropertyToObject(global, L"game", game);

	JsValueRef addEventListenerFunction;
	JsCreateFunction(&addEventListener, taskQueue, &addEventListenerFunction);
	Js::AddPropertyToObject(game, L"addEventListener", addEventListenerFunction);
	Js::AddPropertyToObject(global, L"addEventListener", addEventListenerFunction);
}