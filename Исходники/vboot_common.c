int PublicKeyCopy(VbPublicKey *dest, const VbPublicKey *src)
{
	if (dest->key_size < src->key_size)
		return 1;

	dest->key_size = src->key_size;
	dest->algorithm = src->algorithm;
	dest->key_version = src->key_version;
	Memcpy(GetPublicKeyData(dest), GetPublicKeyDataC(src), src->key_size);
	return 0;
}