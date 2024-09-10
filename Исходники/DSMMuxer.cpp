void CDSMMuxerFilter::MuxHeader(IBitStream* pBS)
{
	CString muxer;
	muxer.Format(_T("DSM Muxer (%s)"), CString(__TIMESTAMP__));

	SetProperty(L"MUXR", CStringW(muxer));
	SetProperty(L"DATE", CStringW(CTime::GetCurrentTime().FormatGmt(_T("%Y-%m-%d %H:%M:%S"))));

	MuxFileInfo(pBS);

	POSITION pos = m_pPins.GetHeadPosition();
	while(pos)
	{
		CBaseMuxerInputPin* pPin = m_pPins.GetNext(pos);
		const CMediaType& mt = pPin->CurrentMediaType();

		ASSERT((mt.lSampleSize >> 30) == 0); // you don't need >1GB samples, do you?

		MuxPacketHeader(pBS, DSMP_MEDIATYPE, 5 + sizeof(GUID)*3 + mt.FormatLength());
		pBS->BitWrite(pPin->GetID(), 8);
		pBS->ByteWrite(&mt.majortype, sizeof(mt.majortype));
		pBS->ByteWrite(&mt.subtype, sizeof(mt.subtype));
		pBS->BitWrite(mt.bFixedSizeSamples, 1);
		pBS->BitWrite(mt.bTemporalCompression, 1);
		pBS->BitWrite(mt.lSampleSize, 30);
		pBS->ByteWrite(&mt.formattype, sizeof(mt.formattype));
		pBS->ByteWrite(mt.Format(), mt.FormatLength());
		
		MuxStreamInfo(pBS, pPin);
	}

	// resources & chapters

	CInterfaceList<IDSMResourceBag> pRBs;
	pRBs.AddTail(this);

	CComQIPtr<IDSMChapterBag> pCB = (IUnknown*)(INonDelegatingUnknown*)this;

	pos = m_pPins.GetHeadPosition();
	while(pos)
	{
		for(CComPtr<IPin> pPin = m_pPins.GetNext(pos)->GetConnected(); pPin; pPin = GetUpStreamPin(GetFilterFromPin(pPin)))
		{
			if(m_fAutoRes)
			{
				CComQIPtr<IDSMResourceBag> pPB = GetFilterFromPin(pPin);
				if(pPB && !pRBs.Find(pPB)) pRBs.AddTail(pPB);
			}

			if(m_fAutoChap)
			{
				if(!pCB || pCB->ChapGetCount() == 0) pCB = GetFilterFromPin(pPin);				
			}
		}
	}

	// resources

	pos = pRBs.GetHeadPosition();
	while(pos)
	{
		IDSMResourceBag* pRB = pRBs.GetNext(pos);

		for(DWORD i = 0, j = pRB->ResGetCount(); i < j; i++)
		{
			CComBSTR name, desc, mime;
			BYTE* pData = NULL;
			DWORD len = 0;
			if(SUCCEEDED(pRB->ResGet(i, &name, &desc, &mime, &pData, &len, NULL)))
			{
				CStringA utf8_name = UTF16To8(name);
				CStringA utf8_desc = UTF16To8(desc);
				CStringA utf8_mime = UTF16To8(mime);

				MuxPacketHeader(pBS, DSMP_RESOURCE, 
					1 + 
					utf8_name.GetLength()+1 + 
					utf8_desc.GetLength()+1 + 
					utf8_mime.GetLength()+1 + 
					len);

				pBS->BitWrite(0, 2);
				pBS->BitWrite(0, 6); // reserved
				pBS->ByteWrite(utf8_name, utf8_name.GetLength()+1);
				pBS->ByteWrite(utf8_desc, utf8_desc.GetLength()+1);
				pBS->ByteWrite(utf8_mime, utf8_mime.GetLength()+1);
				pBS->ByteWrite(pData, len);

				CoTaskMemFree(pData);
			}
		}
	}

	// chapters

	if(pCB)
	{
		CAtlList<CDSMChapter> chapters;
		REFERENCE_TIME rtPrev = 0;
		int len = 0;

		pCB->ChapSort();

		for(DWORD i = 0; i < pCB->ChapGetCount(); i++)
		{
			CDSMChapter c;
			CComBSTR name;
			if(SUCCEEDED(pCB->ChapGet(i, &c.rt, &name)))
			{
				REFERENCE_TIME rtDiff = c.rt - rtPrev; rtPrev = c.rt; c.rt = rtDiff;
				c.name = name;
				len += 1 + GetByteLength(myabs(c.rt)) + UTF16To8(c.name).GetLength()+1;
				chapters.AddTail(c);
			}
		}

		if(chapters.GetCount())
		{
			MuxPacketHeader(pBS, DSMP_CHAPTERS, len);

			pos = chapters.GetHeadPosition();
			while(pos)
			{
				CDSMChapter& c = chapters.GetNext(pos);
				CStringA name = UTF16To8(c.name);
				int irt = GetByteLength(myabs(c.rt));
				pBS->BitWrite(c.rt < 0, 1);
				pBS->BitWrite(irt, 3);
				pBS->BitWrite(0, 4);
				pBS->BitWrite(myabs(c.rt), irt<<3);
				pBS->ByteWrite((LPCSTR)name, name.GetLength()+1);
			}
		}
	}
}