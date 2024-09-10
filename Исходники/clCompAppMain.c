void AddRemVirtualAddress(const char *cmd,const VirtualIpAddress* vip)
{
  if (vip->ip && vip->dev && vip->netmask)
    {
      char exec[81];
      snprintf(exec,80,"%s/virtualIp %s %s %s %s ", CL_APP_BINDIR, cmd,vip->ip,vip->netmask,vip->dev);
      system(exec);

      if (cmd[0] == 'u')  /* If we are coming up, do a gratuitous arp */
        SendArp(vip->ip,vip->dev);
    }
}