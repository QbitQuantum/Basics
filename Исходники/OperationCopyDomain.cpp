bool OperationCopyDomain::ProcessAclAction(WCHAR * const sSdPart, ObjectEntry & tObjectEntry, PACL & tCurrentAcl, bool & bAclReplacement)
{
	// check on canonicalization status so if can error if the acl needs to be updated
	const bool bAclIsCanonical = OperationCheckCanonical::IsAclCanonical(tCurrentAcl);

	// check explicit effective rights from sid (no groups)
	bool bAclIsDirty = false;
	if (tCurrentAcl != NULL)
	{
		ACCESS_ACE * tAceDacl = FirstAce(tCurrentAcl);
		for (LONG iEntry = 0; iEntry < tCurrentAcl->AceCount; tAceDacl = 
			(iEntry == -1) ? FirstAce(tCurrentAcl) : NextAce(tAceDacl), iEntry++)
		{
			// do not bother with inherited aces
			if (IsInherited(tAceDacl)) continue;
			
			// see if this sid in the source domain
			BOOL bDomainSidsEqual = FALSE;
			if (EqualDomainSid(&tAceDacl->Sid, tSourceDomain, &bDomainSidsEqual) == 0 ||
				bDomainSidsEqual == FALSE)
			{
				// no match - cease processing this instruction
				continue;
			}

			const PISID tSidStruct = (PISID) &tAceDacl->Sid;
			const PISID tSidTargetDomain = (PISID)tTargetDomain;
			PSID tTargetAccountSid = NULL;
			std::wstring sInfoToReport = L"";
			if (tSidStruct->SubAuthorityCount == 5 &&
				tSidStruct->SubAuthority[0] == 21 &&
				tSidStruct->SubAuthority[4] < 1000)
			{
				// create a new sid that has the domain identifier of the target domain
				PSID tSidTmp = NULL;
				AllocateAndInitializeSid(&tSidStruct->IdentifierAuthority, tSidStruct->SubAuthorityCount,
					tSidStruct->SubAuthority[0], tSidTargetDomain->SubAuthority[1], tSidTargetDomain->SubAuthority[2],
					tSidTargetDomain->SubAuthority[3], tSidStruct->SubAuthority[4], 0, 0, 0, &tSidTmp);

				// lookup the target name and see if it exists
				std::wstring sTargetAccountName = GetNameFromSid(tSidTmp);
				FreeSid(tSidTmp);
				if (sTargetAccountName.empty())	continue;

				// do a forward lookup on the name in order to get a reference to the 
				// SID that we do not have to worry about cleaning up
				tTargetAccountSid = GetSidFromName(sTargetAccountName);

				// lookup the source name for reporting
				std::wstring sSourceAccountName = GetNameFromSidEx(&tAceDacl->Sid);

				// record the status to report
				sInfoToReport = L"Copying Well Known '" + sSourceAccountName + L"' to '" + sTargetAccountName + L"'";
			}
			else
			{
				// translate the old sid to an account name
				std::wstring sSourceAccountName = GetNameFromSid(&tAceDacl->Sid, NULL);
				if (sSourceAccountName.empty())	continue;

				// check to see if an equivalent account exists in the target domain
				std::wstring sTargetAccountName = sTargetDomain + (wcsstr(sSourceAccountName.c_str(), L"\\") + 1);
				tTargetAccountSid = GetSidFromName(sTargetAccountName);

				// continue if no match was found
				if (tTargetAccountSid == nullptr)
				{
					InputOutput::AddWarning(L"Could not find matching account in target domain '" + 
						sTargetDomain + L"' for '" + sSourceAccountName + L"'", sSdPart);
					continue;
				}

				// do a reverse lookup to see if this might be a sid history item
				if (GetNameFromSidEx(tTargetAccountSid) == sSourceAccountName) continue;

				// stop processing if the account does not exist
				if (tTargetAccountSid == nullptr) continue;

				// record the status to report
				sInfoToReport = L"Copying '" + sSourceAccountName + L"' to '" + sTargetAccountName + L"'";
			}

			// determine access mode
			ACCESS_MODE tMode = NOT_USED_ACCESS;
			if (tAceDacl->Header.AceType == ACCESS_ALLOWED_ACE_TYPE)
			{
				tMode = GRANT_ACCESS;
			}
			else if (tAceDacl->Header.AceType == ACCESS_DENIED_ACE_TYPE)
			{
				tMode = DENY_ACCESS;
			}
			else if (tAceDacl->Header.AceType == SYSTEM_AUDIT_ACE_TYPE)
			{
				if (CheckBitSet(tAceDacl->Header.AceFlags, SUCCESSFUL_ACCESS_ACE_FLAG))
				{
					tMode = (ACCESS_MODE) (tMode | SET_AUDIT_SUCCESS);
				}
				if (CheckBitSet(tAceDacl->Header.AceFlags, FAILED_ACCESS_ACE_FLAG))
				{
					tMode = (ACCESS_MODE) (tMode | SET_AUDIT_FAILURE);
				}
			}
			else
			{
				// unknown type; skipping
				continue;
			}

			// since SetEntriesInAcl reacts poorly / unexpectedly in cases where the
			// acl is not canonical, just error out and continue on
			if (!bAclIsCanonical)
			{
				std::wstring sTargetAccountName = GetNameFromSid(tTargetAccountSid);
				InputOutput::AddError(L"Could not add '" + sTargetAccountName + L"' for domain '"
					+ sTargetDomain + L"' to access control list since ACL was not canonical.", sSdPart);
				continue;
			}

			// create a structure to add the missing permissions
			EXPLICIT_ACCESS tEa;
			tEa.grfAccessPermissions = tAceDacl->Mask;
			tEa.grfAccessMode = tMode;
			tEa.grfInheritance = VALID_INHERIT_FLAGS & tAceDacl->Header.AceFlags;
			tEa.Trustee.MultipleTrusteeOperation = NO_MULTIPLE_TRUSTEE;
			tEa.Trustee.pMultipleTrustee = NULL;
			tEa.Trustee.ptstrName = (LPWSTR) tTargetAccountSid;
			tEa.Trustee.TrusteeForm = TRUSTEE_IS_SID;
			tEa.Trustee.TrusteeType = TRUSTEE_IS_UNKNOWN;

			// special case since SetEntriesInAcl does not handle setting both success
			// and failure types together
			PACL tNewDacl = NULL;
			DWORD iError = 0;
			if (CheckBitSet(tEa.grfAccessMode, SET_AUDIT_SUCCESS) &&
				CheckBitSet(tEa.grfAccessMode, SET_AUDIT_FAILURE))
			{
				PACL tNewDaclTmp = NULL;
				tEa.grfAccessMode = SET_AUDIT_SUCCESS;
				iError = SetEntriesInAcl(1, &tEa, tCurrentAcl, &tNewDaclTmp);
				tEa.grfAccessMode = SET_AUDIT_FAILURE;
				if (iError == ERROR_SUCCESS) {
					SetEntriesInAcl(1, &tEa, tNewDaclTmp, &tNewDacl);
					LocalFree(tNewDaclTmp);
				}
			}
			else
			{
				// merge the new trustee into the dacl
				iError = SetEntriesInAcl(1, &tEa, tCurrentAcl, &tNewDacl);
			}

			// verify the new acl could be generated
			if (iError != ERROR_SUCCESS || tNewDacl == NULL)
			{
				std::wstring sTargetAccountName = GetNameFromSid(tTargetAccountSid);
				InputOutput::AddError(L"Could not add '" + sTargetAccountName + L"' for domain '" 
					+ sTargetDomain + L"' to access control list (" + std::to_wstring(iError) + L").", sSdPart);
				continue;
			}

			// see if the old and new acl match
			if (tCurrentAcl->AclSize == tNewDacl->AclSize &&
				memcmp(tCurrentAcl, tNewDacl, tCurrentAcl->AclSize) == 0)
			{
				// if acls match then no change was made and we do not need
				// to mark this as dirty or restart the enumeration 
				LocalFree(tNewDacl);
			}
			else
			{
				// report status
				InputOutput::AddInfo(sInfoToReport, sSdPart);

				// cleanup the old dacl (if necessary) and assign our new active dacl
				if (bAclReplacement) LocalFree(tCurrentAcl);
				tCurrentAcl = tNewDacl;
				bAclReplacement = true;
				bAclIsDirty = true;
				iEntry = -1;
			}
		}
	}

	return bAclIsDirty;
}