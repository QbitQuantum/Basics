void
yport_net_init(void)
{
    uip_listen(HTONS(YPORT_PORT), yport_net_main);
}