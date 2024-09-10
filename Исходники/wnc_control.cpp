void resolve_mdm(void)
{
    do
    {
      WNC_MDM_ERR = WNC_OK;
      at_dnsresolve_wnc(MY_SERVER_URL, &MyServerIpAddress);
      if (WNC_MDM_ERR == WNC_NO_RESPONSE)
      {
        reinitialize_mdm();
        software_init_mdm();
      }
      else if (WNC_MDM_ERR == WNC_CMD_ERR)
      {
        pc.puts("Bad URL!!!!!!\r\n");
        MyServerIpAddress = "192.168.0.1";
        WNC_MDM_ERR = WNC_OK;
      }
    } while (WNC_MDM_ERR != WNC_OK);
    
    pc.printf("My Server IP: %s\r\n", MyServerIpAddress.data());
}