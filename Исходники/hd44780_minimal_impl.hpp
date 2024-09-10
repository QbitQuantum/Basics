void
xpcc::Hd44780Minimal<E, RW, RS, DATA>::write(char c)
{
	if (c == '\n')
	{
		line++;
		if (line >= lineCount) {
			line = 0;
		}
		column = 0;
		setCursor(line, column);
	}
	else {
		if (column >= lineWidth) {
			write('\n');
		}
		writeRaw(c);
		column++;
	}
}