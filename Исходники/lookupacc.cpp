int
wmain(int argc, LPWSTR *argv)
{
  SetOemPrintFLineLength(GetStdHandle(STD_ERROR_HANDLE));

  DWORD (WINAPI *pConvertStringSidToSid)(LPCWSTR, PSID*) =
    (DWORD (WINAPI *)(LPCWSTR, PSID*))
    GetProcAddress(GetModuleHandleA("advapi32.dll"), "ConvertStringSidToSidW");

  if (argc < 2)
    {
      if (pConvertStringSidToSid != NULL)
	fputs("Utility to display basic account information about a user account given a user\r\n"
	      "name or SID.\r\n"
	      "\n"
	      "Syntax:\r\n"
	      "lookupacc [computer] S-n-n-n\r\n"
	      "lookupacc [computer] [domain\\]username\r\n"
	      "lookupacc [computer] username[@fqdn]\r\n", stderr);
      else
	fputs("Utility to display basic account information about a user account given a user\r\n"
	      "name.\r\n"
	      "\n"
	      "Syntax:\r\n"
	      "lookupacc [computer] [domain\\]username\r\n", stderr);
      return 1;
    }

  if (argc > 3)
    {
      fputs("Too many parameters.\r\n", stderr);
      return 1;
    }

  LPWSTR computername = NULL;
  if (argc > 2)
    {
      computername = argv[1];
      argc--;
      argv++;
    }

  SID_NAME_USE SIDnameuse;
  WCHAR userdomain[260] = L"";
  DWORD userdomainsiz = sizeof userdomain;
  WCHAR username[260] = L"";
  DWORD usernamesiz = sizeof username;
  BYTE userSID[260] = { 0 };
  DWORD userSIDsiz = sizeof userSID;
  LPWSTR wczUsername = L"(unknown)";
  PSID sidLookup = NULL;
  UNICODE_STRING StringSID = { 0 };
  BOOL bConversionResult = FALSE;

  if (pConvertStringSidToSid == NULL)
    bConversionResult = FALSE;
  else
    bConversionResult = pConvertStringSidToSid(argv[1], &sidLookup);

  if (bConversionResult)
    {
      if (!LookupAccountSid(computername, sidLookup, username, &usernamesiz,
			    userdomain, &userdomainsiz, &SIDnameuse))
	{
	  win_perror();
	  return 1;
	}

      RtlInitUnicodeString(&StringSID, argv[1]);
      wczUsername = username;
    }
  else
    {
      if (!LookupAccountName(computername, argv[1], &userSID, &userSIDsiz,
			     userdomain, &userdomainsiz, &SIDnameuse))
	{
	  win_perror();
	  return 1;
	}

      RtlConvertSidToUnicodeString(&StringSID, &userSID, TRUE);
      wczUsername = argv[1];
    }

  LPSTR czSIDnameuse;
  switch (SIDnameuse)
    {
    case SidTypeUser:
      czSIDnameuse = "User";
      break;
    case SidTypeGroup:
      czSIDnameuse = "Group";
      break;
    case SidTypeDomain:
      czSIDnameuse = "Domain";
      break;
    case SidTypeAlias:
      czSIDnameuse = "Alias";
      break;
    case SidTypeWellKnownGroup:
      czSIDnameuse = "Well known group";
      break;
    case SidTypeDeletedAccount:
      czSIDnameuse = "Deleted account";
      break;
    case SidTypeInvalid:
      czSIDnameuse = "Invalid";
      break;
    case SidTypeUnknown:
      czSIDnameuse = "Unknown";
      break;
    case SidTypeComputer:
      czSIDnameuse = "Computer";
      break;
    default:
      czSIDnameuse = "Not known";
      break;
    }

  oem_printf(stdout,
	     "Account type: %1%%n"
	     "User domain: %2!ws!%%n"
	     "User name: %3!ws!%%n"
	     "SID: %4!.*ws!%%n",
	     czSIDnameuse,
	     userdomain,
	     wczUsername,
	     StringSID.Length, StringSID.Buffer);

  return 0;
}