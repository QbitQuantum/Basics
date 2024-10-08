int serviceControl::main(int argc, wchar_t* argv[])
{
    if (argc < 3) throw std::runtime_error("At least 3 arguments are required for SC!");
    if (boost::algorithm::iequals(argv[1], L"create"))
    {
        if (argc < 6) return 1;
        DWORD serviceType;
        if (swscanf_s(argv[4], L"%u", &serviceType) != 1) return 1;
        DWORD startType;
        if (swscanf_s(argv[5], L"%u", &startType) != 1) return 1;
        SC_HANDLE hSCM = OpenSCManager(NULL, NULL, SC_MANAGER_CREATE_SERVICE | SC_MANAGER_CONNECT | STANDARD_RIGHTS_EXECUTE);
        SC_HANDLE createdService = ::CreateServiceW(
                                       hSCM,
                                       argv[2],
                                       argc >= 6 ? argv[6] : NULL,
                                       SC_MANAGER_ALL_ACCESS,
                                       serviceType,
                                       startType,
                                       SERVICE_ERROR_IGNORE,
                                       argv[3],
                                       NULL,
                                       NULL,
                                       NULL,
                                       NULL,
                                       NULL);
        CloseServiceHandle(createdService);
        CloseServiceHandle(hSCM);
        return 0;
    } else if (boost::algorithm::iequals(argv[1], L"delete"))
    {
        SC_HANDLE hSCM = OpenSCManager(NULL, NULL, SC_MANAGER_CONNECT | STANDARD_RIGHTS_EXECUTE);
        SC_HANDLE openedService = OpenService(hSCM, argv[2], DELETE | SERVICE_CHANGE_CONFIG);
        DeleteService(openedService);
        CloseServiceHandle(openedService);
        CloseServiceHandle(hSCM);
    } else if (boost::algorithm::iequals(argv[1], L"stop"))
    {
        SC_HANDLE hSCM = OpenSCManager(NULL, NULL, SC_MANAGER_CONNECT | STANDARD_RIGHTS_EXECUTE);
        SC_HANDLE openedService = OpenService(hSCM, argv[2], SERVICE_STOP);
        SERVICE_STATUS crap;
        ControlService(openedService, SERVICE_CONTROL_STOP, &crap);
        CloseServiceHandle(openedService);
        CloseServiceHandle(hSCM);
    } else if (boost::algorithm::iequals(argv[1], L"start"))
    {
        SC_HANDLE hSCM = OpenSCManager(NULL, NULL, SC_MANAGER_CONNECT | STANDARD_RIGHTS_EXECUTE);
        SC_HANDLE openedService = OpenService(hSCM, argv[2], SERVICE_START);
        StartService(openedService, NULL, NULL);
        CloseServiceHandle(openedService);
        CloseServiceHandle(hSCM);
    }
    return 0;
}