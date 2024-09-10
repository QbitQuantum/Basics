int inject_library_obf(HANDLE process, const wchar_t *dll,
		const char *create_remote_thread_obf, uint64_t obf1,
		const char *write_process_memory_obf, uint64_t obf2,
		const char *virtual_alloc_ex_obf,     uint64_t obf3,
		const char *virtual_free_ex_obf,      uint64_t obf4,
		const char *load_library_w_obf,       uint64_t obf5)
{
	int ret = INJECT_ERROR_UNLIKELY_FAIL;
	DWORD last_error = 0;
	bool success = false;
	size_t written_size;
	DWORD thread_id;
	HANDLE thread = NULL;
	size_t size;
	void *mem;

	/* -------------------------------- */

	HMODULE kernel32 = GetModuleHandleW(L"KERNEL32");
	create_remote_thread_t create_remote_thread;
	write_process_memory_t write_process_memory;
	virtual_alloc_ex_t virtual_alloc_ex;
	virtual_free_ex_t virtual_free_ex;
	FARPROC load_library_w;

	create_remote_thread = get_obfuscated_func(kernel32,
			create_remote_thread_obf, obf1);
	write_process_memory = get_obfuscated_func(kernel32,
			write_process_memory_obf, obf2);
	virtual_alloc_ex = get_obfuscated_func(kernel32,
			virtual_alloc_ex_obf, obf3);
	virtual_free_ex = get_obfuscated_func(kernel32,
			virtual_free_ex_obf, obf4);
	load_library_w = get_obfuscated_func(kernel32,
			load_library_w_obf, obf5);

	/* -------------------------------- */

	size = (wcslen(dll) + 1) * sizeof(wchar_t);
	mem = virtual_alloc_ex(process, NULL, size, MEM_RESERVE | MEM_COMMIT, PAGE_READWRITE);
	if (!mem) {
		goto fail;
	}

	success = write_process_memory(process, mem, dll,
			size, &written_size);
	if (!success) {
		goto fail;
	}

	thread = create_remote_thread(process, NULL, 0,
			(LPTHREAD_START_ROUTINE)load_library_w, mem, 0,
			&thread_id);
	if (!thread) {
		goto fail;
	}

	if (WaitForSingleObject(thread, 4000) == WAIT_OBJECT_0) {
		DWORD code;
		GetExitCodeThread(thread, &code);
		ret = (code != 0) ? 0 : INJECT_ERROR_INJECT_FAILED;

		SetLastError(0);
	}

fail:
	if (ret == INJECT_ERROR_UNLIKELY_FAIL) {
		last_error = GetLastError();
	}
	if (thread) {
		CloseHandle(thread);
	}
	if (mem) {
		virtual_free_ex(process, mem, 0, MEM_RELEASE);
	}
	if (last_error != 0) {
		SetLastError(last_error);
	}

	return ret;
}