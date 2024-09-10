void Tserial_event::OnEvent (unsigned long events)
{
	unsigned long ModemStat;

	GetCommModemStatus(serial_handle, &ModemStat);

	if ((events & EV_RING)!=0)
	{
		if ((ModemStat &  MS_RING_ON)!= 0)
		{
			if (manager!=0)
				manager((uint32) this, SERIAL_RING);
		}
	}

	if ((events & EV_RLSD)!=0)
	{
		if ((ModemStat &  MS_RLSD_ON)!= 0)
		{
			if (manager!=0)
				manager((uint32) this, SERIAL_CD_ON);
		}
		else
		{
			if (manager!=0)
				manager((uint32) this, SERIAL_CD_OFF);
		}
	}
}