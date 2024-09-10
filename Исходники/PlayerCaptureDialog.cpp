static void SetupMediaTypes(IAMStreamConfig* pAMSC, CFormatArray<T>& tfa, CComboBox& type, CComboBox& dim, CMediaType& mt)
{
	tfa.RemoveAll();
	type.ResetContent();
	dim.ResetContent();
	type.EnableWindow(FALSE);
	dim.EnableWindow(FALSE);

	if (!pAMSC) {
		return;
	}

	AM_MEDIA_TYPE* pcurmt = NULL;
	pAMSC->GetFormat(&pcurmt);

	int iCount = 0, iSize;
	if (SUCCEEDED(pAMSC->GetNumberOfCapabilities(&iCount, &iSize))
			&& iSize == sizeof(T) && iCount > 0) {
		for (int i = 0; i < iCount; i++) {
			T caps;
			AM_MEDIA_TYPE* pmt = NULL;
			if (SUCCEEDED(pAMSC->GetStreamCaps(i, &pmt, (BYTE*)&caps))) {
				tfa.AddFormat(pmt, caps);
			}
		}

		if (iSize == sizeof(VIDEO_STREAM_CONFIG_CAPS)) {
			for (int i = 0, cnt = tfa.GetCount(); i < cnt; i++) {
				if (tfa[i]->GetCount() != 1) {
					continue;
				}

				CFormatElem<T>* pfe = tfa[i]->GetAt(0);

				if (pfe->mt.formattype != FORMAT_VideoInfo
						&& pfe->mt.formattype != FORMAT_VideoInfo2) {
					continue;
				}

				static SIZE presets[] = {
					{160, 120}, {192, 144},
					{320, 240}, {384, 288},
					{480, 240}, {512, 288},
					{480, 360}, {512, 384},
					{640, 240}, {768, 288},
					{640, 480}, {768, 576},
					{704, 240}, {704, 288},
					{704, 480}, {704, 576},
					{720, 240}, {720, 288},
					{720, 480}, {720, 576},
					{768, 240}, {768, 288},
					{768, 480}, {768, 576},
				};

				VIDEO_STREAM_CONFIG_CAPS* pcaps = (VIDEO_STREAM_CONFIG_CAPS*)&pfe->caps;
				BITMAPINFOHEADER bihCur;
				ExtractBIH(&pfe->mt, &bihCur);

				for (int j = 0; j < countof(presets); j++) {
					if (presets[j].cx == bihCur.biWidth
							&& presets[j].cy == abs(bihCur.biHeight)
							|| presets[j].cx < pcaps->MinOutputSize.cx
							|| presets[j].cx > pcaps->MaxOutputSize.cx
							|| presets[j].cy < pcaps->MinOutputSize.cy
							|| presets[j].cy > pcaps->MaxOutputSize.cy
							|| presets[j].cx % pcaps->OutputGranularityX
							|| presets[j].cy % pcaps->OutputGranularityY) {
						continue;
					}

					CMediaType mt = pfe->mt;

					if (mt.formattype == FORMAT_VideoInfo) {
						VIDEOINFOHEADER* vih = (VIDEOINFOHEADER*)mt.pbFormat;
						if (!vih->bmiHeader.biHeight) {
							vih->bmiHeader.biHeight = 1;
						}
						vih->bmiHeader.biWidth = presets[j].cx;
						vih->bmiHeader.biHeight = presets[j].cy*(vih->bmiHeader.biHeight/vih->bmiHeader.biHeight);
						vih->bmiHeader.biSizeImage = presets[j].cx*presets[j].cy*vih->bmiHeader.biBitCount>>3;

						AM_MEDIA_TYPE* pmt = (AM_MEDIA_TYPE*)CoTaskMemAlloc(sizeof(AM_MEDIA_TYPE));
						CopyMediaType(pmt, &mt);
						tfa.AddFormat(pmt, pcaps, sizeof(*pcaps));

						if (presets[j].cx*3 != presets[j].cy*4) {
							int extra = mt.cbFormat - sizeof(VIDEOINFOHEADER);
							int bmiHeaderSize = sizeof(vih->bmiHeader) + extra;
							BYTE* pbmiHeader = DNew BYTE[bmiHeaderSize];
							memcpy(pbmiHeader, &vih->bmiHeader, bmiHeaderSize);
							mt.ReallocFormatBuffer(FIELD_OFFSET(VIDEOINFOHEADER2, bmiHeader) + bmiHeaderSize);
							VIDEOINFOHEADER2* vih2 = (VIDEOINFOHEADER2*)mt.pbFormat;
							memcpy(&vih2->bmiHeader, pbmiHeader, bmiHeaderSize);
							delete [] pbmiHeader;
							vih2->dwInterlaceFlags = vih2->dwCopyProtectFlags = 0;
							vih2->dwReserved1 = vih2->dwReserved2 = 0;
							vih2->dwPictAspectRatioX = 4;
							vih2->dwPictAspectRatioY = 3;

							AM_MEDIA_TYPE* pmt = (AM_MEDIA_TYPE*)CoTaskMemAlloc(sizeof(AM_MEDIA_TYPE));
							CopyMediaType(pmt, &mt);
							tfa.AddFormat(pmt, pcaps, sizeof(*pcaps));
						}
					} else if (mt.formattype == FORMAT_VideoInfo2) {
						VIDEOINFOHEADER2* vih2 = (VIDEOINFOHEADER2*)mt.pbFormat;
						if (!vih2->bmiHeader.biHeight) {
							vih2->bmiHeader.biHeight = 1;
						}
						vih2->bmiHeader.biWidth = presets[j].cx;
						vih2->bmiHeader.biHeight = presets[j].cy*(vih2->bmiHeader.biHeight/vih2->bmiHeader.biHeight);
						vih2->bmiHeader.biSizeImage = presets[j].cx*presets[j].cy*vih2->bmiHeader.biBitCount>>3;
						vih2->dwPictAspectRatioX = 4;
						vih2->dwPictAspectRatioY = 3;

						AM_MEDIA_TYPE* pmt = (AM_MEDIA_TYPE*)CoTaskMemAlloc(sizeof(AM_MEDIA_TYPE));
						CopyMediaType(pmt, &mt);
						tfa.AddFormat(pmt, pcaps, sizeof(*pcaps));
					}
				}
			}