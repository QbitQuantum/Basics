TORRENT_EXPORT void print_backtrace(char* out, int len, int max_depth
	, void* ctx)
{
	CONTEXT context_record;
	if (ctx)
	{
		context_record = *static_cast<CONTEXT*>(ctx);
	}
	else
	{
		// use the current thread's context
		RtlCaptureContext(&context_record);
	}

	int size = 0;
	std::array<void*, 50> stack;

	STACKFRAME64 stack_frame;
	memset(&stack_frame, 0, sizeof(stack_frame));
#if defined(_WIN64)
	int const machine_type = IMAGE_FILE_MACHINE_AMD64;
	stack_frame.AddrPC.Offset = context_record.Rip;
	stack_frame.AddrFrame.Offset = context_record.Rbp;
	stack_frame.AddrStack.Offset = context_record.Rsp;
#else
	int const machine_type = IMAGE_FILE_MACHINE_I386;
	stack_frame.AddrPC.Offset = context_record.Eip;
	stack_frame.AddrFrame.Offset = context_record.Ebp;
	stack_frame.AddrStack.Offset = context_record.Esp;
#endif
	stack_frame.AddrPC.Mode = AddrModeFlat;
	stack_frame.AddrFrame.Mode = AddrModeFlat;
	stack_frame.AddrStack.Mode = AddrModeFlat;
	while (StackWalk64(machine_type,
		GetCurrentProcess(),
		GetCurrentThread(),
		&stack_frame,
		&context_record,
		nullptr,
		&SymFunctionTableAccess64,
		&SymGetModuleBase64,
		nullptr) && size < stack.size())
	{
		stack[size++] = reinterpret_cast<void*>(stack_frame.AddrPC.Offset);
	}

	struct symbol_bundle : SYMBOL_INFO
	{
		wchar_t name[MAX_SYM_NAME];
	};

	HANDLE p = GetCurrentProcess();
	static bool sym_initialized = false;
	if (!sym_initialized)
	{
		sym_initialized = true;
		SymInitialize(p, NULL, true);
	}
	SymRefreshModuleList(p);
	for (int i = 0; i < size && len > 0; ++i)
	{
		DWORD_PTR frame_ptr = reinterpret_cast<DWORD_PTR>(stack[i]);

		DWORD64 displacement = 0;
		symbol_bundle symbol;
		symbol.MaxNameLen = MAX_SYM_NAME;
		symbol.SizeOfStruct = sizeof(SYMBOL_INFO);
		BOOL const has_symbol = SymFromAddr(p, frame_ptr, &displacement, &symbol);

		DWORD line_displacement = 0;
		IMAGEHLP_LINE64 line = {};
		line.SizeOfStruct = sizeof(IMAGEHLP_LINE64);
		BOOL const has_line = SymGetLineFromAddr64(GetCurrentProcess(), frame_ptr,
			&line_displacement, &line);

		int ret = std::snprintf(out, len, "%2d: %p", i, stack[i]);
		out += ret; len -= ret; if (len <= 0) break;

		if (has_symbol)
		{
			ret = std::snprintf(out, len, " %s +%-4" PRId64
				, demangle(symbol.Name).c_str(), displacement);
			out += ret; len -= ret; if (len <= 0) break;
		}

		if (has_line)
		{
			ret = std::snprintf(out, len, " %s:%d"
				, line.FileName, line.LineNumber);
			out += ret; len -= ret; if (len <= 0) break;
		}


		ret = std::snprintf(out, len, "\n");
		out += ret;
		len -= ret;

		if (i == max_depth && max_depth > 0) break;
	}
}