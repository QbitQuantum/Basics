BOOST_DATA_TEST_CASE(dmo_NotImpl_encoder_IAMVfwCompressDialogs, data::make(vecCodecFcc), fcc)
{
	DMOEncoderCLSID clsid(fcc);

	HRESULT hr;
	IAMVfwCompressDialogs *pDlg;

	hr = CoCreateInstance(clsid, NULL, CLSCTX_INPROC_SERVER, IID_IAMVfwCompressDialogs, (LPVOID*)&pDlg);
	BOOST_REQUIRE(hr == S_OK);
	BOOST_REQUIRE(pDlg != NULL);

	hr = pDlg->SendDriverMessage(0, 0, 0);
	BOOST_CHECK(hr == E_NOTIMPL);

	pDlg->Release();
}