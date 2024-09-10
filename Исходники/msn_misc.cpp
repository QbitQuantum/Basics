void directconnection::xNonceToBin(UUID* nonce)
{
	size_t len = strlen(xNonce);
	char *p = (char*)alloca(len);
	strcpy(p, xNonce + 1);
	p[len-2] = 0;
	UuidFromStringA((BYTE*)p, nonce);
}