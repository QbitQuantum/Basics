// メソッドの呼び出し
Handle<Value>
TJSObject::caller(const Arguments& args)
{
	tTJSVariant self;
	if (getVariant(self, args.This())) {
		Handle<Value> ret;
		
		// 引数変換
		tjs_int argc = args.Length();
		tTJSVariant **argv = new tTJSVariant*[argc];
		for (tjs_int i=0;i<argc;i++) {
			argv[i] = new tTJSVariant();
			*argv[i] = toVariant(args[i]);
		}

		if (self.AsObjectClosureNoAddRef().IsInstanceOf(0, NULL, NULL, L"Class", NULL) == TJS_S_TRUE) {
			// クラスオブジェクトならコンストラクタ呼び出し
			iTJSDispatch2 *instance = NULL;
			tjs_error error;
			if (TJS_SUCCEEDED(error = self.AsObjectClosureNoAddRef().CreateNew(0, NULL, NULL, &instance, argc, argv, NULL))) {
				ret = toJSValue(tTJSVariant(instance, instance));
				instance->Release();
			} else {
				ret = ERROR_KRKR(error);
			}
		} else {
			// メソッド呼び出し
			tTJSVariant result;
			tjs_error error;
			if (TJS_SUCCEEDED(error = self.AsObjectClosureNoAddRef().FuncCall(0, NULL, NULL, &result, argc, argv, NULL))) {
				ret = toJSValue(result);
			} else {
				ret = ERROR_KRKR(error);
			}
		}

		// 引数解放
		if (argv) {
			for (int i=0;i<argc;i++) {
				delete argv[i];
			}
			delete[] argv;
		}
		
		return ret;
	}
	return ERROR_BADINSTANCE();
}