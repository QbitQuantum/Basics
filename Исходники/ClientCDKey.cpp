// ClientCDKey::DecryptKey
// Decrypt 16 byte binary key into 8 byte buffer.  Uses symmetric key built from product
// name for decryption.
bool
ClientCDKey::DecryptKey(__int64& theBufR)
{
	WTRACE("ClientCDKey::DecryptKey");
	try
	{
		// Build symmetric key from product
		WDBG_LL("ClientCDKey::DecryptKey Creating symmetric key from product=" << mProduct);
		BFSymmetricKey aSymKey;
		CreateSymmetricKey(aSymKey);

		// Decrypt the key
		WDBG_LL("ClientCDKey::DecryptKey Decrypting CDKey.");
		BFSymmetricKey::CryptReturn aDecrypt(aSymKey.Decrypt(mBinKey.data(), mBinKey.size()));
		auto_ptr<unsigned char>     aDelP(aDecrypt.first);
		if (aDecrypt.second != sizeof(theBufR))
		{
			WDBG_LM("ClientCDKey::DecryptKey Decrypt of key has bad length.");
			return false;
		}

		// Fill buffer with decrypted key
		memcpy(static_cast<void*>(&theBufR), aDecrypt.first, sizeof(theBufR));
	}
	catch (WONCrypt::CryptException& anExR)
	{
		WDBG_LH("ClientCDKey::DecryptKey exception decrypting key: " << anExR);
		return false;
	}

	return true;
}