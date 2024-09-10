/*
 * Tcl proc to embed Javascript
 */
int jsEval(
	ClientData clientData,
	Tcl_Interp *interp,
	int objc,
	Tcl_Obj *const objv[]
){
	v8log("TclBinding::jsEval (interp=%p)\n", interp);

	// Get handle to the V8 Isolate for this Tcl interpreter
	Isolate* isolate  = v8::Isolate::GetCurrent();
	assert(isolate != nullptr);

	// lock the Isolate for multi-threaded access (not reentrant on its own)
	Locker locker(isolate);

	// create a bindings map and store it in the current V8 Isolate
	TclVariableBindingsMap* varbindings = new TclVariableBindingsMap;
	isolate->SetData(0, varbindings);
	v8log("jsEval: created new bindings map at %lp\n", (void*)varbindings );

	// validate input params
	if ( (objc != 3) ) {
		std::string msg("usage: jsEval [list of tcl vars to add to v8 context] { javascript }");
		Tcl_SetObjResult(interp, Tcl_NewStringObj(msg.c_str(), msg.length()));
		return TCL_ERROR;
	}

	// get the argument list
	Tcl_Obj* arglist = objv[1];
	if ( (arglist->typePtr == NULL) || strcmp(arglist->typePtr->name, "list") ) {
		std::string msg("jsEval: 1st arg not a list");
		Tcl_SetObjResult(interp, Tcl_NewStringObj(msg.c_str(), msg.length()));
		return TCL_ERROR;
	}

	// get the JS snippet
	char* javascript = Tcl_GetString(objv[2]);
	if ( strlen(javascript) == 0 ) {
		std::string msg("jsEval: 2nd arg not a string");
		Tcl_SetObjResult(interp, Tcl_NewStringObj(msg.c_str(), msg.length()));
		return TCL_ERROR;
	}

	// Create stack-allocated isolate and handle scopes.
	Isolate::Scope isolate_scope(isolate);
	HandleScope    handle_scope(isolate);

	// new v8 global template
	Handle<ObjectTemplate> global_templ = ObjectTemplate::New(isolate);

	// scrum our F18 Interceptors
	global_templ->SetNamedPropertyHandler(
			&TclVariableBinding::GenericNamedPropertyReader,
			&TclVariableBinding::GenericNamedPropertyWriter
	);

	// Create and Enter a new context for compiling and running the script.
	Handle<Context> context = Context::New(isolate, NULL, global_templ);
	context->Enter();

	int arglistLength;
	Tcl_ListObjLength(interp, arglist, &arglistLength);
	v8log("arg list length == %d\n", arglistLength);

	for ( int i = 0; i < arglistLength; i++ ) {
		// get the variable NAME
		Tcl_Obj* varName;
		Tcl_ListObjIndex(interp, arglist, i, &varName);
		char* vn = Tcl_GetString(varName);
		v8log("binding %s (idx: %d) to V8\n", vn, i);
		// then create a binding  and store it
		(*varbindings)[vn] = new TclVariableBinding(interp, varName);
	}

	// Compile
	v8log("compiling jsEval'ed script\n");
	v8::MaybeLocal<v8::Script> jsSource = v8::Script::Compile(context, Nan::New<String>(javascript).ToLocalChecked());
	if (jsSource.IsEmpty()) {
		v8log("*** jsSource.IsEmpty()\n");
	} else {
		// Run
		v8log("running jsEval'ed script\n");
		Nan::TryCatch tc;
		Nan::MaybeLocal<v8::Value> retv = jsSource.ToLocalChecked()->Run();
		v8log("done running jsEval'ed script\n");
		if ( tc.HasCaught() ) {
			// oops, exception raised from V8 while in JS land
			Local<Message> msg = tc.Message();
			std::string msgtext(*String::Utf8Value(msg->Get()));
			v8log("*** caught JS exception: %s\n", msgtext.c_str());
		}

		TclVariableBindingsMap::const_iterator it;
		for (it = varbindings->begin(); it != varbindings->end(); it++) {
			TclVariableBinding* vb = it->second;
			v8log("reverse mapping of %s (v8: %p) to Tcl...\n", it->first.c_str(), vb->m_v8val);
			Tcl_SetVar2Ex(vb->m_interp, it->first.c_str(), NULL, vb->m_tclvar, 0);
			delete vb;
		}
		varbindings->clear();
		// handle return value, if there is one
		if (!retv.IsEmpty()) {
			Local<Value> rv = retv.ToLocalChecked();
			std::string res(*String::Utf8Value(rv));
			std::string restype(V8ValueType(rv));
			v8log("Tcl_SetObjResult(interp == %lp, result == %s (%s)\n", (void*) interp, res.c_str(), restype.c_str());
			Tcl_Obj* tclres = V8ToTcl(interp, rv);
			Tcl_SetObjResult(interp, tclres);
		}
		delete varbindings;
	}
	context->Exit();

// TODO: error handling!
	return TCL_OK;
}