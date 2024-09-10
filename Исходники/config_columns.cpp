void double_to_string(double blah, pfc::string_base & p_out, int points = 10, bool ms = true)
{
	int decimal, sign;
	pfc::array_t<char> buffer;
	buffer.set_size(_CVTBUFSIZE);
	buffer.fill_null();
	_fcvt_s(buffer.get_ptr(), buffer.get_size(), blah*(ms ? 1000.0 : 1.0), points, &decimal, &sign);
	const char * ptr = buffer.get_ptr();
	if (decimal <= 0)
	{
		p_out.add_string("0.",2);
		while (decimal) 
		{
			p_out.add_byte('0');
			decimal ++;
		}
		p_out.add_string(ptr, pfc_infinite);
	}
	else
	{
		p_out.add_string(ptr, decimal);
		p_out.add_string(".",1);
		ptr += decimal;
		p_out.add_string(ptr,pfc_infinite);
	}
}