		AssertBehavior ReportFailure(const char* condition, const char* file, int line, const char* msg, ...)
		{
			const char* message = nullptr;
			if (msg != nullptr)
			{
				char messageBuffer[1024];
				{
					va_list args;
					va_start(args, msg);
					vsnprintf_s(messageBuffer, 1024, msg, args);
					va_end(args);
				}

				message = messageBuffer;
			}

			return DefaultAssertHandler(condition, message, file, line);
		}