int
can_switch_ids( void )
{
#ifdef WIN32
   static bool HasChecked = false;
   // can't switch users if we're not root/SYSTEM
   if ( ! HasChecked) {

      // begin by assuming we can't switch ID's
      SwitchIds = FALSE;

      // if we are running as LocalSystem, then we really Shouldn't 
      // run jobs without switching users first, and we can be certain
      // that this account has all of the needed privs.
      PSID psid = my_user_Sid();
      if (psid) {
         if (EqualSid(psid, const_cast<SID*>(&sids.LocalSystem)))
            SwitchIds = TRUE;
         free(psid);
      }

      // if SwitchIds is FALSE, then we know we aren't the system account, 
      // So if we allow non-system accounts to switch ids
      // set SwitchIds to true if we have the necessary privileges
      //
      if ( ! SwitchIds && ! only_SYSTEM_can_switch_ids) {

         static const LPCTSTR needed[] = {
            SE_INCREASE_QUOTA_NAME, //needed by CreateProcessAsUser
            //SE_TCB_NAME,            //needed on Win2k to CreateProcessAsUser
            SE_PROF_SINGLE_PROCESS_NAME, //needed?? to get CPU% and Memory/Disk useage for our children
            SE_CREATE_GLOBAL_NAME,  //needed to create named shared memory
            SE_CHANGE_NOTIFY_NAME,  //needed by CreateProcessAsUser
            SE_SECURITY_NAME,       //needed to change file ACL's
            SE_TAKE_OWNERSHIP_NAME, //needed to take ownership of files
            //SE_CREATE_TOKEN_NAME,   //needed?
            //SE_ASSIGNPRIMARYTOKEN_NAME //needed?
            //SE_IMPERSONATE_NAME,    //needed?
            };

         struct {
            PRIVILEGE_SET       set;
            LUID_AND_ATTRIBUTES a[COUNTOF(needed)];
            } privs = { 0, PRIVILEGE_SET_ALL_NECESSARY };

         LUID_AND_ATTRIBUTES * pla = &privs.set.Privilege[0];
         for (int ii = 0; ii < COUNTOF(needed); ++ii) {
            LookupPrivilegeValue(NULL, needed[0], &pla->Luid);
            pla->Attributes = SE_PRIVILEGE_ENABLED;
            ++pla;
         }
         privs.set.PrivilegeCount = (pla - &privs.set.Privilege[0]);

         HANDLE hToken = NULL;
         if ( ! OpenProcessToken(GetCurrentProcess(),TOKEN_QUERY,&hToken)) {
            dprintf(D_ALWAYS, "can_switch_ids: OpenProcessToken failed error = %d", GetLastError());
         } else {
            BOOL fEnabled = false;
            if ( ! PrivilegeCheck(hToken, &privs.set, &fEnabled)) {
               dprintf(D_ALWAYS, "can_switch_ids: PrivilegeCheck failed error = %d", GetLastError());
            } else {
               SwitchIds = fEnabled;
            }
            CloseHandle(hToken);
         }
      }

      HasChecked = true;
   }
#else // *NIX
	static bool HasCheckedIfRoot = false;

	// can't switch users if we're not root/SYSTEM
	if (!HasCheckedIfRoot) {
		if (!is_root()) {
			SwitchIds = FALSE;
		}
		HasCheckedIfRoot = true;
	}
#endif

	return SwitchIds;
}