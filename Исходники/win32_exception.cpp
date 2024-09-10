void win32_exception::install_handler() 
{
//#ifndef _DEBUG
	_set_se_translator(win32_exception::Handler);
	installed_for_thread() = true;
//#endif
}