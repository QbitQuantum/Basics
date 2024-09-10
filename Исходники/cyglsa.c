NTSTATUS NTAPI
LsaApLogonUserEx (PLSA_CLIENT_REQUEST request, SECURITY_LOGON_TYPE logon_type,
		  PVOID auth, PVOID client_auth_base, ULONG auth_len,
		  PVOID *pbuf, PULONG pbuf_len, PLUID logon_id,
		  PNTSTATUS sub_stat, PLSA_TOKEN_INFORMATION_TYPE tok_type,
		  PVOID *tok, PUNICODE_STRING *account,
		  PUNICODE_STRING *authority, PUNICODE_STRING *machine)
{
  DWORD checksum, i;
  PDWORD csp, csp_end;
  NTSTATUS stat;
  SECPKG_CLIENT_INFO clinf;
  PLSA_TOKEN_INFORMATION_V2 tokinf;

  cyglsa_t *authinf = (cyglsa_t *) auth;

  /* Check if the caller has the SeTcbPrivilege, otherwise refuse service. */
  stat = funcs->GetClientInfo (&clinf);
  if (stat != STATUS_SUCCESS)
    {
      cyglsa_printf ("GetClientInfo failed: 0x%08lx\n", stat);
      return stat;
    }
  if (!clinf.HasTcbPrivilege)
    {
      cyglsa_printf ("Client has no TCB privilege.  Access denied.\n");
      return STATUS_ACCESS_DENIED;
    }

  /* Make a couple of validity checks. */
  if (auth_len < sizeof *authinf
      || authinf->magic != CYG_LSA_MAGIC
      || !authinf->username[0]
      || !authinf->domain[0])
    {
      cyglsa_printf ("Invalid authentication parameter.\n");
      return STATUS_INVALID_PARAMETER;
    }
  checksum = CYG_LSA_MAGIC;
  csp = (PDWORD) &authinf->username;
  csp_end = (PDWORD) ((PBYTE) authinf + auth_len);
  while (csp < csp_end)
    checksum += *csp++;
  if (authinf->checksum != checksum)
    {
      cyglsa_printf ("Invalid checksum.\n");
      return STATUS_INVALID_PARAMETER_3;
    }

  /* Set account to username and authority to domain resp. machine name.
     The name of the logon account name as returned by LookupAccountSid
     is created from here as "authority\account". */
  authinf->username[UNLEN] = '\0';
  authinf->domain[MAX_DOMAIN_NAME_LEN] = '\0';
  if (account && !(*account = uni_alloc (authinf->username,
  					 wcslen (authinf->username))))
    {
      cyglsa_printf ("No memory trying to create account.\n");
      return STATUS_NO_MEMORY;
    }
  if (authority && !(*authority = uni_alloc (authinf->domain,
					     wcslen (authinf->domain))))
    {
      cyglsa_printf ("No memory trying to create authority.\n");
      return STATUS_NO_MEMORY;
    }
  if (machine)
    {
      WCHAR mach[MAX_COMPUTERNAME_LENGTH + 1];
      DWORD msize = MAX_COMPUTERNAME_LENGTH + 1;
      if (!GetComputerNameW (mach, &msize))
        wcscpy (mach, L"UNKNOWN");
      if (!(*machine = uni_alloc (mach, wcslen (mach))))
	{
	  cyglsa_printf ("No memory trying to create machine.\n");
	  return STATUS_NO_MEMORY;
	}
    }
  /* Create a fake buffer in pbuf which is free'd again in the client.
     Windows 2000 tends to crash when setting this pointer to NULL. */
  if (pbuf)
    {
#ifdef JUST_ANOTHER_NONWORKING_SOLUTION
      cygprf_t prf;
      WCHAR sam_username[MAX_DOMAIN_NAME_LEN + UNLEN + 2];
      SECURITY_STRING sam_user, prefix;
      PUCHAR user_auth;
      ULONG user_auth_size;
      WCHAR flatname[UNLEN + 1];
      UNICODE_STRING flatnm;
      TOKEN_SOURCE ts;
      HANDLE token;
#endif /* JUST_ANOTHER_NONWORKING_SOLUTION */

      stat = funcs->AllocateClientBuffer (request, 64UL, pbuf);
      if (!LSA_SUCCESS (stat))
	{
	  cyglsa_printf ("AllocateClientBuffer failed: 0x%08lx\n", stat);
	  return stat;
	}
#ifdef JUST_ANOTHER_NONWORKING_SOLUTION
      prf.magic_pre = MAGIC_PRE;
      prf.token = NULL;
      prf.magic_post = MAGIC_POST;

#if 0
      /* That's how it was supposed to work according to MSDN... */
      wcscpy (sam_username, authinf->domain);
      wcscat (sam_username, L"\\");
      wcscat (sam_username, authinf->username);
#else
      /* That's the only solution which worked, and then it only worked
         for machine local accounts.  No domain authentication possible.
	 STATUS_NO_SUCH_USER galore! */
      wcscpy (sam_username, authinf->username);
#endif
      RtlInitUnicodeString (&sam_user, sam_username);
      RtlInitUnicodeString (&prefix, L"");
      RtlInitEmptyUnicodeString (&flatnm, flatname,
				 (UNLEN + 1) * sizeof (WCHAR));

      stat = funcs->GetAuthDataForUser (&sam_user, SecNameSamCompatible,
					NULL, &user_auth,
					&user_auth_size, &flatnm);
      if (!NT_SUCCESS (stat))
	{
	  char sam_u[MAX_DOMAIN_NAME_LEN + UNLEN + 2];
	  wcstombs (sam_u, sam_user.Buffer, sizeof (sam_u));
	  cyglsa_printf ("GetAuthDataForUser (%u,%u,%s) failed: 0x%08lx\n",
		  sam_user.Length, sam_user.MaximumLength, sam_u, stat);
	  return stat;
	}

      memcpy (ts.SourceName, "Cygwin.1", 8);
      ts.SourceIdentifier.HighPart = 0;
      ts.SourceIdentifier.LowPart = 0x0104;
      RtlInitEmptyUnicodeString (&flatnm, flatname,
				 (UNLEN + 1) * sizeof (WCHAR));
      stat = funcs->ConvertAuthDataToToken (user_auth, user_auth_size,
					    SecurityDelegation, &ts,
					    Interactive, *authority,
					    &token, logon_id, &flatnm,
					    sub_stat);
      if (!NT_SUCCESS (stat))
	{
	  cyglsa_printf ("ConvertAuthDataToToken failed: 0x%08lx\n", stat);
	  return stat;
	}

      stat = funcs->DuplicateHandle (token, &prf.token);
      if (!NT_SUCCESS (stat))
	{
	  cyglsa_printf ("DuplicateHandle failed: 0x%08lx\n", stat);
	  return stat;
	}
      
      stat = funcs->CopyToClientBuffer (request, sizeof prf, *pbuf, &prf);
      if (!NT_SUCCESS (stat))
	{
	  cyglsa_printf ("CopyToClientBuffer failed: 0x%08lx\n", stat);
	  return stat;
	}
      funcs->FreeLsaHeap (user_auth);
#endif /* JUST_ANOTHER_NONWORKING_SOLUTION */
    }
  if (pbuf_len)
    *pbuf_len = 64UL;

  /* A PLSA_TOKEN_INFORMATION_V2 is allocated in one piece, so... */
#if defined (__x86_64__) || defined (_M_AMD64)
    {
      /* ...on 64 bit systems we have to convert the incoming 32 bit offsets
	 into 64 bit pointers.  That requires to re-evaluate the size of the
	 outgoing tokinf structure and a somewhat awkward procedure to copy
	 the information over. */
      LONG_PTR base;
      PBYTE tptr;
      DWORD size, newsize;
      PSID src_sid;
      PCYG_TOKEN_GROUPS src_grps;
      PTOKEN_GROUPS grps;
      PTOKEN_PRIVILEGES src_privs;
      PACL src_acl;

      base = (LONG_PTR) &authinf->inf;

      newsize = authinf->inf_size;
      newsize += sizeof (TOKEN_USER) - sizeof (CYG_TOKEN_USER); /* User SID */
      newsize += sizeof (PTOKEN_GROUPS) - sizeof (OFFSET); /* Groups */
      src_grps = (PCYG_TOKEN_GROUPS) (base + authinf->inf.Groups);
      newsize += src_grps->GroupCount		  /* Group SIDs */
      		 * (sizeof (SID_AND_ATTRIBUTES)
		    - sizeof (CYG_SID_AND_ATTRIBUTES));
      newsize += sizeof (PSID) - sizeof (OFFSET); /* Primary Group SID */
      newsize += sizeof (PTOKEN_PRIVILEGES) - sizeof (OFFSET); /* Privileges */
      newsize += 0; /* Owner SID */
      newsize += sizeof (PACL) - sizeof (OFFSET); /* Default DACL */

      if (!(tokinf = funcs->AllocateLsaHeap (newsize)))
	return STATUS_NO_MEMORY;
      tptr = (PBYTE)(tokinf + 1);

      tokinf->ExpirationTime = authinf->inf.ExpirationTime;
      /* User SID */
      src_sid = (PSID) (base + authinf->inf.User.User.Sid);
      size = RtlLengthSid (src_sid);
      RtlCopySid (size, (PSID) tptr, src_sid);
      tokinf->User.User.Sid = (PSID) tptr;
      tptr += size;
      tokinf->User.User.Attributes = authinf->inf.User.User.Attributes;
      /* Groups */
      grps = (PTOKEN_GROUPS) tptr;
      tokinf->Groups = grps;
      grps->GroupCount = src_grps->GroupCount;
      tptr += sizeof grps->GroupCount
	      + grps->GroupCount * sizeof (SID_AND_ATTRIBUTES);
      /* Group SIDs */
      for (i = 0; i < src_grps->GroupCount; ++i)
	{
	  src_sid = (PSID) (base + src_grps->Groups[i].Sid);
	  size = RtlLengthSid (src_sid);
	  RtlCopySid (size, (PSID) tptr, src_sid);
	  tokinf->Groups->Groups[i].Sid = (PSID) tptr;
	  tptr += size;
	  tokinf->Groups->Groups[i].Attributes = src_grps->Groups[i].Attributes;
	}
      /* Primary Group SID */
      src_sid = (PSID) (base + authinf->inf.PrimaryGroup.PrimaryGroup);
      size = RtlLengthSid (src_sid);
      RtlCopySid (size, (PSID) tptr, src_sid);
      tokinf->PrimaryGroup.PrimaryGroup = (PSID) tptr;
      tptr += size;
      /* Privileges */
      src_privs = (PTOKEN_PRIVILEGES) (base + authinf->inf.Privileges);
      size = sizeof src_privs->PrivilegeCount
	     + src_privs->PrivilegeCount * sizeof (LUID_AND_ATTRIBUTES);
      memcpy (tptr, src_privs, size);
      tokinf->Privileges = (PTOKEN_PRIVILEGES) tptr;
      tptr += size;
      /* Owner */
      tokinf->Owner.Owner = NULL;
      /* Default DACL */
      src_acl = (PACL) (base + authinf->inf.DefaultDacl.DefaultDacl);
      size = src_acl->AclSize;
      memcpy (tptr, src_acl, size);
      tokinf->DefaultDacl.DefaultDacl = (PACL) tptr;
    }
#else
    {
      /* ...on 32 bit systems we just allocate tokinf with the same size as
         we get, copy the whole structure and convert offsets into pointers. */

      /* Allocate LUID for usage in the logon SID on Windows 2000.  This is
	 not done in the 64 bit code above for hopefully obvious reasons... */
      LUID logon_sid_id;

      if (must_create_logon_sid
	  && !NT_SUCCESS (NtAllocateLocallyUniqueId (&logon_sid_id)))
	return STATUS_INSUFFICIENT_RESOURCES;

      if (!(tokinf = funcs->AllocateLsaHeap (authinf->inf_size)))
	return STATUS_NO_MEMORY;
      memcpy (tokinf, &authinf->inf, authinf->inf_size);

      /* User SID */
      tokinf->User.User.Sid = (PSID)
	      ((PBYTE) tokinf + (LONG_PTR) tokinf->User.User.Sid);
      /* Groups */
      tokinf->Groups = (PTOKEN_GROUPS)
	      ((PBYTE) tokinf + (LONG_PTR) tokinf->Groups);
      /* Group SIDs */
      for (i = 0; i < tokinf->Groups->GroupCount; ++i)
	{
	  tokinf->Groups->Groups[i].Sid = (PSID)
		((PBYTE) tokinf + (LONG_PTR) tokinf->Groups->Groups[i].Sid);
	  if (must_create_logon_sid
	      && tokinf->Groups->Groups[i].Attributes & SE_GROUP_LOGON_ID
	      && *RtlSubAuthorityCountSid (tokinf->Groups->Groups[i].Sid) == 3
	      && *RtlSubAuthoritySid (tokinf->Groups->Groups[i].Sid, 0)
		 == SECURITY_LOGON_IDS_RID)
	    {
	      *RtlSubAuthoritySid (tokinf->Groups->Groups[i].Sid, 1)
	      = logon_sid_id.HighPart;
	      *RtlSubAuthoritySid (tokinf->Groups->Groups[i].Sid, 2)
	      = logon_sid_id.LowPart;
	    }
	}

      /* Primary Group SID */
      tokinf->PrimaryGroup.PrimaryGroup = (PSID)
	      ((PBYTE) tokinf + (LONG_PTR) tokinf->PrimaryGroup.PrimaryGroup);
      /* Privileges */
      tokinf->Privileges = (PTOKEN_PRIVILEGES)
	      ((PBYTE) tokinf + (LONG_PTR) tokinf->Privileges);
      /* Owner SID */
      tokinf->Owner.Owner = NULL;
      /* Default DACL */
      tokinf->DefaultDacl.DefaultDacl = (PACL)
	      ((PBYTE) tokinf + (LONG_PTR) tokinf->DefaultDacl.DefaultDacl);

    }
#endif

  *tok = (PVOID) tokinf;
  *tok_type = LsaTokenInformationV2;

  print_tokinf (tokinf, authinf->inf_size, authinf, &authinf->inf,
		(PVOID)((LONG_PTR) &authinf->inf + authinf->inf_size));

  /* Create logon session. */
  stat = NtAllocateLocallyUniqueId (logon_id);
  if (!NT_SUCCESS (stat))
    {
      funcs->FreeLsaHeap (*tok);
      *tok = NULL;
      cyglsa_printf ("NtAllocateLocallyUniqueId status 0x%08lx\n", stat);
      return STATUS_INSUFFICIENT_RESOURCES;
    }
  stat = funcs->CreateLogonSession (logon_id);
  if (stat != STATUS_SUCCESS)
    {
      funcs->FreeLsaHeap (*tok);
      *tok = NULL;
      cyglsa_printf ("CreateLogonSession failed: 0x%08lx\n", stat);
      return stat;
    }

  cyglsa_printf ("BINGO!!!\n", stat);
  return STATUS_SUCCESS;
}