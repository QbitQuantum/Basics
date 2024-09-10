/*
 * .KB_C_FN_DEFINITION_START
 * void DebugPrintHex(int, int)
 *  This global function displays the value with the number of digits specified.
 * .KB_C_FN_DEFINITION_END
 */
void DebugPrintHex(int digits, int value) {

	char	dValue[11], *cPtr;
	int	nextDigit;

	if ((digits < 1) || (digits > 8)) return ;

	cPtr = &dValue[10];
	*cPtr-- = 0;
	while (digits--) {
		nextDigit = 0xF & value;
		*cPtr-- = ToASCII(nextDigit);
		value >>= 4;
	}
	*cPtr-- = 'x';
	*cPtr = '0';
	DebugPrint(cPtr);
}