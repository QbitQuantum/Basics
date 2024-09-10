std::vector<ComPtr<IShellItem>> get_shell_items(IDataObject* object) {
	auto format = FORMATETC{CF_HDROP, nullptr, DVASPECT_CONTENT, -1, TYMED_HGLOBAL};
	STGMEDIUM stgm;
	if (FAILED(object->GetData(&format, &stgm)))
		return {};

	auto hdrop = reinterpret_cast<HDROP>(stgm.hGlobal);
	auto n_paths = DragQueryFile(hdrop, 0xffffffff, nullptr, 0);

	std::vector<ComPtr<IShellItem>> items;
	for (UINT i = 0; i < n_paths; i++) {
		auto buffer_size = er = DragQueryFile(hdrop, i, nullptr, 0);
		std::vector<wchar_t> buffer(buffer_size + 1);
		buffer[buffer_size] = L'\0';
		er = DragQueryFile(hdrop, i, buffer.data(), numeric_cast<UINT>(buffer.size()));

		ComPtr<IShellItem> si;
		er = SHCreateItemFromParsingName(
			buffer.data(), nullptr, IID_IShellItem, reinterpret_cast<void**>(&si));
		items.push_back(si);
	}
	ReleaseStgMedium(&stgm);

	return items;
}