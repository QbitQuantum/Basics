	void console_appender::append_color_by_priority( const logging_event& event )
	{
		//Prepare the color
#if defined(WIN32) || defined(WIN64)
		static WORD 	attributes[] = {
			0
			,defualt_attributes_//TRACE
			,FOREGROUND_RED | FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_INTENSITY//DEBUG
			,FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_INTENSITY//INFO
			,FOREGROUND_GREEN | FOREGROUND_RED | FOREGROUND_INTENSITY//WARN
			,FOREGROUND_RED | FOREGROUND_INTENSITY//ERROR
			,FOREGROUND_RED | FOREGROUND_INTENSITY | FOREGROUND_BLUE //FATAL
		};
#else
		static const char*	color_codes[] = {
			""
			,""//TRACE
			,"\033[1;37m"//DEBUG
			,"\033[1;36m"//INFO
			,"\033[1;33m"//WARN
			,"\033[1;31m"//ERROR
			,"\033[1;35m"//FATAL
		};
#endif
#if defined(WIN32) || defined(WIN64)
		SetConsoleTextAttribute(out_handle_, attributes[event.get_priority()/10000]);
		if ( utf8_ )
		{
			wchar_t wbuf[LOGGING_MAX_MESSAGE_SIZE];
			char	buf[LOGGING_MAX_MESSAGE_SIZE*4];
			int len = MultiByteToWideChar( CP_UTF8, 0, event.get_message().c_str(), event.get_message().length(),wbuf,sizeof(wbuf) );
			len = WideCharToMultiByte( GetOEMCP(),0,wbuf,len,buf,sizeof(buf),NULL,NULL );
			buf[len] = 0;
			const_cast<logging_event&>(event).get_message().assign( buf, len );
		}
#else
		(*stream_) << color_codes[event.get_priority()/10000];
#endif
		_get_layout().format(event,*stream_);
#if defined(WIN32) || defined(WIN64)
		stream_->flush();
		SetConsoleTextAttribute(out_handle_, defualt_attributes_);
		stream_->flush();
#else
		*stream_ << "\033[0m";
		stream_->flush();
#endif
	}