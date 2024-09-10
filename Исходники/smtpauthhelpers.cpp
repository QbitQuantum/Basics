TPtr8 CSmtpAuthCramMd5MechanismHelper::FormSharedSecret(TPtr8 aPassword)
	{
	TPtr8 secret = aPassword;
	
	if (aPassword.Length() <= KMd5BlockLength)
		{
		//pad up to 64 bytes with zeros
		secret.SetLength(64);
		TInt origLen = aPassword.Length();
		TInt lengthToFill = KMd5BlockLength-aPassword.Length();
		for (TInt i = 0; i<lengthToFill; i++)
			{
			secret[origLen+i]=0x00;
			}
		}
	else
		{
		//make shared secret the Digest of the password
		secret.Zero();
		iMd5Hash->Reset();
		secret = (iMd5Hash->Hash(aPassword));
		//do we need to call this function again now to pad out the 16 byte result?
		}

	return secret;
	}