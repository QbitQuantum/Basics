int32
BUnicodeChar::DigitValue(uint32 c)
{
	BUnicodeChar();
	return u_digit(c, 10);
}