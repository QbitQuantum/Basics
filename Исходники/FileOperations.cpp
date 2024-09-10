bool FileVEILOperationsImpl::EncryptSignStream(std::shared_ptr<IDataReader> inputData, std::shared_ptr<IDataWriter> outputData, std::shared_ptr<ICmsHeader> Header, CompressionType comp, TS_ALG_ID algorithm,
	TS_ALG_ID hashAlgorithm, bool SignHeader, bool bindData, CMSFileFormatIds DataFormat, bool randomIvec, SymmetricPaddingType paddingType, int blockSize)
{
	TSDECLARE_FUNCTIONExt(true);

	std::shared_ptr<ICmsHeaderBase> header2;
	std::shared_ptr<ICmsHeader> header7;
	std::shared_ptr<IKeyGenCallback> callback;
	int64_t fileSize = 0;

	if (Header == NULL)
	{
		LogError("The CKM Header is missing.");
		return TSRETURN_ERROR(("Bad Header"), false);
	}

	if (!Header->DuplicateHeader(header2))
	{
		LogError("The specified CKM Header is incomplete or invalid.");
		return TSRETURN_ERROR(("Bad Header"), false);
	}
	if (!(header7 = std::dynamic_pointer_cast<ICmsHeader>(header2)))
	{
		LogError("The specified CKM Header is incomplete or invalid.");
		return TSRETURN_ERROR(("Bad Header"), false);
	}

	//
	// Now get the length of the source file
	//
	if (inputData->AllowsRandomAccess())
		fileSize = inputData->DataLength();
	else
		fileSize = -1;

	if (!PrepareHeader(header7, comp, algorithm, hashAlgorithm, SignHeader, bindData, DataFormat, randomIvec, paddingType, blockSize, fileSize))
	{
		LogError("The specified CKM Header could not be prepared for key generation.");
		return TSRETURN_ERROR(("Bad Header"), false);
	}

	//	CkmDevOnly << "Header after prepare" << endl << indent << TSHeaderToString(header7) << endl << outdent;

#ifdef HAVE_BSTR
	// TODO:  Implement Linux mime support here - libmagic
	{
		tscrypto::tsCryptoData tmp;
		CryptoUtf16 tmpBstr(inputData->DataName());
		LPWSTR mime = NULL;

		if (inputData->PeekData(4096, tmp))
		{
			if (FindMimeFromData(NULL, tmpBstr.c_str(), tmp.rawData(), (DWORD)tmp.size(), NULL, 3 /*FMFD_ENABLEMIMESNIFFING | FMFD_URLASFILENAME*/, &mime, 0) >= 0)
			{
				if (mime != NULL && mime[0] != 0)
				{
					header7->SetMimeType(CryptoUtf16(mime).toUtf8());
				}
			}
		}
	}
#endif // HAVE_BSTR

	std::shared_ptr<ICryptoHelper> helper;

	if (!m_session && header7->NeedsSession())
	{
		if (!!m_sessionCallback)
		{
			if (!(m_sessionCallback->GetSessionForHeader(true, header2, 0, m_session)))
			{
				LogError("No session.");
				return TSRETURN_ERROR(("Returns ~~"), false);
			}
		}
	}

	if (!m_session)
	{
		LogError("Unable to retrieve the cryptographic helper object from the CKM Runtime.");
		return TSRETURN_ERROR(("Returns ~~"), false);
	}
	else
	{
		if (!(helper = CreateCryptoHelper(m_session)))
		{
			LogError("Unable to generate the working key and encrypted data - Unable to create the helper.");
			return TSRETURN_ERROR(("Unable to generate the working key and encrypted data."), false);
		}
	}

	helper->SetOperationStatusCallback(m_status);
	helper->SetTaskInformation(m_currentTask, m_taskCount);
	if (!!m_keyGenCallback)
		helper->SetKeyGenCallback(m_keyGenCallback);

	if (!header7->SetDataName(inputData->DataName().c_str()))
	{
		LOG(DebugInfo1, "WARNING:  Unable to save the original file name.  Continuing to process the file.\n");
	}

	if (!helper->EncryptStream(comp, algorithm, hashAlgorithm, header2, true, tscrypto::tsCryptoData(), inputData, outputData, SignHeader,
		bindData, DataFormat, randomIvec, paddingType, blockSize))
	{
		LogError("Unable to encrypt the data.");
		return TSRETURN_ERROR(("Unable to encrypt the data."), false);
	}

	return TSRETURN(("OK"), true);
}