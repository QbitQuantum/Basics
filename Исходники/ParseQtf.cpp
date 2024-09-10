void RichQtfParser::Cat(int chr)
{
	if(accesskey && ToUpper(ToAscii(chr)) == LOBYTE(accesskey)) {
		Flush();
		format.Underline(!format.IsUnderline());
		text.Cat(chr);
		Flush();
		format.Underline(!format.IsUnderline());
		accesskey = 0;
	}
	else if(chr >= ' ') {
		text.Cat(chr);
	}
}