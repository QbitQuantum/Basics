BOOL CNTScmService::SetObjectSecurity(SECURITY_INFORMATION dwSecurityInformation,
                                      PSECURITY_DESCRIPTOR lpSecurityDescriptor) const

{
  //Validate our parameters
  ATLASSUME(m_hService != NULL);
  
  return SetServiceObjectSecurity(m_hService, dwSecurityInformation, lpSecurityDescriptor);
}