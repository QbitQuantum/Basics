BOOL APIENTRY DllMain(HINSTANCE hInstDLL, DWORD fdwReason, LPVOID lpvReserved)
{
    switch (fdwReason)
    {
        case DLL_PROCESS_ATTACH:
			// get system path
			if (GetSystemDirectoryA(g_system32_path, MAX_PATH - 1))
			{
#ifdef WS2
				sprintf(g_wsock32orig_path, "%s\\ws2_32.dll", g_system32_path);
#else
				sprintf(g_wsock32orig_path, "%s\\wsock32.dll", g_system32_path);
#endif
			}
			// load original library
			if (!g_wsock32orig && strlen(g_wsock32orig_path))
			{
				g_wsock32orig = LoadLibraryA(g_wsock32orig_path);
			}
			// get functions addr
			if (g_wsock32orig)
			{
				for (size_t i = 0; i < F_COUNT; i++)
				{
					g_f_addr[i] = (void *)GetProcAddress(g_wsock32orig, g_f_name[i]);
				}
			} else
			{
				for (size_t i = 0; i < F_COUNT; i++)
				{
					g_f_addr[i] = NULL;
				}
			}
			if (GetModuleFileName(hInstDLL, g_ini_path, MAX_PATH - 1))
			{
				size_t ini_path_size = strlen(g_ini_path);
				while (ini_path_size >= 0)
				{
					if (g_ini_path[ini_path_size] == '\\')
					{
						ini_path_size++;
						break;
					}
					ini_path_size--;
				}
				g_ini_path[ini_path_size] = '\0';
				strcat(g_ini_path, "azimuth.conf");
			}
			if (GetModuleFileName(hInstDLL, g_hosts_path, MAX_PATH - 1))
			{
				size_t hosts_path_size = strlen(g_hosts_path);
				while (hosts_path_size >= 0)
				{
					if (g_hosts_path[hosts_path_size] == '\\')
					{
						hosts_path_size++;
						break;
					}
					hosts_path_size--;
				}
				g_hosts_path[hosts_path_size] = '\0';
				strcat(g_hosts_path, "hosts");
			}
			conf_init();
			hbn_init();
            break;

        case DLL_THREAD_ATTACH:
            break;

        case DLL_THREAD_DETACH:
            break;

        case DLL_PROCESS_DETACH:

			// free original library
			if (g_wsock32orig)
			{
				FreeLibrary(g_wsock32orig);
				g_wsock32orig = NULL;
			}
			hbn_deinit();
			conf_deinit();
            break;
    }
    return TRUE;
}