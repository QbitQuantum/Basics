		AVSValue __cdecl CreateWritePipe(AVSValue args, void* user_data, IScriptEnvironment* env) {
			LPCSTR pipe_name = args[0].AsString();
			HANDLE hPipe = CreateNamedPipeA(pipe_name, PIPE_ACCESS_OUTBOUND,
				PIPE_TYPE_BYTE | PIPE_WAIT, 1, PIPE_BUFFER_SIZE, 0, NMPWAIT_USE_DEFAULT_WAIT, nullptr);
			if (hPipe == INVALID_HANDLE_VALUE)
				env->ThrowError("Error creating pipe with name \"%s\", code 0x%08X", pipe_name, GetLastError());
			return (int)hPipe;
		}