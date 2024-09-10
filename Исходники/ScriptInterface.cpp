ScriptInterface_impl::ScriptInterface_impl(const char* nativeScopeName, const shared_ptr<ScriptRuntime>& runtime) :
	m_runtime(runtime), m_glob(runtime->m_rt), m_nativeScope(runtime->m_rt)
{
	bool ok;

	m_cx = JS_NewContext(m_runtime->m_rt, STACK_CHUNK_SIZE);
	ENSURE(m_cx);

	JS_SetOffthreadIonCompilationEnabled(m_runtime->m_rt, true);

	// For GC debugging:
	// JS_SetGCZeal(m_cx, 2, JS_DEFAULT_ZEAL_FREQ);

	JS_SetContextPrivate(m_cx, NULL);

	JS_SetErrorReporter(m_runtime->m_rt, ErrorReporter);

	JS_SetGlobalJitCompilerOption(m_runtime->m_rt, JSJITCOMPILER_ION_ENABLE, 1);
	JS_SetGlobalJitCompilerOption(m_runtime->m_rt, JSJITCOMPILER_BASELINE_ENABLE, 1);

	JS::RuntimeOptionsRef(m_cx).setExtraWarnings(1)
		.setWerror(0)
		.setVarObjFix(1)
		.setStrictMode(1);

	JS::CompartmentOptions opt;
	opt.setVersion(JSVERSION_LATEST);
	// Keep JIT code during non-shrinking GCs. This brings a quite big performance improvement.
	opt.setPreserveJitCode(true);

	JSAutoRequest rq(m_cx);
	JS::RootedObject globalRootedVal(m_cx, JS_NewGlobalObject(m_cx, &global_class, NULL, JS::OnNewGlobalHookOption::FireOnNewGlobalHook, opt));
	m_comp = JS_EnterCompartment(m_cx, globalRootedVal);
	ok = JS_InitStandardClasses(m_cx, globalRootedVal);
	ENSURE(ok);
	m_glob = globalRootedVal.get();

	JS_DefineProperty(m_cx, m_glob, "global", globalRootedVal, JSPROP_ENUMERATE | JSPROP_READONLY | JSPROP_PERMANENT);

	m_nativeScope = JS_DefineObject(m_cx, m_glob, nativeScopeName, nullptr, JSPROP_ENUMERATE | JSPROP_READONLY | JSPROP_PERMANENT);

	JS_DefineFunction(m_cx, globalRootedVal, "print", ::print,        0, JSPROP_ENUMERATE | JSPROP_READONLY | JSPROP_PERMANENT);
	JS_DefineFunction(m_cx, globalRootedVal, "log",   ::logmsg,       1, JSPROP_ENUMERATE | JSPROP_READONLY | JSPROP_PERMANENT);
	JS_DefineFunction(m_cx, globalRootedVal, "warn",  ::warn,         1, JSPROP_ENUMERATE | JSPROP_READONLY | JSPROP_PERMANENT);
	JS_DefineFunction(m_cx, globalRootedVal, "error", ::error,        1, JSPROP_ENUMERATE | JSPROP_READONLY | JSPROP_PERMANENT);
	JS_DefineFunction(m_cx, globalRootedVal, "deepcopy", ::deepcopy,  1, JSPROP_ENUMERATE | JSPROP_READONLY | JSPROP_PERMANENT);

	Register("ProfileStart", ::ProfileStart, 1);
	Register("ProfileStop", ::ProfileStop, 0);
	Register("ProfileAttribute", ::ProfileAttribute, 1);

	runtime->RegisterContext(m_cx);
}