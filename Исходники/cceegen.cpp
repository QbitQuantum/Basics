HRESULT CCeeGen::emitMetaData(IMetaDataEmit *emitter, CeeSection* section, DWORD offset, BYTE* buffer, unsigned buffLen)
{
	HRESULT hr;

	if (! m_fTokenMapSupported) {
		IUnknown *pMapTokenIface;
		hr = getMapTokenIface(&pMapTokenIface, emitter);
		_ASSERTE(SUCCEEDED(hr));

	// Set a callback for token remap and save the tokens which change.
		hr = emitter->SetHandler(pMapTokenIface);
		_ASSERTE(SUCCEEDED(hr));
	}

    // generate the metadata
    IStream *metaStream;
    int rc = CreateStreamOnHGlobal(NULL, TRUE, &metaStream);
    _ASSERTE(rc == S_OK);

    hr = emitter->SaveToStream(metaStream, 0);
    _ASSERTE(SUCCEEDED(hr));

    // get size of stream and get sufficient storage for it

	if (section == 0) {
		section = &getMetaSection();
		STATSTG statStg;
		rc = metaStream->Stat(&statStg, STATFLAG_NONAME);       
		_ASSERTE(rc == S_OK);

		buffLen = statStg.cbSize.u.LowPart;
		if(m_objSwitch)
		{
			CeeSection* pSect;
			DWORD flags = IMAGE_SCN_LNK_INFO | IMAGE_SCN_LNK_REMOVE | IMAGE_SCN_ALIGN_1BYTES; // 0x00100A00
			hr = getSectionCreate(".cormeta",flags,&pSect,&m_metaIdx);
		}
		buffer = (BYTE *)section->getBlock(buffLen, sizeof(DWORD));
		TESTANDRETURN(buffer, E_OUTOFMEMORY);

		offset = getMetaSection().dataLen() - buffLen;
	}

	// reset seek pointer and read from stream
    LARGE_INTEGER disp = { {0, 0} };
	rc = metaStream->Seek(disp, STREAM_SEEK_SET, NULL);
	_ASSERTE(rc == S_OK);
	ULONG metaDataLen;
	rc = metaStream->Read(buffer, buffLen+1, &metaDataLen);	// +1 so assert below will fire.
	_ASSERTE(metaDataLen <= buffLen);
	metaStream->Release();

	if (! m_fTokenMapSupported) {
		// Remove the handler that we set
		hr = emitter->SetHandler(NULL);
		TESTANDRETURNHR(hr);
	}

    // Set meta virtual address to offset of metadata within .meta, and 
    // and add a reloc for this offset, which will get turned 
    // into an rva when the pewriter writes out the file. 

    m_corHeader->MetaData.VirtualAddress = VAL32(offset);
    getCorHeaderSection().addSectReloc(m_corHeaderOffset + offsetof(IMAGE_COR20_HEADER, MetaData), *section, srRelocAbsolute);
    m_corHeader->MetaData.Size = VAL32(metaDataLen);
    
    return S_OK;
}