/*
 * ObjectDaclEntryAdd() -- add an access-control entry to an object's DACL.
 *
 *     Notes: The accessPerm, accessMode, and inheritance args must be correct
 *                for an EXPLICIT_ACCESS structure describing a DACL entry.
 *            Caller must have READ_CONTRL/WRITE_DAC rights for object handle.
 *
 * RETURN CODES: Win32 status code (ERROR_SUCCESS if succeeds)
 */
DWORD
ObjectDaclEntryAdd(HANDLE objectHandle, SE_OBJECT_TYPE objectType,
		   WELLKNOWN_TRUSTEE_ID trustee, DWORD accessPerm,
		   ACCESS_MODE accessMode, DWORD inheritance)
{
    DWORD status = ERROR_SUCCESS;
    PSID trusteeSidP;

    /* allocate SID for (well-known) trustee */

    if (trustee == WorldGroup) {
	if (!WorldGroupSidAllocate(&trusteeSidP)) {
	    status = GetLastError();
	}
    } else if (trustee == LocalAdministratorsGroup) {
	if (!LocalAdminsGroupSidAllocate(&trusteeSidP)) {
	    status = GetLastError();
	}
    } else {
	status = ERROR_INVALID_PARAMETER;
    }

    if (status == ERROR_SUCCESS) {
	EXPLICIT_ACCESS accessEntry;
	PACL curDaclP, newDaclP;
	PSECURITY_DESCRIPTOR secP;

	/* initialize access information for trustee */

	BuildExplicitAccessWithSid(&accessEntry, trusteeSidP, accessPerm,
				   accessMode, inheritance);

	/* get object's current DACL */

	status =
	    GetSecurityInfo(objectHandle, objectType,
			    DACL_SECURITY_INFORMATION, NULL, NULL, &curDaclP,
			    NULL, &secP);

	if (status == ERROR_SUCCESS) {
	    /* merge access information into current DACL to form new DACL */
	    status = SetEntriesInAcl(1, &accessEntry, curDaclP, &newDaclP);

	    if (status == ERROR_SUCCESS) {
		/* replace object's current DACL with newly formed DACL */

		/* MS SP4 introduced a bug into SetSecurityInfo() so that it
		 * no longer operates correctly with named pipes.  Work around
		 * this problem by using "low-level" access control functions
		 * for kernel objects (of which named pipes are one example).
		 */

		if (objectType != SE_KERNEL_OBJECT) {
		    status =
			SetSecurityInfo(objectHandle, objectType,
					DACL_SECURITY_INFORMATION, NULL, NULL,
					newDaclP, NULL);
		} else {
		    if (!SetSecurityDescriptorDacl
			(secP, TRUE, newDaclP, FALSE)
			|| !SetKernelObjectSecurity(objectHandle,
						    DACL_SECURITY_INFORMATION,
						    secP)) {
			status = GetLastError();
		    }
		}

		(void)LocalFree((HLOCAL) newDaclP);
	    }

	    (void)LocalFree((HLOCAL) secP);
	}

	FreeSid(trusteeSidP);
    }

    return status;
}