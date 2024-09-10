int LoadEffekseerEffect(const wchar_t* fileName, float magnification)
{
	if (g_manager2d == nullptr) return -1;

	if (effectFileNameToEffectHandle.count(fileName) > 0)
	{
		return effectFileNameToEffectHandle[fileName];
	}

	auto effect = Effekseer::Effect::Create(g_manager2d, (const EFK_CHAR*) fileName, magnification);
	if (effect == nullptr) return -1;

	int32_t handle = nextEffectHandle;
	nextEffectHandle++;

	effectFileNameToEffectHandle[fileName] = handle;
	effectHandleToEffectFileName[handle] = fileName;
	effectHandleToEffect[handle] = effect;

	if (g_server != nullptr)
	{
		wchar_t _dir[_MAX_DIR];
		wchar_t _drive[_MAX_DRIVE];
		wchar_t _fileName[_MAX_FNAME];
		wchar_t _ext[_MAX_EXT];
		_wsplitpath_s(fileName, _drive, _dir, _fileName, _ext);
		g_server->Register((const EFK_CHAR*) _fileName, effect);
	}

	return handle;
}