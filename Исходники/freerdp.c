/* Process receivable fds, return true if connection should live on */
static int
l_rdp_check_fds(rdpInst * inst)
{
	rdpRdp * rdp;
	RD_BOOL deactivated;
	int rv;

	rdp = RDP_FROM_INST(inst);
#ifdef _WIN32
	WSAResetEvent(rdp->sec->mcs->iso->tcp->wsa_event);
#endif
	rv = 0;
	if (tcp_can_recv(rdp->sec->mcs->iso->tcp->sock, 0))
	{
		if (!rdp_loop(rdp, &deactivated))
		{
			rv = 1;
		}
	}
	if ((rv != 0) && rdp->redirect)
	{
		rdp->redirect = False;
		if (rdp_reconnect(rdp))
		{
			rv = 0;
		}
	}
	return rv;
}