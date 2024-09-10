int	udpclo(int a1, int a2, int a3, int a4, int a5,
		int a6, int a7, int a8, int a9, int a10)
{
#else
int	main(int argc, char *argv[])
{
#endif
	unsigned char		*buffer;
	VOutduct		*vduct;
	PsmAddress		vductElt;
	Sdr			sdr;
	Outduct			outduct;
	ClProtocol		protocol;
	Outflow			outflows[3];
	int			i;
	char			*hostName;
	unsigned short		portNbr;
	unsigned int		hostNbr;
	struct sockaddr		socketName;
	struct sockaddr_in	*inetName;
	Object			bundleZco;
	BpExtendedCOS		extendedCOS;
	char			destDuctName[MAX_CL_DUCT_NAME_LEN + 1];
	unsigned int		bundleLength;
	int			ductSocket = -1;
	int			bytesSent;

	if (bpAttach() < 0)
	{
		putErrmsg("udpclo can't attach to BP.", NULL);
		return -1;
	}

	buffer = MTAKE(UDPCLA_BUFSZ);
	if (buffer == NULL)
	{
		putErrmsg("No memory for UDP buffer in udpclo.", NULL);
		return -1;
	}

	findOutduct("udp", "*", &vduct, &vductElt);
	if (vductElt == 0)
	{
		putErrmsg("No such udp duct.", "*");
		MRELEASE(buffer);
		return -1;
	}

	if (vduct->cloPid > 0 && vduct->cloPid != sm_TaskIdSelf())
	{
		putErrmsg("CLO task is already started for this duct.",
				itoa(vduct->cloPid));
		MRELEASE(buffer);
		return -1;
	}

	/*	All command-line arguments are now validated.		*/

	sdr = getIonsdr();
	sdr_read(sdr, (char *) &outduct, sdr_list_data(sdr, vduct->outductElt),
			sizeof(Outduct));
	sdr_read(sdr, (char *) &protocol, outduct.protocol, sizeof(ClProtocol));
	if (protocol.nominalRate <= 0)
	{
		vduct->xmitThrottle.nominalRate = DEFAULT_UDP_RATE;
	}
	else
	{
		vduct->xmitThrottle.nominalRate = protocol.nominalRate;
	}

	memset((char *) outflows, 0, sizeof outflows);
	outflows[0].outboundBundles = outduct.bulkQueue;
	outflows[1].outboundBundles = outduct.stdQueue;
	outflows[2].outboundBundles = outduct.urgentQueue;
	for (i = 0; i < 3; i++)
	{
		outflows[i].svcFactor = 1 << i;
	}

	/*	Set up signal handling.  SIGTERM is shutdown signal.	*/

	oK(udpcloSemaphore(&(vduct->semaphore)));
	isignal(SIGTERM, shutDownClo);

	/*	Can now begin transmitting to remote duct.		*/

	writeMemo("[i] udpclo is running.");
	while (!(sm_SemEnded(vduct->semaphore)))
	{
		if (bpDequeue(vduct, outflows, &bundleZco, &extendedCOS,
				destDuctName) < 0)
		{
			sm_SemEnd(udpcloSemaphore(NULL));/*	Stop.	*/
			continue;
		}

		if (bundleZco == 0)	/*	Interrupted.		*/
		{
			continue;
		}

		hostName = destDuctName;
		parseSocketSpec(destDuctName, &portNbr, &hostNbr);
		if (portNbr == 0)
		{
			portNbr = BpUdpDefaultPortNbr;
		}

		portNbr = htons(portNbr);
		if (hostNbr == 0)
		{
			writeMemoNote("[?] Can't get IP address for host",
					hostName);
		}

		hostNbr = htonl(hostNbr);
		memset((char *) &socketName, 0, sizeof socketName);
		inetName = (struct sockaddr_in *) &socketName;
		inetName->sin_family = AF_INET;
		inetName->sin_port = portNbr;
		memcpy((char *) &(inetName->sin_addr.s_addr),
				(char *) &hostNbr, 4);
		bundleLength = zco_length(sdr, bundleZco);
		bytesSent = sendBundleByUDP(&socketName, &ductSocket,
				bundleLength, bundleZco, buffer);
		if (bytesSent < bundleLength)
		{
			sm_SemEnd(udpcloSemaphore(NULL));/*	Stop.	*/
			continue;
		}

		/*	Make sure other tasks have a chance to run.	*/

		sm_TaskYield();
	}

	if (ductSocket != -1)
	{
		close(ductSocket);
	}

	writeErrmsgMemos();
	writeMemo("[i] udpclo duct has ended.");
	MRELEASE(buffer);
	ionDetach();
	return 0;
}