	service_info get_service_info(const std::string computer, const std::string service) {
		std::wstring comp = utf8::cvt<std::wstring>(computer);

		service_handle sc = OpenSCManager(comp.empty()?NULL:comp.c_str(),NULL,SC_MANAGER_ENUMERATE_SERVICE);
		if (!sc) 
			throw nscp_exception("Failed to open service manager: " + error::lookup::last_error());

		service_handle hService = OpenService(sc, utf8::cvt<std::wstring>(service).c_str(), SERVICE_QUERY_CONFIG|SERVICE_QUERY_STATUS );
		if (!hService)
			throw nscp_exception("Failed to open service: " + service);

		hlp::buffer<BYTE, SERVICE_STATUS_PROCESS*> ssp = queryServiceStatusEx(hService, service);

		service_info info(service, "TODO");
		info.pid = ssp.get()->dwProcessId;
		info.state = ssp.get()->dwCurrentState;
		info.type = ssp.get()->dwServiceType;

		DWORD bytesNeeded2 = 0;
		DWORD deErr = 0;
		if (QueryServiceConfig(hService, NULL, 0, &bytesNeeded2) || (deErr = GetLastError()) != ERROR_INSUFFICIENT_BUFFER)
			throw nscp_exception("Failed to open service " + info.name + ": " + error::lookup::last_error(deErr));
		hlp::buffer<BYTE> buf2(bytesNeeded2+10);

		if (!QueryServiceConfig(hService, reinterpret_cast<QUERY_SERVICE_CONFIG*>(buf2.get()), bytesNeeded2, &bytesNeeded2))
			throw nscp_exception("Failed to open service: " + info.name);
		QUERY_SERVICE_CONFIG *data2 = reinterpret_cast<QUERY_SERVICE_CONFIG*>(buf2.get());
		info.start_type = data2->dwStartType;
		info.binary_path = utf8::cvt<std::string>(data2->lpBinaryPathName);
		info.error_control = data2->dwErrorControl;
		return info;
	}