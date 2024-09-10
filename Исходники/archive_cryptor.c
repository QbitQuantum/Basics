static int
pbkdf2_sha1(const char *pw, size_t pw_len, const uint8_t *salt,
	size_t salt_len, unsigned rounds, uint8_t *derived_key,
	size_t derived_key_len)
{
	NTSTATUS status;
	BCRYPT_ALG_HANDLE hAlg;

	status = BCryptOpenAlgorithmProvider(&hAlg, BCRYPT_SHA1_ALGORITHM,
		MS_PRIMITIVE_PROVIDER, BCRYPT_ALG_HANDLE_HMAC_FLAG);
	if (!BCRYPT_SUCCESS(status))
		return -1;

	status = BCryptDeriveKeyPBKDF2(hAlg,
		(PUCHAR)(uintptr_t)pw, (ULONG)pw_len,
		(PUCHAR)(uintptr_t)salt, (ULONG)salt_len, rounds,
		(PUCHAR)derived_key, (ULONG)derived_key_len, 0);

	BCryptCloseAlgorithmProvider(hAlg, 0);

	return (BCRYPT_SUCCESS(status)) ? 0: -1;
}