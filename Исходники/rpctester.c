/* Return token for test user with required privileges to execute
 * programs as that user. Note that for this to work, some system
 * configuration is required:
 *   - you must have a local user account with name "test" and
 *     password "test"
 *   - you must run "secpol.msc", and in the Local Policies >
 *     User Rights Assignment section, give your test user the right to
 *     "Replace a process level token"
 */
void get_test_user_token (HANDLE *p_token) {
	BOOL  success;
	DWORD result;

	success = LogonUser ("test",
	                     ".",
	                     "test",
	                     LOGON32_LOGON_INTERACTIVE,
	                     LOGON32_PROVIDER_DEFAULT,
	                     p_token);

	if (! success) {
		result = GetLastError ();

		if (result == ERROR_LOGON_FAILURE) {
			rpc_log_error (test_user_logon_failure_error_message);
		} else {
			printf ("tester: Unable to log on second user: "******"SeIncreaseQuotaPrivilege",
	                                &se_increase_quota_privilege);

	if (! success)
		rpc_log_error_from_status (GetLastError ());

	success = LookupPrivilegeValue (NULL,
	                                "SeTakeOwnershipPrivilege",
	                                &se_take_ownership_privilege);

	if (! success)
		rpc_log_error_from_status (GetLastError ());

	success = LookupPrivilegeValue (NULL,
	                                "SeAssignPrimaryTokenPrivilege",
	                                &se_assign_primary_token_privilege);

	if (! success)
		rpc_log_error_from_status (GetLastError ());

	new_privileges->PrivilegeCount = 3;
	new_privileges->Privileges[0].Luid = se_increase_quota_privilege;
	new_privileges->Privileges[0].Attributes = SE_PRIVILEGE_ENABLED;
	new_privileges->Privileges[1].Luid = se_take_ownership_privilege;
	new_privileges->Privileges[1].Attributes = SE_PRIVILEGE_ENABLED;
	new_privileges->Privileges[2].Luid = se_assign_primary_token_privilege;
	new_privileges->Privileges[2].Attributes = SE_PRIVILEGE_ENABLED;

	/* If SeAssignPrimaryToken isn't present in the token (which it
	 * won't be if it's not been enabled in secpol.msc) this function
	 * will succeed anyway and just not enable the privilege. Then
	 * CreateProcessAsUser() will fail because "A required privilege is
	 * not held by the client."
	 */
	success = AdjustTokenPrivileges (*p_token,
	                                 FALSE,
	                                 new_privileges,
	                                 length,
	                                 NULL,
	                                 NULL);

	if (! success)
		rpc_log_error_from_status (GetLastError ());

	free (new_privileges);
}