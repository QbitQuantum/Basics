static BOOL open_service_control(SC_HANDLE *scm, SC_HANDLE *service){
  if((*scm = OpenSCManager(NULL, 
			  NULL,  
			  SC_MANAGER_ALL_ACCESS))
     == NULL)
    return FALSE;
  *service = OpenServiceW(*scm,
			  real_service_name,
			  SERVICE_ALL_ACCESS);
  if(service == NULL){
    CloseServiceHandle(*scm);
    return FALSE;
  }
  return TRUE;
}