void ecmd_net_init()
{
  /* Without teensy support we use tcp */
    uip_listen(HTONS(ECMD_TCP_PORT), ecmd_net_main);
}