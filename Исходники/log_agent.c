/**  
 * @brief output(unicode)
 * @param [in] p_agent, agent
 * @param [in] level, log level
 * @param [in] p_src_file, src file that call this func
 * @param [in] src_line, src line that call this func
 * @param [in] p_format, format string
 * @param [in] var_str, var string
 * @return
 * 0: success
 * other: fail
 */
static inline int32 log_agent_outputW(LOG_AGENT* p_agent, uint32 level, wchar_t* p_src_file, int32 src_line, wchar_t* p_format, va_list var_str)
{
	//int8*  p_int8 = NULL;
	wchar_t*  p_char = NULL;
	int32  buf_left_size;
	int32  char_buf_left_size;
	int32  total_str_size;


	SYSTEMTIME sys_time;
	struct tm  now_time;
	uint32 proc_id;
	uint32 thread_id;

	LARGE_INTEGER seek_pos;
	int64  file_pos;

	int64  now;
	int32  left_value;
	int32  b_need_open;
	uint32 write_size;
	int32  ret;

	_time64(&now);
	ret = _localtime64_s(&now_time, &now);
	GetLocalTime(&sys_time);
	proc_id = GetCurrentProcessId();
	thread_id = GetCurrentThreadId();

	EnterCriticalSection(&p_agent->cs);

	p_agent->now_time_year = sys_time.wYear;
	p_agent->now_time_month = sys_time.wMonth;
	p_agent->now_time_day = sys_time.wDay;
	p_agent->now_time_hour = sys_time.wHour;

	p_char = (wchar_t*)p_agent->str_buf;
	buf_left_size = LA_MAX_LOG_STRING_SIZE;
	char_buf_left_size = buf_left_size / sizeof(wchar_t);
	total_str_size = 0;

	switch( level )
	{
	case LA_LOG_LEVEL_FATAL:
		{
			if( p_agent->level & LA_LOG_LEVEL_FATAL )
			{
				ret = swprintf_s(p_char, char_buf_left_size, L"[Fatal]");

				p_char += ret;
				char_buf_left_size -= ret;
				buf_left_size -= (ret * sizeof(wchar_t));
				total_str_size += ret;

			}else
			{
				goto FIN;
			}
		}
		break;

	case LA_LOG_LEVEL_ERROR:
		{
			if( p_agent->level & LA_LOG_LEVEL_ERROR )
			{
				ret = swprintf_s(p_char, char_buf_left_size, L"[Error]");

				p_char += ret;
				char_buf_left_size -= ret;
				buf_left_size -= (ret * sizeof(wchar_t));
				total_str_size += ret;

			}else
			{
				goto FIN;
			}
		}
		break;

	case LA_LOG_LEVEL_WARN:
		{
			if( p_agent->level & LA_LOG_LEVEL_WARN )
			{
				ret = swprintf_s(p_char, char_buf_left_size, L"[Warn]");

				p_char += ret;
				char_buf_left_size -= ret;
				buf_left_size -= (ret * sizeof(wchar_t));
				total_str_size += ret;

			}else
			{
				goto FIN;
			}
		}
		break;

	case LA_LOG_LEVEL_INFO:
		{
			if( p_agent->level & LA_LOG_LEVEL_INFO )
			{
				ret = swprintf_s(p_char, char_buf_left_size, L"[Info]");

				p_char += ret;
				char_buf_left_size -= ret;
				buf_left_size -= (ret * sizeof(wchar_t));
				total_str_size += ret;

			}else
			{
				goto FIN;
			}
		}
		break;

	case LA_LOG_LEVEL_DEBUG:
		{
			if( p_agent->level & LA_LOG_LEVEL_DEBUG )
			{
				ret = swprintf_s(p_char, char_buf_left_size, L"[Debug]");

				p_char += ret;
				char_buf_left_size -= ret;
				buf_left_size -= (ret * sizeof(wchar_t));
				total_str_size += ret;

			}else
			{
				goto FIN;
			}
		}
		break;

	case LA_LOG_LEVEL_ACCESS:
		{
			if( p_agent->level & LA_LOG_LEVEL_ACCESS )
			{
				ret = swprintf_s(p_char, char_buf_left_size, L"[Access]");

				p_char += ret;
				char_buf_left_size -= ret;
				buf_left_size -= (ret * sizeof(wchar_t));
				total_str_size += ret;

			}else
			{
				goto FIN;
			}
		}
		break;

	default:
		{
			goto FIN;
		}
	}

	ret = swprintf_s(p_char, char_buf_left_size, L"[%04d-%02d-%02d %02d:%02d:%02d %03d][%s:%d][%u:%u] ",
		sys_time.wYear, sys_time.wMonth, sys_time.wDay, sys_time.wHour, sys_time.wMinute, sys_time.wSecond, sys_time.wMilliseconds,
		p_src_file, src_line, proc_id, thread_id);

	p_char += ret;
	char_buf_left_size -= ret;
	buf_left_size -= (ret * sizeof(wchar_t));
	total_str_size += ret;

	ret = vswprintf_s(p_char, char_buf_left_size, p_format, var_str);

	if( ret < 0 )
	{
		goto FIN;
	}

	p_char += ret;
	char_buf_left_size -= ret;
	buf_left_size -= (ret * sizeof(wchar_t));
	total_str_size += ret;

	p_agent->str_buf_size = total_str_size * sizeof(wchar_t);
	p_char = (wchar_t*)p_agent->str_buf;
	p_char[total_str_size] = 0x0;

	/** output to stdout */
	if( p_agent->type & LA_LOG_TYPE_STDOUT )
	{
		//OutputDebugStringW((wchar_t*)p_agent->str_buf);
	}

	/** output to file */
	if( p_agent->type & LA_LOG_TYPE_FILE )
	{
		b_need_open = 0;

		if( p_agent->h != INVALID_HANDLE_VALUE )
		{
			/** already open */
			if( p_agent->split_file_rule == LA_SPLIT_FILE_BY_TIME )
			{
				if( now >= p_agent->next_split_time )
				{
					CloseHandle(p_agent->h);
					p_agent->h = INVALID_HANDLE_VALUE;

					p_agent->split_file_seq++;
					p_agent->next_split_time += p_agent->split_time;
					b_need_open = 1;
				}

			}else
			{
			}

		}else
		{
			/** not open */
			if( p_agent->split_time < 60 )
			{
				/** split < 1 minute */
				p_agent->split_file_seq = sys_time.wSecond / p_agent->split_time;
				left_value = sys_time.wSecond % p_agent->split_time;
				p_agent->next_split_time = now - left_value + p_agent->split_time;

			}else if( p_agent->split_time < (60 * 60) )
			{
				/** split < 1 hour */
				p_agent->split_file_seq = (sys_time.wMinute * 60 + sys_time.wSecond) / p_agent->split_time;
				left_value = (sys_time.wMinute * 60 + sys_time.wSecond) % p_agent->split_time;
				p_agent->next_split_time = now - left_value + p_agent->split_time;

			}else
			{
				/** split >= 1 hour */
				p_agent->split_file_seq = (sys_time.wHour * 60 * 60 + sys_time.wMinute * 60 + sys_time.wSecond) / p_agent->split_time;
				left_value = (sys_time.wHour * 60 * 60 + sys_time.wMinute * 60 + sys_time.wSecond) % p_agent->split_time;
				p_agent->next_split_time = now - left_value + p_agent->split_time;
			}

			b_need_open = 1;
		}

		if( b_need_open )
		{
			/** open file */
			ret = log_agent_open_fileW(p_agent);
			if( ret )
			{
				goto FIN;
			}

			seek_pos.QuadPart = 0;
			ret = SetFilePointerEx(p_agent->h, seek_pos, (LARGE_INTEGER*)&file_pos, FILE_END);
		}

		ret = WriteFile(p_agent->h, p_agent->str_buf, p_agent->str_buf_size, (DWORD*)&write_size, NULL);
	}

	/** output to sock */
	if( p_agent->type & LA_LOG_TYPE_SOCK )
	{
#if LA_ENABLE_NETWORK

		if( p_agent->sock == -1 )
		{
			ret = log_agent_open_sock(p_agent);
			if( ret )
			{
				goto FIN;
			}
		}

		ret = log_agent_sendto_sock(p_agent, p_agent->str_buf, p_agent->str_buf_size);

#endif
	}

FIN:

	LeaveCriticalSection(&p_agent->cs);

	return GEN_S_OK;
}