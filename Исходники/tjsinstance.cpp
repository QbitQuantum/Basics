/**
 * TJSオブジェクトのオーバライド処理
 * @param args 引数
 * @return 結果
 */
void
TJSInstance::tjsOverride(const FunctionCallbackInfo<Value>& args)
{
	Isolate *isolate = args.GetIsolate();
	HandleScope handle_scope(isolate);
	tTJSVariant instance;
	if (getVariant(isolate, instance, args.This())) {
		if (args.Length() > 0) {
			Local<Value> func = args.Length() > 1 ? args[1] : args.This()->Get(args[0]);
			if (func->IsFunction()) {
				tTJSVariant value = toVariant(isolate, func->ToObject(), args.This());
				String::Value methodName(args[0]);
				tjs_error error;
				if (TJS_FAILED(error = instance.AsObjectClosureNoAddRef().PropSet(TJS_MEMBERENSURE, *methodName, NULL, &value, NULL))) {
					args.GetReturnValue().Set(ERROR_KRKR(isolate, error));
					return;
				}
				args.GetReturnValue().Set(Undefined(isolate));
				return;
			}
		}
		args.GetReturnValue().Set(isolate->ThrowException(String::NewFromUtf8(isolate, "not function")));
		return;
	}
	args.GetReturnValue().Set(ERROR_BADINSTANCE(isolate));
}