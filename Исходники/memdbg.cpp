//------------------------------------------------------------------------------------------------------
// Function:	TFStats_setNewHandler
// Purpose:	 sets the new handler to the TFStats new handler
//------------------------------------------------------------------------------------------------------
void TFStats_setNewHandler()
{
#ifdef WIN32
	_set_new_handler(TFStats_win32_new_handler);
	_set_new_mode(1);
#else
	std::set_new_handler(TFStats_linux_new_handler);
	//std::set_new_mode(1);
#endif
}