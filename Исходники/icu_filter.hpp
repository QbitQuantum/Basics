    bool filter(const char_type*& src_begin, const char_type* src_end,
		char_type*& dest_begin, char_type* dest_end,
		bool flush)
    {
      if (! ucnv_from && ! ucnv_to) {
	// no converter... simply copy!
	
	const size_t copy_size = std::min(src_end - src_begin, dest_end - dest_begin);
	
	std::copy(src_begin, src_begin + copy_size, dest_begin);
	
	src_begin += copy_size;
	dest_begin += copy_size;
	
	return false;
      }

      UChar* pivot_end = pivot_start + boost::iostreams::default_device_buffer_size;
      
      UErrorCode status = U_ZERO_ERROR;
      
      if (pivot_target != pivot_end) {
	const char_type* src_begin_prev = src_begin;
	UChar* pivot_target_prev = pivot_target;
	
	status = U_ZERO_ERROR;
	ucnv_toUnicode(ucnv_from, &pivot_target, pivot_end, &src_begin, src_end, 0, flush, &status);
	
	offset_from += src_begin - src_begin_prev;
	offset_pivot_target += pivot_target - pivot_target_prev;
	
	if (status != U_BUFFER_OVERFLOW_ERROR && U_FAILURE(status)) {
	  UErrorCode status_getname = U_ZERO_ERROR;
	  const char* encoding = ucnv_getName(ucnv_from, &status_getname);
	  
	  std::ostringstream offset_stream;
	  offset_stream << offset_from;

	  std::ostringstream offset_stream_unicode;
	  offset_stream_unicode << offset_pivot_target;
	  
	  message_from = (std::string("ucnv_toUnicode(): ") + u_errorName(status)
			  + " from " + encoding
			  + " offset: " + offset_stream.str()
			  + " unicode offset: " + offset_stream_unicode.str());
	  throw BOOST_IOSTREAMS_FAILURE(message_from);
	}
      }
      
      char_type*   dest_begin_prev = dest_begin;
      const UChar* pivot_source_prev = pivot_source;
      
      status = U_ZERO_ERROR;
      ucnv_fromUnicode(ucnv_to, &dest_begin, dest_end, &pivot_source, pivot_target, 0, flush, &status);
      
      offset_to += dest_begin - dest_begin_prev;
      offset_pivot_source += pivot_source - pivot_source_prev;
      
      if (status != U_BUFFER_OVERFLOW_ERROR && U_FAILURE(status)) {
	UErrorCode status_getname = U_ZERO_ERROR;
	const char* encoding = ucnv_getName(ucnv_to, &status_getname);
	
	std::ostringstream offset_stream;
	offset_stream << offset_to;
	
	std::ostringstream offset_stream_unicode;
	offset_stream_unicode << offset_pivot_source;
	
	message_to = (std::string("ucnv_fromUnicode(): ") + u_errorName(status) 
		      + " to " + encoding
		      + " offset: " + offset_stream.str()
		      + " unicode offset: " + offset_stream_unicode.str());
	throw BOOST_IOSTREAMS_FAILURE(message_to);
      }
      
      if (pivot_source == pivot_target) {
	pivot_source = pivot_start;
	pivot_target = pivot_start;
      }
      
      return status == U_BUFFER_OVERFLOW_ERROR;
    }