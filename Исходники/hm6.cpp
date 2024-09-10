BigInt getDecryptedMessageFromRSA_obj(BigInt m, RSA RSA_obj)
{
	return RSA_obj.decrypt(m);
}