/* static */ SQInteger GameInfo::Constructor(HSQUIRRELVM vm)
{
	/* Get the GameInfo */
	SQUserPointer instance = NULL;
	if (SQ_FAILED(sq_getinstanceup(vm, 2, &instance, 0)) || instance == NULL) return sq_throwerror(vm, _SC("Pass an instance of a child class of GameInfo to RegisterGame"));
	GameInfo *info = (GameInfo *)instance;

	SQInteger res = ScriptInfo::Constructor(vm, info);
	if (res != 0) return res;

	if (info->engine->MethodExists(*info->SQ_instance, "MinVersionToLoad")) {
		if (!info->engine->CallIntegerMethod(*info->SQ_instance, "MinVersionToLoad", &info->min_loadable_version, MAX_GET_OPS)) return SQ_ERROR;
	} else {
		info->min_loadable_version = info->GetVersion();
	}
	/* When there is an IsSelectable function, call it. */
	if (info->engine->MethodExists(*info->SQ_instance, "IsDeveloperOnly")) {
		if (!info->engine->CallBoolMethod(*info->SQ_instance, "IsDeveloperOnly", &info->is_developer_only, MAX_GET_OPS)) return SQ_ERROR;
	} else {
		info->is_developer_only = false;
	}
	/* Try to get the API version the AI is written for. */
	if (!info->CheckMethod("GetAPIVersion")) return SQ_ERROR;
	if (!info->engine->CallStringMethodStrdup(*info->SQ_instance, "GetAPIVersion", &info->api_version, MAX_GET_OPS)) return SQ_ERROR;
	if (!CheckAPIVersion(info->api_version)) {
		DEBUG(script, 1, "Loading info.nut from (%s.%d): GetAPIVersion returned invalid version", info->GetName(), info->GetVersion());
		return SQ_ERROR;
	}

	/* Remove the link to the real instance, else it might get deleted by RegisterGame() */
	sq_setinstanceup(vm, 2, NULL);
	/* Register the Game to the base system */
	info->GetScanner()->RegisterScript(info);
	return 0;
}