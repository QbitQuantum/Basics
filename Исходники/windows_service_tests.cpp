				int check_run()
				{
					int install_res = check_install();
					if (install_res != 1)
						return install_res;

					int res = 0;
					SC_HANDLE sch_manager = NULL;
					SC_HANDLE sch_service = NULL;

					sch_manager = OpenSCManager(NULL, NULL, SC_MANAGER_ALL_ACCESS);
					if (sch_manager)
					{
						sch_service = OpenService(sch_manager, "win_srv_tests_helper", SERVICE_ALL_ACCESS);
						if (sch_service)
						{
							SERVICE_STATUS_PROCESS ssp_status;
							DWORD dw_temp;
							if (QueryServiceStatusEx(sch_service, SC_STATUS_PROCESS_INFO, 
								reinterpret_cast<LPBYTE> (&ssp_status), sizeof(SERVICE_STATUS_PROCESS),	&dw_temp ) == TRUE )
							{
								if (ssp_status.dwCurrentState == SERVICE_RUNNING)
									res = 1;
							}
							CloseServiceHandle(sch_service);
						}
						CloseServiceHandle(sch_manager);
					}
					else
					{
						res = -1;
						std::cout << "Error in open SCManager" << std::endl;
					}
					return res;
				 }