static int
iwin32_file_set_sid (const char *file, PSID sid)
{
  char file_sd_buf [256];
  PSECURITY_DESCRIPTOR file_sd = (PSECURITY_DESCRIPTOR) &file_sd_buf;

  if (!InitializeSecurityDescriptor (file_sd, SECURITY_DESCRIPTOR_REVISION)) return 0;
  if (!SetSecurityDescriptorOwner (file_sd, sid, FALSE)) return 0;
  if (!IsValidSecurityDescriptor (file_sd)) return 0;
  if (!SetFileSecurity (file, (SECURITY_INFORMATION)(OWNER_SECURITY_INFORMATION),
    file_sd)) return 0;

  return 1;
}