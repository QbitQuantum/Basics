 template<class msg_type> void operator()(msg_type & msg) const {
     char_type buffer[64];
     ::time_t t = ::time (nullptr);
     ::tm t_details = m_localtime ? *localtime( &t) : *gmtime( &t);
 #ifdef HPX_LOG_USE_WCHAR_T
     if (0 != wcsftime (buffer, sizeof (buffer), m_format.c_str (), &t_details))
 #else
     if (0 != strftime (buffer, sizeof (buffer), m_format.c_str (), &t_details))
 #endif
         convert::write(buffer, msg);
 }