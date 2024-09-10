/** Implement the Lua function GetCurrentConfiguration().
 * 
 * Discover some details about the service's configuration as 
 * known to the \ref ssSCM and report them to the debug trace
 * while building a table from them to return.
 * 
 * \param L Lua state context for the function.
 * \returns The number of values on the Lua stack to be returned
 * to the Lua caller.
 */
static int dbgGetCurrentConfiguration(lua_State *L)
{
    SC_HANDLE schService;
    SC_HANDLE schManager;
    LPQUERY_SERVICE_CONFIG lpqscBuf;
    LPSERVICE_DESCRIPTION lpqscBuf2;
    DWORD dwBytesNeeded;
    const char *name;

    name = luaL_optstring(L, 1, ServiceName);
    SvcDebugTraceStr("Get service configuration for %s:\n", name);
    
    // Open a handle to the service. 
    schManager = OpenSCManagerA(NULL, NULL, (0
	    |GENERIC_READ
	    |SC_MANAGER_CONNECT
	    |SC_MANAGER_CREATE_SERVICE
	    |SC_MANAGER_ENUMERATE_SERVICE
    ));
    if (schManager == NULL)
	return luaL_error(L, "OpenSCManager failed (%d)", GetLastError());
    schService = OpenServiceA(schManager, // SCManager database 
	    name, // name of service 
	    SERVICE_QUERY_CONFIG); // need QUERY access 
    if (schService == NULL) {
	CloseServiceHandle(schManager);
	return luaL_error(L, "OpenService failed (%d)", GetLastError());
    }

    // Allocate buffers for the configuration information.
    lpqscBuf = (LPQUERY_SERVICE_CONFIG) LocalAlloc(
    LPTR, 8192);
    if (lpqscBuf == NULL) {
	CloseServiceHandle(schService);
	CloseServiceHandle(schManager);
	return luaL_error(L, "Can't allocate lpqscBuf");
    }
    lpqscBuf2 = (LPSERVICE_DESCRIPTION) LocalAlloc(
    LPTR, 8192);
    if (lpqscBuf2 == NULL) {
	LocalFree(lpqscBuf);
	CloseServiceHandle(schService);
	CloseServiceHandle(schManager);
	return luaL_error(L, "Can't allocate lpqscBuf2");
    }
    
    // Get the configuration information. 
    if (! QueryServiceConfig(
	    schService,
	    lpqscBuf,
	    8192,
	    &dwBytesNeeded)) {
	LocalFree(lpqscBuf);
	LocalFree(lpqscBuf2);
	CloseServiceHandle(schService);
	CloseServiceHandle(schManager);
	return luaL_error(L, "QueryServiceConfig failed (%d)",
		GetLastError());
    }
    if (! QueryServiceConfig2(
	    schService,
	    SERVICE_CONFIG_DESCRIPTION,
	    (LPBYTE)lpqscBuf2,
	    8192,
	    &dwBytesNeeded)) {
	LocalFree(lpqscBuf);
	LocalFree(lpqscBuf2);
	CloseServiceHandle(schService);
	CloseServiceHandle(schManager);
	return luaL_error(L, "QueryServiceConfig2 failed (%d)",
		GetLastError());
    }

    // Build a table of configuration details, 
    // passing them to the trace log along the way

    lua_newtable(L);
    fieldstr("name", name);
    fieldint("ServiceType", lpqscBuf->dwServiceType);
    fieldint("StartType", lpqscBuf->dwStartType);
    fieldint("ErrorControl", lpqscBuf->dwErrorControl);
    fieldstr("BinaryPathName", lpqscBuf->lpBinaryPathName);
    if (lpqscBuf->lpLoadOrderGroup != NULL)
	fieldstr("LoadOrderGroup", lpqscBuf->lpLoadOrderGroup);
    if (lpqscBuf->dwTagId != 0)
	fieldint("TagId", lpqscBuf->dwTagId);
    if (lpqscBuf->lpDependencies != NULL)
	fieldstr("Dependencies", lpqscBuf->lpDependencies);
    if (lpqscBuf->lpServiceStartName != NULL)
	fieldstr("ServiceStartName", lpqscBuf->lpServiceStartName);
    if (lpqscBuf2->lpDescription != NULL)
	fieldstr("Description", lpqscBuf2->lpDescription);
    
    LocalFree(lpqscBuf);
    LocalFree(lpqscBuf2);
    CloseServiceHandle(schService);
    CloseServiceHandle(schManager);
    return 1;
}