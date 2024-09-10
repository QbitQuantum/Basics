BOOL lsa_error(NTSTATUS nt_status, LPCTSTR function)
{
  return win_error(LsaNtStatusToWinError(nt_status), function);
}