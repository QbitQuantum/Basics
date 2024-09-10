s32 _sys_strcmp(vm::cptr<char> str1, vm::cptr<char> str2)
{
	sysPrxForUser.trace("_sys_strcmp(str1=*0x%x, str2=*0x%x)", str1, str2);

	return strcmp(str1.get_ptr(), str2.get_ptr());
}