static void PutOctalString(Stream& out, const char *b, const char *e, bool split = false)
{
	out.Put('\"');
	int64 start = out.GetPos();
	while(b < e) {
		if(split && out.GetPos() >= start + 200u) {
			out.Put("\"\r\n\t\"");
			start = out.GetPos();
		}
		if((byte)*b >= ' ' && *b != '\x7F' && *b != '\xFF') {
			if(*b == '\\' || *b == '\"' || *b == '\'')
				out.Put('\\');
			out.Put(*b++);
		}
		else if(IsDigit(b[1]))
			out.Put(Sprintf("\\%03o", (byte)*b++));
		else
			out.Put(Sprintf("\\%o", (byte)*b++));
	}
	out.Put('\"');
}