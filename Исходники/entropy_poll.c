int mbedtls_platform_entropy_poll(void *data, unsigned char *output, size_t len, size_t *olen)
{
	((void)data);
	*olen = 0;

	/*
	 * size_t may be 64 bits, but ULONG is always 32.
	 * If len is larger than the maximum for ULONG, just fail.
	 * It's unlikely anything ever will want to ask for this much randomness.
	 */
	if (len > 0xFFFFFFFFULL) {
		return (MBEDTLS_ERR_ENTROPY_SOURCE_FAILED);
	}

	if (!BCRYPT_SUCCESS(BCryptGenRandom(NULL, output, (ULONG) len, BCRYPT_USE_SYSTEM_PREFERRED_RNG))) {
		return (MBEDTLS_ERR_ENTROPY_SOURCE_FAILED);
	}

	*olen = len;

	return (0);
}