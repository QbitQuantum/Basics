/**@ingroup tsk_string_group
*/
int64_t tsk_atoll(const char* str)
{
	// FIXME: use HAVE_ATOLL and use macro instead of function
	if(str){
#if defined(_MSC_VER)
		return _atoi64(str);
#elif defined(__GNUC__)
		return atoll(str);
#else
		return atol(str); 
#endif
	}
	return 0;
}