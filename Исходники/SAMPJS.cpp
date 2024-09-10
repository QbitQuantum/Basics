void SAMPJS::JS_Load(const FunctionCallbackInfo<Value> & args){
	if (args.Length() < 1)return;
	string file = JS2STRING(args[0]);
	CreateScript(file);
	auto script = GetScript(file);
	if (script != nullptr){
		script->Server()->FireEvent("ScriptInit");
	}
}