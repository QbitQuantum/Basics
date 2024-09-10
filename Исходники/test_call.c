int wmain(int argc, wchar_t * argv[])
{
	RPC_BINDING_HANDLE hBinding;
	wchar_t dataIn[] = L"a cleartext message!";
	PVOID pDataOut, pDataOut2;
	DWORD dwDataOut, dwDataOut2;

	if(argc > 1)
	{
		wprintf(L"Will use \'%s\' for DC name...\n", argv[1]);
		if(kull_m_rpc_createBinding(L"ncacn_np", argv[1], L"\\pipe\\protected_storage", L"ProtectedStorage", RPC_C_IMP_LEVEL_IMPERSONATE, &hBinding, NULL))
		{
			wprintf(L"\n* Retrieve RSA Public Key\n");
			if(kull_m_rpc_bkrp_generic(&hBinding, &BACKUPKEY_RETRIEVE_BACKUP_KEY_GUID, (PVOID) 0xbadc00fe, 0, &pDataOut, &dwDataOut)) // don't ask me why dummy data is needed here (not used).
			{
				wprintf(L"  > pDataOut @ 0x%p (%u)\n", pDataOut, dwDataOut);
				//printHex(pDataOut, dwDataOut);
				MIDL_user_free(pDataOut);
			}

			wprintf(L"\n* Backup a secret (%s)\n", dataIn);
			if(kull_m_rpc_bkrp_generic(&hBinding, &BACKUPKEY_BACKUP_GUID, &dataIn, sizeof(dataIn), &pDataOut, &dwDataOut))
			{
				wprintf(L"  > pDataOut @ 0x%p (%u)\n", pDataOut, dwDataOut);
				printHex(pDataOut, dwDataOut);

				wprintf(L"\n* Restore a secret\n");
				if(kull_m_rpc_bkrp_generic(&hBinding, &BACKUPKEY_RESTORE_GUID, pDataOut, dwDataOut, &pDataOut2, &dwDataOut2))
				{
					wprintf(L"  > pDataOut2 @ 0x%p (%u)\n", pDataOut, dwDataOut);
					wprintf(L"  > Secret : %s\n", pDataOut2);
					MIDL_user_free(pDataOut2);
				}
				MIDL_user_free(pDataOut);
			}

			kull_m_rpc_deleteBinding(&hBinding);
		}
	}
	else wprintf(L"[ERROR] A DC name is needed in argument\n");
	return ERROR_SUCCESS;
}