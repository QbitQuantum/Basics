/* Reads the specified ASCII/ANSI string value from system registry */
SshRegBool
ssh_registry_asciiz_string_get(SshRegKey registry_key,
                               SshRegValue value_name,
                               unsigned char **string)
{
  SshRegBool success = FALSE;
  UNICODE_STRING uc_value;

  memset(&uc_value, 0x00, sizeof(uc_value));
  if (ssh_registry_unicode_string_get(registry_key, value_name, &uc_value))
    {
      SshUInt32 buf_size;
      ANSI_STRING ansi_str;

      buf_size = ((uc_value.Length / sizeof(uc_value.Buffer[0])) + 1);

      ansi_str.Length = 0;
      ansi_str.MaximumLength = (SshUInt16)buf_size;
      ansi_str.Buffer = ssh_calloc(1, ansi_str.MaximumLength);
      if (ansi_str.Buffer != NULL)
        {
          if (RtlUnicodeStringToAnsiString(&ansi_str, &uc_value, 
                                           FALSE) == STATUS_SUCCESS)
            {
              *string = ansi_str.Buffer;
              success = TRUE;
            }
          else
            {
              ssh_free(ansi_str.Buffer);
            }
        }

      ssh_free(uc_value.Buffer);
    }
  
  return success;
}