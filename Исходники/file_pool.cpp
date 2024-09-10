	void set_low_priority(file_handle const& f)
	{
		// file prio is only supported on vista and up
		// so load the functions dynamically
		typedef enum _FILE_INFO_BY_HANDLE_CLASS {
			FileBasicInfo,
			FileStandardInfo,
			FileNameInfo,
			FileRenameInfo,
			FileDispositionInfo,
			FileAllocationInfo,
			FileEndOfFileInfo,
			FileStreamInfo,
			FileCompressionInfo,
			FileAttributeTagInfo,
			FileIdBothDirectoryInfo,
			FileIdBothDirectoryRestartInfo,
			FileIoPriorityHintInfo,
			FileRemoteProtocolInfo,
			MaximumFileInfoByHandleClass
		} FILE_INFO_BY_HANDLE_CLASS, *PFILE_INFO_BY_HANDLE_CLASS;

		typedef enum _PRIORITY_HINT {
			IoPriorityHintVeryLow = 0,
			IoPriorityHintLow,
			IoPriorityHintNormal,
			MaximumIoPriorityHintType
		} PRIORITY_HINT;

		typedef struct _FILE_IO_PRIORITY_HINT_INFO {
			PRIORITY_HINT PriorityHint;
		} FILE_IO_PRIORITY_HINT_INFO, *PFILE_IO_PRIORITY_HINT_INFO;

		typedef BOOL (WINAPI *SetFileInformationByHandle_t)(HANDLE hFile, FILE_INFO_BY_HANDLE_CLASS FileInformationClass, LPVOID lpFileInformation, DWORD dwBufferSize);
		static SetFileInformationByHandle_t SetFileInformationByHandle = NULL;

		static bool failed_kernel_load = false;

		if (failed_kernel_load) return;

		if (SetFileInformationByHandle == NULL)
		{
			HMODULE kernel32 = LoadLibraryA("kernel32.dll");
			if (kernel32 == NULL)
			{
				failed_kernel_load = true;
				return;
			}

			SetFileInformationByHandle = (SetFileInformationByHandle_t)GetProcAddress(kernel32, "SetFileInformationByHandle");
			if (SetFileInformationByHandle == NULL)
			{
				failed_kernel_load = true;
				return;
			}
		}

		TORRENT_ASSERT(SetFileInformationByHandle);

		FILE_IO_PRIORITY_HINT_INFO io_hint;
		io_hint.PriorityHint = IoPriorityHintLow;
		SetFileInformationByHandle(f->native_handle(),
			FileIoPriorityHintInfo, &io_hint, sizeof(io_hint));
	}