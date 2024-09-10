NamedMutexImpl::NamedMutexImpl(const std::string& name):
	_name(name)
{
	UnicodeConverter::toUTF16(_name, _uname);
	_mutex = CreateMutexW(NULL, FALSE, _uname.c_str());
	if (!_mutex) 
		throw SystemException("cannot create named mutex", _name);
}