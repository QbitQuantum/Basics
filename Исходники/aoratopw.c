void retFromKadmin(_octet1 * data)
{
	WORD code;
	if(data->length >= 2)
	{
		if(code = _byteswap_ushort(*(PWORD) data->value))
			kprintf("%s (%u)", kull_m_kadmin_passwd_err_to_string(code), code);
		else kprintf("OK");
		if(data->length > 2)
		{
			kprintf(" - {");
			kull_m_string_printf_hex(data->value + 2, data->length - 2, 0);
			kprintf("}");
		}
		printf("\n");
	}
	else PRINT_ERROR("Size\n");
}