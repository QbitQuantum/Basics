void DLLCALL js_PrepareToExecute(JSContext *cx, JSObject *obj, const char *filename, const char* startup_dir)
{
	JSString*	str;
	jsval		val;

	if(JS_GetProperty(cx, obj, "js", &val) && JSVAL_IS_OBJECT(val)) {
		JSObject* js = JSVAL_TO_OBJECT(val);
		char	dir[MAX_PATH+1];

		if(filename!=NULL) {
			char* p;

			if((str=JS_NewStringCopyZ(cx, filename)) != NULL)
				JS_DefineProperty(cx, js, "exec_path", STRING_TO_JSVAL(str)
					,NULL,NULL,JSPROP_ENUMERATE|JSPROP_READONLY);
			if((str=JS_NewStringCopyZ(cx, getfname(filename))) != NULL)
				JS_DefineProperty(cx, js, "exec_file", STRING_TO_JSVAL(str)
					,NULL,NULL,JSPROP_ENUMERATE|JSPROP_READONLY);
			SAFECOPY(dir,filename);
			p=getfname(dir);
			*p=0;
			if((str=JS_NewStringCopyZ(cx, dir)) != NULL)
				JS_DefineProperty(cx, js, "exec_dir", STRING_TO_JSVAL(str)
					,NULL,NULL,JSPROP_ENUMERATE|JSPROP_READONLY);
		}
		if(startup_dir==NULL)
			startup_dir="";
		if((str=JS_NewStringCopyZ(cx, startup_dir)) != NULL)
			JS_DefineProperty(cx, js, "startup_dir", STRING_TO_JSVAL(str)
				,NULL,NULL,JSPROP_ENUMERATE|JSPROP_READONLY);
	}
#if defined(_MSC_VER)
	_set_invalid_parameter_handler(msvc_invalid_parameter_handler);
#endif
}