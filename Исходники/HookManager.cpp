BOOL HookManager::DoHook(int hookingMethod)
{
	HMODULE hModule;
	PROC OrigAddrFunc;
	if(hookingMethod==Hook_Specified_Module){
		for(int i=0;i< MyHookedAPIList->g_Counter;i++)
		{
			if(strcmp(MyHookedAPIList->GetModuleName(i),"")==0)
			{
				OutputDebugStringA("Module Not Found!");
				return FALSE;
			}
			hModule=LoadLibraryA(MyHookedAPIList->GetModuleName(i));
			//Also Hook EAT function for yet-to-load DLL if functions , that are going
			//to be hooked , are exported.
			OrigAddrFunc=HookExportTable(MyHookedAPIList->GetDLLName(i),
										 MyHookedAPIList->GetOrigAddressOfFunc(i),
										 MyHookedAPIList->GetNewAddressOfFunc(i));
			OrigAddrFunc=HookInOneModule(hModule,
										 MyHookedAPIList->GetDLLName(i),
										 MyHookedAPIList->GetOrigAddressOfFunc(i),
										 MyHookedAPIList->GetNewAddressOfFunc(i));
		
			MyHookedAPIList->SetHookedStatus(i);
		}
	}
	//If all modules are to be hooked , HookInAllModule should be defined 
	else if(hookingMethod==Hook_All_Module) {
		HMODULE hMyDll1=LoadLibraryA("H2.dll");
		HMODULE hMyDll2=LoadLibraryA("Forwarder.dll");
		HANDLE snap= CreateToolhelp32Snapshot(TH32CS_SNAPMODULE,GetCurrentProcessId());
		MODULEENTRY32 mod;
		mod.dwSize=sizeof(MODULEENTRY32);
		
		for(int i=0;i<MyHookedAPIList->g_Counter;i++)
		{
			//Also Hook EAT function for yet-to-load DLL if functions , that are going
			//to be hooked , are exported.
			OrigAddrFunc=HookExportTable(MyHookedAPIList->GetDLLName(i),
										 MyHookedAPIList->GetOrigAddressOfFunc(i),
										 MyHookedAPIList->GetNewAddressOfFunc(i));
			Module32First(snap,&mod);
			HMODULE first=mod.hModule;
			OrigAddrFunc=HookInOneModule(first,
										 MyHookedAPIList->GetDLLName(i),
										 MyHookedAPIList->GetOrigAddressOfFunc(i),
										 MyHookedAPIList->GetNewAddressOfFunc(i));
			while(Module32Next(snap,&mod))
			{
				HMODULE next=mod.hModule;
				if(next==hMyDll1||next==hMyDll2) continue; // Do not hook injected DLL
				OrigAddrFunc=HookInOneModule(next,
											 MyHookedAPIList->GetDLLName(i),
											 MyHookedAPIList->GetOrigAddressOfFunc(i),
											 MyHookedAPIList->GetNewAddressOfFunc(i));
			}
			MyHookedAPIList->SetHookedStatus(i);
		}
	}
	return TRUE;
}