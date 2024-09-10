nozzle_t nozzle_open(char *devname, size_t devname_size, const char *updownpath)
{
	int savederrno = 0;
	nozzle_t nozzle = NULL;
	char *temp_mac = NULL;
#ifdef KNET_LINUX
	struct ifreq ifr;
#endif
#ifdef KNET_BSD
	uint16_t i;
	long int nozzlenum = 0;
	char curnozzle[IFNAMSIZ];
#endif

	if (devname == NULL) {
		errno = EINVAL;
		return NULL;
	}

	if (devname_size < IFNAMSIZ) {
		errno = EINVAL;
		return NULL;
	}

	if (strlen(devname) > IFNAMSIZ) {
		errno = E2BIG;
		return NULL;
	}

#ifdef KNET_BSD
	/*
	 * BSD does not support named devices like Linux
	 * but it is possible to force a nozzleX device number
	 * where X is 0 to 255.
	 */
	if (strlen(devname)) {
		if (strncmp(devname, "tap", 3)) {
			errno = EINVAL;
			return NULL;
		}
		errno = 0;
		nozzlenum = strtol(devname+3, NULL, 10);
		if (errno) {
			errno = EINVAL;
			return NULL;
		}
		if ((nozzlenum < 0) || (nozzlenum > 255)) {
			errno = EINVAL;
			return NULL;
		}
	}
#endif

	if (updownpath) {
		/* only absolute paths */
		if (updownpath[0] != '/') {
			errno = EINVAL;
			return NULL;
		}
		if (strlen(updownpath) >= UPDOWN_PATH_MAX) {
			errno = E2BIG;
			return NULL;
		}
	}

	savederrno = pthread_mutex_lock(&config_mutex);
	if (savederrno) {
		errno = savederrno;
		return NULL;
	}

	if (!lib_init) {
		lib_cfg.head = NULL;
#ifdef KNET_LINUX
		lib_cfg.nlsock = nl_socket_alloc();
		if (!lib_cfg.nlsock) {
			savederrno = errno;
			goto out_error;
		}
		if (nl_connect(lib_cfg.nlsock, NETLINK_ROUTE) < 0) {
			savederrno = EBUSY;
			goto out_error;
		}
		lib_cfg.ioctlfd = socket(AF_INET, SOCK_STREAM, 0);
#endif
#ifdef KNET_BSD
		lib_cfg.ioctlfd = socket(AF_LOCAL, SOCK_DGRAM, 0);
#endif
		if (lib_cfg.ioctlfd < 0) {
			savederrno = errno;
			goto out_error;
		}
		lib_init = 1;
	}

	nozzle = malloc(sizeof(struct nozzle_iface));
	if (!nozzle) {
		savederrno = ENOMEM;
		goto out_error;
	}

	memset(nozzle, 0, sizeof(struct nozzle_iface));

#ifdef KNET_BSD
	if (!strlen(devname)) {
		for (i = 0; i < 256; i++) {
			snprintf(curnozzle, sizeof(curnozzle) - 1, "/dev/tap%u", i);
			nozzle->fd = open(curnozzle, O_RDWR);
			savederrno = errno;
			if (nozzle->fd > 0) {
				break;
			}
		}
		snprintf(curnozzle, sizeof(curnozzle) -1 , "tap%u", i);
	} else {
		snprintf(curnozzle, sizeof(curnozzle) - 1, "/dev/%s", devname);
		nozzle->fd = open(curnozzle, O_RDWR);
		savederrno = errno;
		snprintf(curnozzle, sizeof(curnozzle) - 1, "%s", devname);
	}
	if (nozzle->fd < 0) {
		savederrno = EBUSY;
		goto out_error;
	}
	strncpy(devname, curnozzle, IFNAMSIZ);
	strncpy(nozzle->name, curnozzle, IFNAMSIZ);
#endif

#ifdef KNET_LINUX
	if ((nozzle->fd = open("/dev/net/tun", O_RDWR)) < 0) {
		savederrno = errno;
		goto out_error;
	}

	memset(&ifr, 0, sizeof(struct ifreq));
	memmove(ifname, devname, IFNAMSIZ);
	ifr.ifr_flags = IFF_TAP | IFF_NO_PI;

	if (ioctl(nozzle->fd, TUNSETIFF, &ifr) < 0) {
		savederrno = errno;
		goto out_error;
	}

	if ((strlen(devname) > 0) && (strcmp(devname, ifname) != 0)) {
		savederrno = EBUSY;
		goto out_error;
	}

	strncpy(devname, ifname, IFNAMSIZ);
	strncpy(nozzle->name, ifname, IFNAMSIZ);
#endif

	nozzle->default_mtu = get_iface_mtu(nozzle);
	if (nozzle->default_mtu < 0) {
		savederrno = errno;
		goto out_error;
	}

	if (get_iface_mac(nozzle, &temp_mac) < 0) {
		savederrno = errno;
		goto out_error;
	}

	strncpy(nozzle->default_mac, temp_mac, 18);
	free(temp_mac);

	if (updownpath) {
		int len = strlen(updownpath);

		strcpy(nozzle->updownpath, updownpath);
		if (nozzle->updownpath[len-1] != '/') {
			nozzle->updownpath[len] = '/';
		}
		nozzle->hasupdown = 1;
	}

	nozzle->next = lib_cfg.head;
	lib_cfg.head = nozzle;

	pthread_mutex_unlock(&config_mutex);
	errno = savederrno;
	return nozzle;

out_error:
	destroy_iface(nozzle);
	pthread_mutex_unlock(&config_mutex);
	errno = savederrno;
	return NULL;
}