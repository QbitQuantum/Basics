void SetExt(char * str, char * new_ext)
{
	_splitpath(str, _drv, _dir, _name, _ext);
	_makepath(str, _drv, _dir, _name, new_ext);
}