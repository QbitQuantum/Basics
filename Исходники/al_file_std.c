bool AL_CALLTYPE alFileStd_wfsopen(alFileStd* _this,
                                  const wchar_t *filename,
                                  const wchar_t *mode,
								  int shflag 
								  )
{
	alFileStdi* _data = (alFileStdi*)_this;
	if (_data->handle != NULL)
		alFileStd_Close(_this);
	_data->handle = _wfsopen(filename, mode, shflag);
	if (_data->handle == NULL)
		return false;
	return true;
}