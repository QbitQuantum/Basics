//-----------------------------------------------------------------------------
static void load_paths_to_watch(LPCTSTR path, HANDLE completion_port_h) {
//-----------------------------------------------------------------------------
    FILE * stream_p;
    wchar_t *get_result;
    HANDLE create_result;
    size_t line_len;
    struct watch_entry **link_p;
    struct watch_entry * next_p;

    if (_wfopen_s(&stream_p, path, L"r, ccs=UTF-8")) {
        _wfopen_s(&error_file, error_path, L"w");
        _wcserror_s(error_buffer, ARRAYSIZE(error_buffer), errno); 
        fwprintf(
            error_file, 
            L"_wfopen(%s) failed: (%d) %s\n",  
            path,
            errno,
            error_buffer 
        );
        fclose(error_file);
        ExitProcess(2);
    }

    link_p = &watch_entry_list_p;
   
    while (1) {

        // create a watch entry
        next_p = (struct watch_entry *) HeapAlloc(
            GetProcessHeap(), HEAP_ZERO_MEMORY, sizeof(struct watch_entry)
        );
		if (next_p == NULL){
			report_error(L"HeapAlloc failed to allocate memory", GetLastError());
			ExitProcess(200);
			}
        // read in the path to watch from config.txt
        get_result = \
            fgetws(full_file_name, ARRAYSIZE(full_file_name), stream_p);

        if (NULL == get_result) {
            if (0 == ferror(stream_p)) {
                HeapFree(GetProcessHeap(), 0, next_p);
                break;
            } 
            _wfopen_s(&error_file, error_path, L"w");
            _wcserror_s(
               error_buffer, sizeof error_buffer/sizeof(wchar_t) , errno
            ); 
            fwprintf(
                error_file, 
                L"fgetws(%s) failed: (%d) %s\n",  
                path,
                errno,
                error_buffer 
            );
            fclose(error_file);
            ExitProcess(2);
        }

        // clean out the newline, if there is one
        line_len = wcslen(full_file_name);
		if (line_len && full_file_name[line_len-1] == L'\n'){
			full_file_name[line_len-1] = L'\0';
			line_len--;
			}
        if (full_file_name[0] == L'\0')
           continue;
		next_p->dir_path_len = line_len;
		next_p->dir_path = (wchar_t *)HeapAlloc(GetProcessHeap(), HEAP_ZERO_MEMORY,
			(line_len + 1) * sizeof(wchar_t));
		if (next_p->dir_path == NULL){
			report_error(L"HeapAlloc failed to allocate memory", GetLastError());
			ExitProcess(201);
		}
		wcsncpy_s(next_p->dir_path, line_len+1, full_file_name, line_len);
		next_p->changes_buffer = (BYTE *)HeapAlloc(GetProcessHeap(), HEAP_ZERO_MEMORY,
			CHANGES_BUFFER_SIZE);
		if (next_p->changes_buffer == NULL){
			report_error(L"HeapAlloc failed to allocate memory", GetLastError());
			ExitProcess(202);
		}
        // 2020-09-05 dougfort -- we don't clean out trailing slash here
        // because if they are backing up something like c:\\, we need
        // the trailing slash. This will come back to bite us when we are
        // checking for excludes

        // open a file handle to watch the directory in overlapped mode
        next_p->hDirectory = CreateFile(
            next_p->dir_path,
            FILE_LIST_DIRECTORY,
            FILE_SHARE_READ | FILE_SHARE_WRITE | FILE_SHARE_DELETE,
            NULL,
            OPEN_EXISTING,
            FILE_FLAG_BACKUP_SEMANTICS | FILE_FLAG_OVERLAPPED,
            NULL
        );

        // 2009-03-11 dougfort -- if we can't create this file, 
        // assume it is a top-level directory
        // which no longer exists; so ignore it and move on.
        if (INVALID_HANDLE_VALUE == next_p->hDirectory) {
            report_error(L"CreateFile", GetLastError());
            continue;
        }

        // add this file handle to the IO Complete port
        create_result = CreateIoCompletionPort(
            next_p->hDirectory,         // FileHandle,
            completion_port_h,          // ExistingCompletionPort,
            0,                          // CompletionKey,
            0                           // NumberOfConcurrentThreads
        );

        if (NULL == create_result) {
            report_error(L"CreateIOCompletionPort (add)", GetLastError());
            ExitProcess(102);
        }

        if (create_result != completion_port_h) {
            ExitProcess(103);
        }

        start_watch(next_p);

        // add this entry to the list
        *link_p = next_p;

        // point to the new entry's next pointer 
        link_p = &(*link_p)->next_p;
    } // while(1)

    fclose(stream_p);

} // load_paths_to_watch