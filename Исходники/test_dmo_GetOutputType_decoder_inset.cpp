void dmo_GetOutputType_decoder_inset_(REFGUID clsidEnc, REFGUID clsidDec, REFGUID guidRaw, const vector<GUID> &expected)
{
	HRESULT hr;
	IMediaObject *pObj;
	vector<GUID> outTypes;
	DMO_MEDIA_TYPE mt;
	VIDEOINFOHEADER *pvih;

	DWORD fccIn = DirectShowFormatToVCMFormat(guidRaw);

	hr = CoCreateInstance(clsidEnc, NULL, CLSCTX_INPROC_SERVER, IID_IMediaObject, (LPVOID*)&pObj);
	BOOST_REQUIRE(hr == S_OK);
	BOOST_REQUIRE(pObj != NULL);

	memset(&mt, 0, sizeof(mt));
	MoInitMediaType(&mt, sizeof(VIDEOINFOHEADER));
	pvih = (VIDEOINFOHEADER*)mt.pbFormat;
	memset(pvih, 0, sizeof(VIDEOINFOHEADER));

	mt.majortype = MEDIATYPE_Video;
	mt.subtype = guidRaw;
	mt.bFixedSizeSamples = TRUE;
	mt.bTemporalCompression = FALSE;
	mt.lSampleSize = 10000000; /* XXX */
	mt.formattype = FORMAT_VideoInfo;
	pvih->bmiHeader.biSize = sizeof(BITMAPINFOHEADER);
	pvih->bmiHeader.biWidth = TEST_WIDTH;
	pvih->bmiHeader.biHeight = TEST_HEIGHT;
	pvih->bmiHeader.biPlanes = 1;
	pvih->bmiHeader.biBitCount = FCC2BitCount(fccIn);
	pvih->bmiHeader.biCompression = FCC2Compression(fccIn);
	pvih->bmiHeader.biSizeImage = 10000000; /* XXX */

	hr = pObj->SetInputType(0, &mt, 0);
	BOOST_REQUIRE(hr == S_OK);

	MoFreeMediaType(&mt);

	hr = pObj->GetOutputType(0, 0, &mt);
	BOOST_REQUIRE(hr == S_OK);

	pObj->Release();


	hr = CoCreateInstance(clsidDec, NULL, CLSCTX_INPROC_SERVER, IID_IMediaObject, (LPVOID*)&pObj);
	BOOST_REQUIRE(hr == S_OK);
	BOOST_REQUIRE(pObj != NULL);

	hr = pObj->SetInputType(0, &mt, 0);
	BOOST_REQUIRE(hr == S_OK);

	for (DWORD idx = 0; (hr = pObj->GetOutputType(0, idx, &mt)) == S_OK; ++idx)
	{
		BOOST_CHECK(mt.majortype == MEDIATYPE_Video);
		BOOST_CHECK(mt.bFixedSizeSamples == TRUE);
		BOOST_CHECK(mt.bTemporalCompression == FALSE);
		BOOST_CHECK(mt.formattype == FORMAT_VideoInfo);
		DWORD fccOut = DirectShowFormatToVCMFormat(mt.subtype);
		pvih = (VIDEOINFOHEADER*)mt.pbFormat;
		BOOST_CHECK(pvih->bmiHeader.biSize >= sizeof(BITMAPINFOHEADER));
		BOOST_CHECK(pvih->bmiHeader.biWidth == TEST_WIDTH);
		BOOST_CHECK(pvih->bmiHeader.biHeight == TEST_HEIGHT);
		BOOST_CHECK(pvih->bmiHeader.biPlanes == 1);
		BOOST_CHECK(pvih->bmiHeader.biBitCount == FCC2BitCount(fccOut));
		BOOST_CHECK(pvih->bmiHeader.biCompression == FCC2Compression(fccOut));
		outTypes.push_back(mt.subtype);
		MoFreeMediaType(&mt);
	}
	BOOST_CHECK(hr == DMO_E_NO_MORE_ITEMS);

	BOOST_CHECK_EQUAL(outTypes, expected);

	pObj->Release();
}