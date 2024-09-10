	bool Plugin::IsPasswordCorrect (const CryptoSystem& cs)
	{
		if (!IsPasswordSet ())
			return false;

		const QByteArray& cookie = Settings_->value ("SecureStorageCookie").toByteArray ();
		try
		{
			cs.Decrypt (cookie);
			return true;
		}
		catch (const WrongHMACException&)
		{
			return false;
		}
	}