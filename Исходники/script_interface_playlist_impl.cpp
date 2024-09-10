STDMETHODIMP FbPlaylistManager::AddLocations(UINT playlistIndex, VARIANT locations, VARIANT_BOOL select)
{
	TRACK_FUNCTION();
	
	bool toSelect = (select == VARIANT_TRUE);
	helpers::com_array_reader helper;

	if (!helper.convert(&locations)) return E_INVALIDARG;
	pfc::list_t<pfc::string8> locations2;

	for (long i = 0; i < static_cast<long>(helper.get_count()); ++i)
	{
		_variant_t varUrl;

		helper.get_item(i, varUrl);

		if (FAILED(VariantChangeType(&varUrl, &varUrl, 0, VT_BSTR))) return E_INVALIDARG;

		locations2.add_item(pfc::string8(pfc::stringcvt::string_utf8_from_wide(varUrl.bstrVal)));
	}

	pfc::list_const_array_t<const char*, pfc::list_t<pfc::string8> > locations3(locations2, locations2.get_count());

	static_api_ptr_t<playlist_incoming_item_filter_v2>()->process_locations_async(
		locations3,
		playlist_incoming_item_filter_v2::op_flag_background,
		NULL,
		NULL,
		NULL,
		new service_impl_t<js_process_locations>(playlistIndex, toSelect));

	return S_OK;
}