/*************************************************************************
 * SHRestricted				 [SHELL32.100]
 *
 * Get the value associated with a policy Id.
 *
 * PARAMS
 *     pol [I] Policy Id
 *
 * RETURNS
 *     The queried value for the policy.
 *
 * NOTES
 *     Exported by ordinal.
 *     This function caches the retrieved values to prevent unnecessary registry access,
 *     if SHInitRestricted() was previously called.
 *
 * REFERENCES
 *     a: MS System Policy Editor.
 *     b: 98Lite 2.0 (which uses many of these policy keys) http://www.98lite.net/
 *     c: 'The Windows 95 Registry', by John Woram, 1996 MIS: Press
 */
DWORD WINAPI SHRestricted (RESTRICTIONS policy)
{
	char regstr[256];
	HKEY    xhkey;
	DWORD   retval, datsize = 4;
	LPPOLICYDATA p;

	TRACE("(%08x)\n", policy);

	/* scan to see if we know this policy ID */
	for (p = sh32_policy_table; p->policy; p++)
	{
	  if (policy == p->policy)
	  {
	    break;
	  }
	}

	if (p->policy == 0)
	{
	    /* we don't know this policy, return 0 */
	    TRACE("unknown policy: (%08x)\n", policy);
		return 0;
	}

	/* we have a known policy */

	/* first check if this policy has been cached, return it if so */
	if (p->cache != SHELL_NO_POLICY)
	{
	    return p->cache;
	}

	lstrcpyA(regstr, strRegistryPolicyA);
	lstrcatA(regstr, p->appstr);

	/* return 0 and don't set the cache if any registry errors occur */
	retval = 0;
	if (RegOpenKeyA(HKEY_CURRENT_USER, regstr, &xhkey) == ERROR_SUCCESS)
	{
	  if (RegQueryValueExA(xhkey, p->keystr, NULL, NULL, (LPBYTE)&retval, &datsize) == ERROR_SUCCESS)
	  {
	    p->cache = retval;
	  }
	  RegCloseKey(xhkey);
	}
	return retval;
}