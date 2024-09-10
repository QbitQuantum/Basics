	void 
	trace_message(
		__in trace_level level,
		__in const char *format,
		...
		)
	{
		char *message_buf;
		size_t message_len;
		va_list message_args;
		std::stringstream stream;

		if(level <= SHOW_TRACE_LEVEL) {
			va_start(message_args, format);

			message_len = _vscprintf(format, message_args) + 1;
			if(message_len) {
			
				message_buf = new char[message_len];
				if(message_buf) {
					
					//if(vsprintf_s(message_buf, message_len, format, message_args) 
					if(vsprintf(message_buf, format, message_args) 
							== (int)(message_len - 1)) {
						stream << message_buf << std::endl;
					}

					delete[] message_buf;
					message_buf = NULL;
				}
			}

			va_end(message_args);
#ifdef _WIN32
			OutputDebugString(stream.str().c_str());
#else
			std::cout << stream.str();
#endif // _WIN32
		}
	}