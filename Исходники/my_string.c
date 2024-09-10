size_t my_string_set(my_string_t *obj, const char* str)
{
	size_t len = my_strlen(str);

	PTR_CHECK_RETURN(obj, "my_string", 0);

	if ((len+1) > obj->mem_size)
	{
		_clear(obj);
		_expand(obj, len*2);
	}

	_set(obj, str);

	signal_emit(obj->update_signal);

	return obj->str_len;
}