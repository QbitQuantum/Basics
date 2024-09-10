	void GarlicDestination::HandleGarlicMessage (std::shared_ptr<I2NPMessage> msg)
	{
		uint8_t * buf = msg->GetPayload ();
		uint32_t length = bufbe32toh (buf);
		if (length > msg->GetLength ())
		{
			LogPrint (eLogError, "Garlic message length ", length, " exceeds I2NP message length ", msg->GetLength ());
			return;
		}	
		buf += 4; // length
		auto it = m_Tags.find (SessionTag(buf));
		if (it != m_Tags.end ())
		{
			// tag found. Use AES
			if (length >= 32)
			{	
				uint8_t iv[32]; // IV is first 16 bytes
				CryptoPP::SHA256().CalculateDigest(iv, buf, 32);
				it->second->SetIV (iv);
				it->second->Decrypt (buf + 32, length - 32, buf + 32);
				HandleAESBlock (buf + 32, length - 32, it->second, msg->from);
			}	
			else
				LogPrint (eLogError, "Garlic message length ", length, " is less than 32 bytes");
			m_Tags.erase (it); // tag might be used only once	
		}
		else
		{
			// tag not found. Use ElGamal
			ElGamalBlock elGamal;
			if (length >= 514 && i2p::crypto::ElGamalDecrypt (GetEncryptionPrivateKey (), buf, (uint8_t *)&elGamal, true))
			{	
				auto decryption = std::make_shared<i2p::crypto::CBCDecryption>();
				decryption->SetKey (elGamal.sessionKey);
				uint8_t iv[32]; // IV is first 16 bytes
				CryptoPP::SHA256().CalculateDigest(iv, elGamal.preIV, 32); 
				decryption->SetIV (iv);
				decryption->Decrypt(buf + 514, length - 514, buf + 514);
				HandleAESBlock (buf + 514, length - 514, decryption, msg->from);
			}	
			else
				LogPrint (eLogError, "Failed to decrypt garlic");
		}

		// cleanup expired tags
		uint32_t ts = i2p::util::GetSecondsSinceEpoch ();
		if (ts > m_LastTagsCleanupTime + INCOMING_TAGS_EXPIRATION_TIMEOUT)
		{
			if (m_LastTagsCleanupTime)
			{
				int numExpiredTags = 0;
				for (auto it = m_Tags.begin (); it != m_Tags.end ();)
				{
					if (ts > it->first.creationTime + INCOMING_TAGS_EXPIRATION_TIMEOUT)
					{
						numExpiredTags++;
						it = m_Tags.erase (it);
					}	
					else
						it++;
				}
				LogPrint (numExpiredTags, " tags expired for ", GetIdentHash().ToBase64 ());
			}	
			m_LastTagsCleanupTime = ts;
		}	
	}	