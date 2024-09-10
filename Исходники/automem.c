int automem_append_field_ulong(automem_t* pmem, const char * field, unsigned int f_len, unsigned long val)
{
	char intVal[32];int slen;

	automem_append_voidp(pmem, field, f_len);
	_ultoa(val, intVal,10);
	slen = strlen(intVal);

	automem_ensure_newspace(pmem, slen + 4);
	pmem->pdata[pmem->size++]='=';
	pmem->pdata[pmem->size++]='"';
	automem_append_voidp(pmem, intVal, slen);
	pmem->pdata[pmem->size++]='"';
	pmem->pdata[pmem->size++]=' ';

	return pmem->size;
}