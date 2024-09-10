ostream& operator <<(ostream&os, VLong&t)
{
    char buf[40];
	_i64toa(t,buf,10);
	return os<<buf;
}