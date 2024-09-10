void AllocRegistry::dump(const char *path) {
#ifdef WIN32
	FILE* f= _wfopen(utf8_decode(path).c_str(), L"wt");
#else
	FILE *f= fopen(path, "wt");
#endif
	int leakCount=0;
	size_t leakBytes=0;

	time_t debugTime = time(NULL);
    struct tm *loctime = localtime (&debugTime);
    char szBuf2[100]="";
    strftime(szBuf2,100,"%Y-%m-%d %H:%M:%S",loctime);

	fprintf(f, "Memory leak dump at: %s\n\n",szBuf2);

	for(int i=0; i<maxAllocs; ++i){
		AllocInfo &info = allocs[i];
		if(info.freetouse == false && info.inuse == true) {

			if(info.line > 0) {
				leakBytes += info.bytes;

				//allocs[i].stack = AllocInfo::getStackTrace();
				fprintf(f, "Leak #%d.\tfile: %s, line: %d, ptr [%p], bytes: " MG_SIZE_T_SPECIFIER ", array: %d, inuse: %d\n%s\n", ++leakCount, info.file, info.line, info.ptr, info.bytes, info.array,info.inuse,info.stack.c_str());
			}
		}
	}

	fprintf(f, "\nTotal leaks: %d, " MG_SIZE_T_SPECIFIER " bytes\n", leakCount, leakBytes);
	fprintf(f, "Total allocations: %d, " MG_SIZE_T_SPECIFIER " bytes\n", allocCount, allocBytes);
	fprintf(f, "Not monitored allocations: %d, " MG_SIZE_T_SPECIFIER " bytes\n", nonMonitoredCount, nonMonitoredBytes);

	fclose(f);

	printf("Memory leak dump summary at: %s\n",szBuf2);
	printf("Total leaks: %d, " MG_SIZE_T_SPECIFIER " bytes\n", leakCount, leakBytes);
	printf("Total allocations: %d, " MG_SIZE_T_SPECIFIER " bytes\n", allocCount, allocBytes);
	printf("Not monitored allocations: %d, " MG_SIZE_T_SPECIFIER " bytes\n", nonMonitoredCount, nonMonitoredBytes);
}