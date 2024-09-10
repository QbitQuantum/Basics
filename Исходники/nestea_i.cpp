int
Nestea_i::load_data (void)
{
  ACE_FILE_IO file;
  ACE_FILE_Connector connector;

  if (connector.connect (file,
                         ACE_FILE_Addr (this->data_filename_),
                         0,
                         ACE_Addr::sap_any) == -1)
    ACE_ERROR_RETURN ((LM_ERROR,
                       "%p\n to %s",
                       "connect",
                       this->data_filename_),
                      -1);

  char str[MAX_UINT32_STR_LEN];

  int len = file.recv (str, MAX_UINT32_STR_LEN);
  str[len] = 0;

  if (len > 0)
    this->cans_ = ACE_OS::atoi (str);
  else
    this->cans_ = 0;
  return 0;
}