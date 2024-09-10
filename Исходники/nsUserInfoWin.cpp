NS_IMETHODIMP
nsUserInfo::GetFullname(PRUnichar **aFullname)
{
  NS_ENSURE_ARG_POINTER(aFullname);
  *aFullname = nullptr;

  PRUnichar fullName[512];
  DWORD size = mozilla::ArrayLength(fullName);

  if (GetUserNameExW(NameDisplay, fullName, &size)) {
    *aFullname = ToNewUnicode(nsDependentString(fullName));
  } else {
    DWORD getUsernameError = GetLastError();

    // Try to use the net APIs regardless of the error because it may be
    // able to obtain the information.
    PRUnichar username[UNLEN + 1];
    size = mozilla::ArrayLength(username);
    if (!GetUserNameW(username, &size)) {
      // ERROR_NONE_MAPPED means the user info is not filled out on this computer
      return getUsernameError == ERROR_NONE_MAPPED ?
             NS_ERROR_NOT_AVAILABLE : NS_ERROR_FAILURE;
    }

    const DWORD level = 2;
    LPBYTE info;
    // If the NetUserGetInfo function has no full name info it will return
    // success with an empty string.
    NET_API_STATUS status = NetUserGetInfo(nullptr, username, level, &info);
    if (status != NERR_Success) {
      // We have an error with NetUserGetInfo but we know the info is not
      // filled in because GetUserNameExW returned ERROR_NONE_MAPPED.
      return getUsernameError == ERROR_NONE_MAPPED ?
             NS_ERROR_NOT_AVAILABLE : NS_ERROR_FAILURE;
    }

    nsDependentString fullName =
      nsDependentString(reinterpret_cast<USER_INFO_2 *>(info)->usri2_full_name);

    // NetUserGetInfo returns an empty string if the full name is not filled out
    if (fullName.Length() == 0) {
      NetApiBufferFree(info);
      return NS_ERROR_NOT_AVAILABLE;
    }

    *aFullname = ToNewUnicode(fullName);
    NetApiBufferFree(info);
  }

  return (*aFullname) ? NS_OK : NS_ERROR_FAILURE;
}