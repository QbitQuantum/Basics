/* static */ SQInteger AIInfo::Constructor(HSQUIRRELVM vm)
{
	/* Get the AIInfo */
	SQUserPointer instance = NULL;
	if (SQ_FAILED(sq_getinstanceup(vm, 2, &instance, 0)) || instance == NULL) return sq_throwerror(vm, _SC("Pass an instance of a child class of AIInfo to RegisterAI"));
	AIInfo *info = (AIInfo *)instance;

	SQInteger res = AIFileInfo::Constructor(vm, info);
	if (res != 0) return res;

	AIConfigItem config = _start_date_config;
	config.name = strdup(config.name);
	config.description = strdup(config.description);
	info->config_list.push_back(config);

	/* Check if we have settings */
	if (info->engine->MethodExists(*info->SQ_instance, "GetSettings")) {
		if (!info->GetSettings()) return SQ_ERROR;
	}
	if (info->engine->MethodExists(*info->SQ_instance, "MinVersionToLoad")) {
		if (!info->engine->CallIntegerMethod(*info->SQ_instance, "MinVersionToLoad", &info->min_loadable_version, MAX_GET_SETTING_OPS)) return SQ_ERROR;
	} else {
		info->min_loadable_version = info->GetVersion();
	}
	/* When there is an UseAsRandomAI function, call it. */
	if (info->engine->MethodExists(*info->SQ_instance, "UseAsRandomAI")) {
		if (!info->engine->CallBoolMethod(*info->SQ_instance, "UseAsRandomAI", &info->use_as_random, MAX_GET_SETTING_OPS)) return SQ_ERROR;
	} else {
		info->use_as_random = true;
	}
	/* Try to get the API version the AI is written for. */
	if (info->engine->MethodExists(*info->SQ_instance, "GetAPIVersion")) {
		if (!info->engine->CallStringMethodStrdup(*info->SQ_instance, "GetAPIVersion", &info->api_version, MAX_GET_SETTING_OPS)) return SQ_ERROR;
		if (!CheckAPIVersion(info->api_version)) {
			DEBUG(ai, 1, "Loading info.nut from (%s.%d): GetAPIVersion returned invalid version", info->GetName(), info->GetVersion());
			return SQ_ERROR;
		}
	} else {
		info->api_version = strdup("0.7");
	}

	/* Remove the link to the real instance, else it might get deleted by RegisterAI() */
	sq_setinstanceup(vm, 2, NULL);
	/* Register the AI to the base system */
	info->base->RegisterAI(info);
	return 0;
}