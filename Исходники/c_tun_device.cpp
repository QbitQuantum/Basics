NET_LUID c_tun_device_windows::get_luid(const std::wstring &human_name) {
	NET_LUID ret;
	NETIO_STATUS status = ConvertInterfaceAliasToLuid(human_name.c_str(), &ret);
	if (status != ERROR_SUCCESS) throw std::runtime_error("ConvertInterfaceAliasToLuid error, error code " + std::to_string(GetLastError()));
	return ret;
}