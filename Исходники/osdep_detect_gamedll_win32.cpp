mBOOL DLLINTERNAL is_gamedll(const char *filename) {
	HANDLE hFile;
	HANDLE hMap;
	void * mapview;
	IMAGE_NT_HEADERS * ntheaders;
	IMAGE_SECTION_HEADER * sections;
	int num_sects;
	IMAGE_EXPORT_DIRECTORY * exports;

	int has_GiveFnptrsToDll = 0;
	int has_GetEntityAPI2 = 0;
	int has_GetEntityAPI = 0;

	// Try open file for read
	hFile = CreateFileA(filename, GENERIC_READ, FILE_SHARE_READ, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
	if(is_invalid_handle(hFile)) {
		META_DEBUG(3, ("is_gamedll(%s): CreateFile() failed.", filename));
		return(mFALSE);
	}
	
	//
	hMap = CreateFileMapping(hFile, NULL, PAGE_READONLY, 0, 0, NULL);
	if(is_invalid_handle(hMap)) {
		META_DEBUG(3, ("is_gamedll(%s): CreateFileMapping() failed.", filename));
		CloseHandle(hFile);
		return(mFALSE);
	}
	
	//
	mapview = MapViewOfFile(hMap, FILE_MAP_READ, 0, 0, 0);
	if(!mapview) {
		META_DEBUG(3, ("is_gamedll(%s): MapViewOfFile() failed.", filename));
		CloseHandle(hMap);
		CloseHandle(hFile);
		return(mFALSE);
	}
	
	ntheaders = get_ntheaders(mapview);
	if(!ntheaders) {
		META_DEBUG(3, ("is_gamedll(%s): get_ntheaders() failed.", filename));
		UnmapViewOfFile(mapview);
		CloseHandle(hMap);
		CloseHandle(hFile);
		return(mFALSE);
	}
	
	//Sections for va_to_mapaddr function
	sections = IMAGE_FIRST_SECTION(ntheaders);
	num_sects = ntheaders->FileHeader.NumberOfSections;
	if(IsBadReadPtr(sections, num_sects * sizeof(IMAGE_SECTION_HEADER))) {
		META_DEBUG(3, ("is_gamedll(%s): IMAGE_FIRST_SECTION() failed.", filename));
		UnmapViewOfFile(mapview);
		CloseHandle(hMap);
		CloseHandle(hFile);
		return(mFALSE);
	}
	
	//
	exports = get_export_table(mapview, ntheaders, sections, num_sects);
	if(!exports) {
		META_DEBUG(3, ("is_gamedll(%s): get_export_table() failed.", filename));
		UnmapViewOfFile(mapview);
		CloseHandle(hMap);
		CloseHandle(hFile);
		return(mFALSE);
	}
	
	//
	unsigned long * names = (unsigned long *)va_to_mapaddr(mapview, sections, num_sects, exports->AddressOfNames);
	if(IsBadReadPtr(names, exports->NumberOfNames * sizeof(unsigned long))) {
		META_DEBUG(3, ("is_gamedll(%s): Pointer to exported function names is invalid.", filename));
		UnmapViewOfFile(mapview);
		CloseHandle(hMap);
		CloseHandle(hFile);
		return(mFALSE);
	}
	
	for(unsigned int i = 0; i < exports->NumberOfNames; i++) {
		//get function name with valid address
		char * funcname = (char *)va_to_mapaddr(mapview, sections, num_sects, names[i]);
		if(IsBadStringPtrA(funcname, 128))
			continue;
		
		// Check
		// Fast check for 'G' first
		if(funcname[0] == 'G') {
			// Collect export information
			if(!has_GiveFnptrsToDll)
				has_GiveFnptrsToDll = strmatch(funcname, "GiveFnptrsToDll");
			if(!has_GetEntityAPI2)
				has_GetEntityAPI2   = strmatch(funcname, "GetEntityAPI2");
	  		if(!has_GetEntityAPI)
	  			has_GetEntityAPI    = strmatch(funcname, "GetEntityAPI");
	  	}
		// Check if metamod plugin
		else if(funcname[0] == 'M') {
			if(strmatch(funcname, "Meta_Init") || 
			   strmatch(funcname, "Meta_Query") || 
			   strmatch(funcname, "Meta_Attach") || 
			   strmatch(funcname, "Meta_Detach")) {
				// Metamod plugin.. is not gamedll
				META_DEBUG(5, ("is_gamedll(%s): Detected Metamod plugin, library exports [%s].", filename, funcname));
		   		
				UnmapViewOfFile(mapview);
				CloseHandle(hMap);
				CloseHandle(hFile);
				
				return(mFALSE);
			}
		}
	}
	
	UnmapViewOfFile(mapview);
	CloseHandle(hMap);
	CloseHandle(hFile);
	
	// Check if gamedll
	if(has_GiveFnptrsToDll && (has_GetEntityAPI2 || has_GetEntityAPI)) {
		// This is gamedll!
		META_DEBUG(5, ("is_gamedll(%s): Detected GameDLL.", filename));

		return(mTRUE);
	} else {
		META_DEBUG(5, ("is_gamedll(%s): Library isn't GameDLL.", filename));
		
		return(mFALSE);
	}
}