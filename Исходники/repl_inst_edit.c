void	mupcli_edit_offset_size_value(sm_uc_ptr_t buff, uint4 offset, uint4 size, gtm_uint64_t value, boolean_t value_present)
{
	char		temp_str[256], temp_str1[256];
	gtm_uint64_t	old_value;

	memset(temp_str, 0, 256);
	memset(temp_str1, 0, 256);
	if (sizeof(char) == size)
	{
		SPRINTF(temp_str, "!UB [0x!XB]");
		old_value = *(sm_uc_ptr_t)buff;
	}
	else if (sizeof(short) == size)
	{
		SPRINTF(temp_str, "!UW [0x!XW]");
		old_value = *(sm_ushort_ptr_t)buff;
	}
	else if (sizeof(int4) == size)
	{
		SPRINTF(temp_str, "!UL [0x!XL]");
		old_value = *(sm_uint_ptr_t)buff;
	}
	else if (sizeof(gtm_int64_t) == size)
	{
		SPRINTF(temp_str, "!@UQ [0x!@XQ]");
		old_value = *(qw_num_ptr_t)buff;
	}
	if (value_present)
	{
		if (sizeof(char) == size)
			*(sm_uc_ptr_t)buff = (unsigned char)value;
		else if (sizeof(short) == size)
			*(sm_ushort_ptr_t)buff = (unsigned short)value;
		else if (sizeof(int4) == size)
			*(sm_uint_ptr_t)buff = (unsigned int)value;
		else if (sizeof(gtm_int64_t) == size)
			*(qw_num_ptr_t)buff = value;
	} else
		value = old_value;
	SPRINTF(temp_str1, "Offset !UL [0x!XL] : Old Value = %s : New Value = %s : Size = !UB [0x!XB]",
		temp_str, temp_str);
	if (sizeof(int4) >= size)
		util_out_print(temp_str1, TRUE, offset, offset, (uint4)old_value, (uint4)old_value,
			(uint4)value, (uint4)value, size, size);
	else
		util_out_print(temp_str1, TRUE, offset, offset, &old_value, &old_value,
			&value, &value, size, size);
}