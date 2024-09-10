static int
pci_vtnet_init(struct vmctx *ctx, struct pci_devinst *pi, char *opts)
{
	MD5_CTX mdctx;
	unsigned char digest[16];
	char nstr[80];
	char tname[MAXCOMLEN + 1];
	struct pci_vtnet_softc *sc;
	char *devname;
	char *vtopts;
	int mac_provided;

	sc = calloc(1, sizeof(struct pci_vtnet_softc));

	pthread_mutex_init(&sc->vsc_mtx, NULL);

	vi_softc_linkup(&sc->vsc_vs, &vtnet_vi_consts, sc, pi, sc->vsc_queues);
	sc->vsc_vs.vs_mtx = &sc->vsc_mtx;

	sc->vsc_queues[VTNET_RXQ].vq_qsize = VTNET_RINGSZ;
	sc->vsc_queues[VTNET_RXQ].vq_notify = pci_vtnet_ping_rxq;
	sc->vsc_queues[VTNET_TXQ].vq_qsize = VTNET_RINGSZ;
	sc->vsc_queues[VTNET_TXQ].vq_notify = pci_vtnet_ping_txq;
#ifdef notyet
	sc->vsc_queues[VTNET_CTLQ].vq_qsize = VTNET_RINGSZ;
        sc->vsc_queues[VTNET_CTLQ].vq_notify = pci_vtnet_ping_ctlq;
#endif
 
	/*
	 * Attempt to open the tap device and read the MAC address
	 * if specified
	 */
	mac_provided = 0;
	sc->vsc_tapfd = -1;
	if (opts != NULL) {
		char tbuf[80];
		int err;

		devname = vtopts = strdup(opts);
		(void) strsep(&vtopts, ",");

		if (vtopts != NULL) {
			err = pci_vtnet_parsemac(vtopts, sc->vsc_config.mac);
			if (err != 0) {
				free(devname);
				return (err);
			}
			mac_provided = 1;
		}

		strcpy(tbuf, "/dev/");
		strlcat(tbuf, devname, sizeof(tbuf));

		free(devname);

		sc->vsc_tapfd = open(tbuf, O_RDWR);
		if (sc->vsc_tapfd == -1) {
			WPRINTF(("open of tap device %s failed\n", tbuf));
		} else {
			/*
			 * Set non-blocking and register for read
			 * notifications with the event loop
			 */
			int opt = 1;
			if (ioctl(sc->vsc_tapfd, FIONBIO, &opt) < 0) {
				WPRINTF(("tap device O_NONBLOCK failed\n"));
				close(sc->vsc_tapfd);
				sc->vsc_tapfd = -1;
			}

			sc->vsc_mevp = mevent_add(sc->vsc_tapfd,
						  EVF_READ,
						  pci_vtnet_tap_callback,
						  sc);
			if (sc->vsc_mevp == NULL) {
				WPRINTF(("Could not register event\n"));
				close(sc->vsc_tapfd);
				sc->vsc_tapfd = -1;
			}
		}		
	}

	/*
	 * The default MAC address is the standard NetApp OUI of 00-a0-98,
	 * followed by an MD5 of the PCI slot/func number and dev name
	 */
	if (!mac_provided) {
		snprintf(nstr, sizeof(nstr), "%d-%d-%s", pi->pi_slot,
		    pi->pi_func, vmname);

		MD5Init(&mdctx);
		MD5Update(&mdctx, nstr, strlen(nstr));
		MD5Final(digest, &mdctx);

		sc->vsc_config.mac[0] = 0x00;
		sc->vsc_config.mac[1] = 0xa0;
		sc->vsc_config.mac[2] = 0x98;
		sc->vsc_config.mac[3] = digest[0];
		sc->vsc_config.mac[4] = digest[1];
		sc->vsc_config.mac[5] = digest[2];
	}

	/* initialize config space */
	pci_set_cfgdata16(pi, PCIR_DEVICE, VIRTIO_DEV_NET);
	pci_set_cfgdata16(pi, PCIR_VENDOR, VIRTIO_VENDOR);
	pci_set_cfgdata8(pi, PCIR_CLASS, PCIC_NETWORK);
	pci_set_cfgdata16(pi, PCIR_SUBDEV_0, VIRTIO_TYPE_NET);

	pci_lintr_request(pi);

	/* link always up */
	sc->vsc_config.status = 1;
	
	/* use BAR 1 to map MSI-X table and PBA, if we're using MSI-X */
	if (vi_intr_init(&sc->vsc_vs, 1, fbsdrun_virtio_msix()))
		return (1);

	/* use BAR 0 to map config regs in IO space */
	vi_set_io_bar(&sc->vsc_vs, 0);

	sc->resetting = 0;

	sc->rx_merge = 1;
	sc->rx_vhdrlen = sizeof(struct virtio_net_rxhdr);
	sc->rx_in_progress = 0;
	pthread_mutex_init(&sc->rx_mtx, NULL); 

	/* 
	 * Initialize tx semaphore & spawn TX processing thread.
	 * As of now, only one thread for TX desc processing is
	 * spawned. 
	 */
	sc->tx_in_progress = 0;
	pthread_mutex_init(&sc->tx_mtx, NULL);
	pthread_cond_init(&sc->tx_cond, NULL);
	pthread_create(&sc->tx_tid, NULL, pci_vtnet_tx_thread, (void *)sc);
	snprintf(tname, sizeof(tname), "vtnet-%d:%d tx", pi->pi_slot,
	    pi->pi_func);
        pthread_set_name_np(sc->tx_tid, tname);

	return (0);
}