void GetSourceFileInfo(DWORD64 dw64Address, FILE * fw) {
    IMAGEHLP_LINE64 il64LineInfo;
	memset(&il64LineInfo, 0, sizeof(IMAGEHLP_LINE64));
	il64LineInfo.SizeOfStruct = sizeof(IMAGEHLP_LINE64);

    DWORD dwDisplacement = 0;

	if(SymGetLineFromAddr64(GetCurrentProcess(), dw64Address, &dwDisplacement, &il64LineInfo) == TRUE) {
        // We have sourcefile and linenumber info, write it.
        fprintf(fw, "%s(%d): ", il64LineInfo.FileName, il64LineInfo.LineNumber);
	} else {
        // We don't have sourcefile and linenumber info, let's try module name

        IMAGEHLP_MODULE64 im64ModuleInfo;
        memset(&im64ModuleInfo, 0, sizeof(IMAGEHLP_MODULE64));
        im64ModuleInfo.SizeOfStruct = sizeof(IMAGEHLP_MODULE64);

        if(SymGetModuleInfo64(GetCurrentProcess(), dw64Address, &im64ModuleInfo)) {
            // We found module name, write module name and address
            fprintf(fw, "%s|0x%08I64X: ", im64ModuleInfo.ModuleName, dw64Address);
        } else {
            // We don't found module. Write address, it's better than nothing
            fprintf(fw, "0x%08I64X: ", dw64Address);
        }
	}
}