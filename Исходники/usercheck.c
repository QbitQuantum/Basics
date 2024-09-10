gboolean
Usercheck_IsAdminMember(const gchar *userName)
{
   NET_API_STATUS status;
   gunichar2 *userNameW = NULL;
   LOCALGROUP_MEMBERS_INFO_1 *groupList;
   DWORD entriesRead;
   DWORD totalEntries;
   DWORD i;
   gboolean bRetVal = FALSE;
   BOOL ok;
   DWORD lastError;
   WCHAR *accountW = NULL;
   WCHAR *domainW = NULL;
   DWORD accountChar2Needed = 0;
   DWORD domainChar2Needed = 0;
   SID_NAME_USE eUse;
   PSID pSid = NULL;

   /*
    * XXX Should this cache some (all?) of the returned data for a perf boost?
    * Or does that open up bugs (security or other) where it might
    * change while the service is running?  The name of the group changing
    * seems unlikely; member changing less so.
    */

   /*
    * To avoid localization issues, start with the Administrators group's SID,
    * and find the name to pass to NetLocalGroupGetMembers to get
    * the group members.
    */
   pSid = WinUtil_GroupAdminSid();

   ok = LookupAccountSidW(NULL, pSid, NULL, &accountChar2Needed,
                          NULL, &domainChar2Needed, &eUse);
   ASSERT(!ok);
   lastError = GetLastError();
   if (lastError != ERROR_INSUFFICIENT_BUFFER) {
      VGAUTH_LOG_ERR_WIN_CODE(lastError, "LookupAccountSidW() failed");
      goto done;
   }

   ASSERT(accountChar2Needed > 0);
   ASSERT(domainChar2Needed > 0);

   accountW = (WCHAR *) g_malloc0(accountChar2Needed * sizeof(WCHAR));
   domainW = (WCHAR *) g_malloc0(domainChar2Needed * sizeof(WCHAR));

   ok = LookupAccountSidW(NULL, pSid, accountW, &accountChar2Needed,
                          domainW, &domainChar2Needed, &eUse);
   if (!ok) {
      VGAUTH_LOG_ERR_WIN("LookupAccountSidW failed");
      goto done;
   }

   /*
    * Since the query is being done on the local server, the domain
    * return value shouldn't matter (and should be 'BUILTIN').
    */

   // get everything in one shot
   status = NetLocalGroupGetMembers(NULL,       // server name
                                    accountW,    // group name
                                    1,          // level
                                    (LPBYTE *) &groupList, // return buffer
                                    MAX_PREFERRED_LENGTH,   // get it all
                                    &entriesRead,
                                    &totalEntries,
                                    NULL);         // resume handle

   if (status != NERR_Success) {
      VGAUTH_LOG_ERR_WIN_CODE(status, "NetLocalGroupGetMembers() failed");
      goto done;
   }

   CHK_UTF8_TO_UTF16(userNameW, userName, goto done);
   for (i = 0; i < entriesRead; i++) {
#ifdef VMX86_DEBUG
      g_debug("%s: checking input %S against group member #%d %S\n",
              __FUNCTION__, userNameW, i, groupList[i].lgrmi1_name);
#endif
      if (_wcsicmp(userNameW, groupList[i].lgrmi1_name) == 0) {
         bRetVal = TRUE;
         goto done;
      }
   }

done:
   g_free(pSid);
   if (groupList) {
      NetApiBufferFree(groupList);
   }
   g_free(userNameW);
   g_free(accountW);
   g_free(domainW);

   return bRetVal;
}