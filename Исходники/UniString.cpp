OP_STATUS
UniString::AppendVFormat(const uni_char *format, va_list args)
{
	size_t buf_len = 0;
	uni_char *buf = GetAppendPtr_NoAlloc(buf_len);
	OP_ASSERT(buf_len <= Length()); // GetAppendPtr_NoAlloc() adds buf_len to Length()
	int result;

	// first, try to append without allocation
#ifdef va_copy // must use va_copy() in order to preserve args for reuse below
	va_list args_copy;
	va_copy(args_copy, args);
	result = uni_vsnprintf(buf, buf_len, format, args_copy);
	va_end(args_copy);
#else // va_copy
	result = uni_vsnprintf(buf, buf_len, format, args);
#endif // va_copy

	if (result < 0) // uni_vsnprintf() returned error
	{
		Trunc(Length() - buf_len);
		return OpStatus::ERR;
	}
	else if (static_cast<size_t>(result) >= buf_len)
	{
		// buf was too short, allocate to make enough room
		Trunc(Length() - buf_len);
		buf_len = result + 1;
		buf = GetAppendPtr(buf_len);
		RETURN_OOM_IF_NULL(buf);
		result = uni_vsnprintf(buf, buf_len, format, args);
	}
	OP_ASSERT(static_cast<size_t>(result) < buf_len);
	Trunc(Length() - (buf_len - result));
	return OpStatus::OK;
}