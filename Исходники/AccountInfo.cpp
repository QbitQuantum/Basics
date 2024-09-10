NTSTATUS
AddPrivilegeToAcccount(LPTSTR name, LPWSTR PrivilegeName) {
	LSA_HANDLE PolicyHandle;
	TCHAR AccountName[256];		/* static account name buffer */
	PSID pSid;
	NTSTATUS Status;
	unsigned long err;

	/*
	 * Open the policy on the target machine.
	 */
	if ((Status = OpenPolicy(NULL, POLICY_ALL_ACCESS, &PolicyHandle))
		!= STATUS_SUCCESS)
		return (RTN_ERROR);

	/*
	 * Let's see if the account exists. Return if not
	 */
	wsprintf(AccountName, TEXT("%hS"), name);
	if (!GetAccountSid(NULL, AccountName, &pSid))
		return (RTN_NOACCOUNT);

	err = LsaNtStatusToWinError(SetPrivilegeOnAccount(PolicyHandle,
		pSid, PrivilegeName, TRUE));

	LsaClose(PolicyHandle);
	if (err == ERROR_SUCCESS)
		return (RTN_OK);
	else
		return (err);
}