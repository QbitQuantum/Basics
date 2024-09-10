void dmo_DMOGetName(REFGUID clsidCodec, wstring wstrName)
{
	HRESULT hr;
	WCHAR name[128];

	hr = DMOGetName(clsidCodec, name);
	BOOST_REQUIRE(hr == S_OK);
	BOOST_CHECK_EQUAL(wstring(name), wstrName);
}