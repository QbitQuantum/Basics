bool z_convert(const double &val,z_string &t,ctext format)
{
    char buff[20];
    _gcvt(val,4,buff);
	t=buff;
	return true;
}