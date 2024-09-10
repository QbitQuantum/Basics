		LIB3MFMETHODIMP CCOMModelTexture2D::ReadFromStream(_In_ IStream * pStream)
		{
			try {
				if (pStream == nullptr)
					throw CNMRException(NMR_ERROR_INVALIDPOINTER);

				HRESULT hResult;

				CModelTexture2DResource * pTextureResource = getTexture2D();
				__NMRASSERT(pTextureResource);

				CComPtr<IStream> pMemoryStream = nullptr;
				hResult = CreateStreamOnHGlobal(nullptr, true, &pMemoryStream);
				if (hResult != S_OK)
					throw CNMRException_Windows(NMR_ERROR_COULDNOTCREATESTREAM, hResult);

				// Seek Stream
				LARGE_INTEGER nOriginPosition;
				ULARGE_INTEGER nNewPosition;
				nOriginPosition.HighPart = 0;
				nOriginPosition.LowPart = 0;
				hResult = pStream->Seek(nOriginPosition, STREAM_SEEK_END, &nNewPosition);
				if (hResult != S_OK)
					throw CNMRException_Windows(NMR_ERROR_COULDNOTSEEKSTREAM, hResult);

				nfUint64 cbStreamSize = nNewPosition.QuadPart;

				hResult = pStream->Seek(nOriginPosition, STREAM_SEEK_SET, &nNewPosition);
				if (hResult != S_OK)
					throw CNMRException_Windows(NMR_ERROR_COULDNOTSEEKSTREAM, hResult);

				std::array<nfByte, NMR_IMPORTSTREAM_COPYBUFFERSIZE> pBuffer;

				nfUint64 cbBytesLeft = cbStreamSize;
				while (cbBytesLeft > 0) {
					nfUint64 cbLength = cbBytesLeft;
					if (cbLength > NMR_IMPORTSTREAM_COPYBUFFERSIZE)
						cbLength = NMR_IMPORTSTREAM_COPYBUFFERSIZE;

					ULONG cbReadBytes = 0;
					ULONG cbWrittenBytes = 0;
					hResult = pStream->Read(&pBuffer[0], (nfUint32)cbLength, &cbReadBytes);
					if (hResult != S_OK)
						throw CNMRException_Windows(NMR_ERROR_COULDNOTREADSTREAM, hResult);

					if (cbReadBytes != cbLength)
						throw CNMRException(NMR_ERROR_COULDNOTREADFULLDATA);

					hResult = pMemoryStream->Write(&pBuffer[0], (nfUint32)cbLength, &cbWrittenBytes);
					if (hResult != S_OK)
						throw CNMRException_Windows(NMR_ERROR_COULDNOTWRITESTREAM, hResult);

					if (cbWrittenBytes != cbLength)
						throw CNMRException(NMR_ERROR_COULDNOTWRITEFULLDATA);
					cbBytesLeft -= cbLength;
				}


				PImportStream pImportStream = std::make_shared<CImportStream_COM>(pMemoryStream);

				CModel * pModel = pTextureResource->getModel();
				__NMRASSERT(pModel);

				pModel->removeTextureStream(pTextureResource->getPath());
				pModel->addTextureStream(pTextureResource->getPath(), pImportStream);

				return handleSuccess();
			}
			catch (CNMRException & Exception) {
				return handleNMRException(&Exception);
			}
			catch (...) {
				return handleGenericException();
			}

		}