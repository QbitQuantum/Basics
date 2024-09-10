		static void safe_debugstr(int max_size, const char* lpformat, ...)
		{
			do 
			{
				string l_out_debug;
				l_out_debug.resize(max_size + 1);
				va_list l_va_list;
				va_start(l_va_list, lpformat);
				StringCchVPrintfA((char*)l_out_debug.c_str(), max_size + 1, lpformat, l_va_list);
				va_end(l_va_list);
				l_out_debug.resize(strlen(l_out_debug.c_str()));
	
				out_msg_base::showmsg(l_out_debug);
	
			} while (false);
		}