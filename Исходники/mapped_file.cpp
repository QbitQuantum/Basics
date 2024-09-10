        mapped_file::mapped_file(const string & fname, unsigned int io_open_mode, unsigned int create_size)
            : file_handle(0), map_handle(0), map_pointer(0)
        {
#ifdef WIN32
            string full_path = io::file::get_full_path(fname);

            // open file handle
            unsigned int win_open_mode = GENERIC_READ;

            if (io_open_mode & io::FILE_OPEN_WRITE)
                win_open_mode |= GENERIC_WRITE;

            if (file::exists(full_path))
            {
                file_handle = CreateFileW(full_path.w_string(), win_open_mode, 0, 0, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, 0);

                if (file_handle != INVALID_HANDLE_VALUE)
                    create_size = GetFileSize(file_handle, 0);
            }
            else
            {
                if (create_size == 0)
                    throw internal_exception(__FILE__, __LINE__, L"Must specify size for creating memory-mapped files.");

                file_handle = CreateFileW(full_path.w_string(), win_open_mode, 0, 0, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, 0);
                
                if (file_handle != INVALID_HANDLE_VALUE)
                {
                    unsigned char buf = 0;
                    unsigned int written;
                    SetFilePointer(file_handle, create_size-1, 0, FILE_BEGIN);                    
                    WriteFile(file_handle, &buf, 1, (LPDWORD) &written, 0);
                    SetFilePointer(file_handle, 0, 0, FILE_BEGIN);
                }
            }
            
            if (file_handle == INVALID_HANDLE_VALUE)
                throw io_exception(L"Unable to open %ls: %ls", full_path.w_string(), get_windows_error().w_string());

            // create mapping
            string map_name = string::format(L"periapsis_mapped_file_%d", NUM_MAPPED_FILES++);

            if (io_open_mode & io::FILE_OPEN_WRITE)
                win_open_mode = PAGE_READWRITE;
            else
                win_open_mode = PAGE_READONLY;

            map_handle = CreateFileMappingW(file_handle, 0, win_open_mode, 0, create_size, map_name.w_string());

            if (!map_handle)
                throw io_exception(L"Unable to create memory map for %ls: %ls", full_path.w_string(), get_windows_error().w_string());

            // map file
            if (io_open_mode & io::FILE_OPEN_WRITE)
                win_open_mode = FILE_MAP_ALL_ACCESS;
            else
                win_open_mode = FILE_MAP_READ;

            map_pointer = MapViewOfFile(map_handle, win_open_mode, 0, 0, 0);

            if (!map_pointer)
                throw io_exception(L"Unable to create memory map for %ls: %ls", full_path.w_string(), get_windows_error().w_string());

            map_size = create_size;
#else
#error Implement memory-mapped files!
#endif
        } // mapped_file::mapped_file()