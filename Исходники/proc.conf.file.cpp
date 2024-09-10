int assign_ulonglong(void* value_ptr, const char* value_string)
{
	int i_ret = APP_SUCCESS;
	char tmp_value[MAX_STRING_SIZE] = {0};

	strcpy_s(tmp_value, MAX_STRING_SIZE - 1, value_string);
//	StrTrimA(tmp_value, " 	");

	*((__int64*)value_ptr) = _atoi64(tmp_value);
	return i_ret;
}