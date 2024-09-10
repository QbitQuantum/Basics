NamedMutexImpl::NamedMutexImpl(const std::string& name):
	_name(name)
{
	_mutex = CreateMutexA(NULL, FALSE, _name.c_str());
	if (!_mutex) 
		throw SystemException("cannot create named mutex", _name);
}