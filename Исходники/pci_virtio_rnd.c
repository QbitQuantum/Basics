static int
pci_vtrnd_init(struct pci_devinst *pi, UNUSED char *opts)
{
	struct pci_vtrnd_softc *sc;
	int fd;
	int len;
	uint8_t v;

	/*
	 * Should always be able to open /dev/random.
	 */
	fd = open("/dev/random", O_RDONLY | O_NONBLOCK);

	assert(fd >= 0);

	/*
	 * Check that device is seeded and non-blocking.
	 */
	len = (int) read(fd, &v, sizeof(v));
	if (len <= 0) {
		WPRINTF(("vtrnd: /dev/random not ready, read(): %d", len));
		return (1);
	}

	sc = calloc(1, sizeof(struct pci_vtrnd_softc));

	vi_softc_linkup(&sc->vrsc_vs, &vtrnd_vi_consts, sc, pi, &sc->vrsc_vq);
	sc->vrsc_vs.vs_mtx = &sc->vrsc_mtx;

	sc->vrsc_vq.vq_qsize = VTRND_RINGSZ;

	/* keep /dev/random opened while emulating */
	sc->vrsc_fd = fd;

	/* initialize config space */
	pci_set_cfgdata16(pi, PCIR_DEVICE, VIRTIO_DEV_RANDOM);
	pci_set_cfgdata16(pi, PCIR_VENDOR, VIRTIO_VENDOR);
	pci_set_cfgdata8(pi, PCIR_CLASS, PCIC_CRYPTO);
	pci_set_cfgdata16(pi, PCIR_SUBDEV_0, VIRTIO_TYPE_ENTROPY);
	pci_set_cfgdata16(pi, PCIR_SUBVEND_0, VIRTIO_VENDOR);

	if (vi_intr_init(&sc->vrsc_vs, 1, fbsdrun_virtio_msix()))
		return (1);
	vi_set_io_bar(&sc->vrsc_vs, 0);

	return (0);
}