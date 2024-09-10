//------------------------------------------------------------------------------
//local function part !!!
//------------------------------------------------------------------------------
void GetSIDFromUser(char *user, char* rid, char *sid, unsigned int max_size)
{
  BYTE BSid[MAX_PATH];
  PSID psid       = (PSID)BSid;
  DWORD sid_size  = MAX_PATH;
  SID_NAME_USE TypeSid;

  char domain[MAX_PATH];
  DWORD domain_size = MAX_PATH;

  if(LookupAccountName(NULL,(LPCTSTR)user,psid,(LPDWORD)&sid_size,(LPTSTR)domain,(LPDWORD)&domain_size,(PSID_NAME_USE)&TypeSid))
  {
    if (IsValidSid(psid))SidtoUser(psid, user, rid, sid, max_size);
  }
}