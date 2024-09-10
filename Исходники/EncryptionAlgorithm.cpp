	void EncryptionAlgorithm::Decrypt (const BufferPtr &data) const
	{
		Decrypt (data, data.Size());
	}