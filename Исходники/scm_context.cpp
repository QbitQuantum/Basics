/**
* @brief	
* @param	
* @see		
* @remarks	
* @code		
* @endcode	
* @return	
*/
bool 
scm_context::install_service(
	_In_ bool auto_start
	)
{
	SC_HANDLE scm_handle = OpenSCManagerW(NULL, 
										  NULL, 
										  SC_MANAGER_ALL_ACCESS);
	if (NULL == scm_handle)
	{
		log_err "OpenSCManagerW() faield. gle = %u", GetLastError() log_end
		return false;
	}