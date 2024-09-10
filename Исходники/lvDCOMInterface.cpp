static void initCOM(void*)
{
	CoInitializeEx(NULL, COINIT_MULTITHREADED);
	_set_com_error_handler(my_com_raise_error);    // replace default _com_raise_error
}