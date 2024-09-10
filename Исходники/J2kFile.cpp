	bool CJ2kFile::Open(BYTE** ppData, int& nComponentsCount, int& nWidth, int& nHeight, const std::wstring& wsSrcPath, const std::wstring& wsXmlOptions)
	{
		Image *pImage = NULL;

		DecoderParams oParameters;

		// Установим стандартные значения параметров
		ApplyDecoderOptions(&oParameters, wsXmlOptions);

		///////////////////////////////////////////////////////////////////////////////////

		NSFile::CFileBinary oFile;
		if (!oFile.OpenFile(wsSrcPath))
			return false;

		DWORD nFileSize = oFile.GetFileSize();

		int type = check_j2000_type(oFile.GetFileNative());
		oFile.CloseFile();

		bool bOpenResult = false;
		if (!bOpenResult && type == 1)
			bOpenResult = (NULL != (pImage = Jp2ToImage(wsSrcPath, &oParameters)));

		if (!bOpenResult && type == 2)
			bOpenResult = (NULL != (pImage = J2kToImage(wsSrcPath, &oParameters)));

		if (!bOpenResult && type == 3)
			bOpenResult = (NULL != (pImage = Mj2ToImage(wsSrcPath, &oParameters)));

		if (!bOpenResult && type == 4)
			bOpenResult = (NULL != (pImage = JptToImage(wsSrcPath, &oParameters)));

		if (!bOpenResult)
		{
			Image_Destroy(pImage);
			return false;
		}

		nWidth  = pImage->pComponents[0].nWidth;
		nHeight = pImage->pComponents[0].nHeight;

		int nBufferSize = pImage->nCsiz * nWidth * nHeight;
		if (nBufferSize < 1 || pImage->nCsiz <= 0)
		{
			Image_Destroy(pImage);
			return false;
		}

		*ppData = new BYTE[nBufferSize];
		if (!(*ppData))
		{
			Image_Destroy(pImage);
			return false;
		}

		unsigned char* pBufferPtr = (unsigned char*)(*ppData);
		long nCreatedBufferSize = nBufferSize;

		nComponentsCount = pImage->nCsiz;

		// Пишем данные в pBufferPtr
		for (int nComponent = 1; nComponent < nComponentsCount; nComponent++)
		{
			if (pImage->pComponents[0].nXRsiz != pImage->pComponents[nComponent].nXRsiz
				|| pImage->pComponents[0].nYRsiz != pImage->pComponents[nComponent].nYRsiz
				|| pImage->pComponents[0].nPrecision != pImage->pComponents[nComponent].nPrecision)

			{
				delete[](*ppData);
				Image_Destroy(pImage);
				return false;
			}
		}

		int nResW = CeilDivPow2(pImage->pComponents[0].nWidth, pImage->pComponents[0].nFactorDiv2);
		int nResH = CeilDivPow2(pImage->pComponents[0].nHeight, pImage->pComponents[0].nFactorDiv2);

		for (int nIndex = 0; nIndex < nResW * nResH; nIndex++)
		{
			for (int nComponent = 0; nComponent < nComponentsCount; nComponent++)
			{
				pBufferPtr[nComponent] = pImage->pComponents[nComponent].pData[nWidth * nResH - ((nIndex) / (nResW)+1) * nWidth + (nIndex) % (nResW)];
			}
			pBufferPtr += nComponentsCount;
		}

		Image_Destroy(pImage);
		return true;
	}