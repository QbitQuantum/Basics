static int gg_rand(void *buff, size_t len)
{
#ifdef _WIN32
	HCRYPTPROV hProvider = 0;
	int res = 0;

	if (!CryptAcquireContextW(&hProvider, 0, 0, PROV_RSA_FULL,
		CRYPT_VERIFYCONTEXT | CRYPT_SILENT))
	{
		gg_debug(GG_DEBUG_MISC | GG_DEBUG_ERROR, "// gg_rand() "
			"couldn't acquire crypto context\n");
		return -1;
	}

	if (!CryptGenRandom(hProvider, len, buff)) {
		gg_debug(GG_DEBUG_MISC | GG_DEBUG_ERROR, "// gg_rand() "
			"couldn't fill random buffer\n");
		res = -1;
	}

	CryptReleaseContext(hProvider, 0);

	return res;
#else
	uint8_t *buff_b = buff;

	int fd = open("/dev/random", O_RDONLY);
	if (fd < 0)
		fd = open("/dev/urandom", O_RDONLY);
	if (fd < 0) {
		gg_debug(GG_DEBUG_MISC | GG_DEBUG_ERROR, "// gg_rand() "
			"couldn't open random device\n");
		return -1;
	}

	while (len > 0) {
		/* TODO: handle EINTR */
		ssize_t got_data = read(fd, buff_b, len);
		if (got_data < 0) {
			gg_debug(GG_DEBUG_MISC | GG_DEBUG_ERROR, "// gg_rand() "
				"couldn't read from random device\n");
			close(fd);
			return -1;
		}

		buff_b += got_data;
		len -= got_data;
	}

	close(fd);

	return 0;
#endif
}