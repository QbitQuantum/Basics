void WriteOutput(float Number) {
	char String[35];
	_gcvt(Number, 10, String);
	WriteUnicodeString(_totchar(String));
}