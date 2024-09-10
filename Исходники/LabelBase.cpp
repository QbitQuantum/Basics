int  ChooseAccessKey(const char *text, dword used)
{
	for(const char *s = text; *s; s++) {
		byte ac = *s;
		if(ac < 128 && ac >= 'A' && ac <= 'Z' && (Ctrl::AccessKeyBit(ac) & used) == 0)
			return MAKELONG(ac, s - text + 1);
	}
	for(const char *s = text; *s; s++) {
		byte ac = ToUpper(*s);
		if(ac < 128 && ac >= 'A' && ac <= 'Z' && ac != 'I' && ac != 'L' && (Ctrl::AccessKeyBit(ac) & used) == 0)
			return ac;
	}
	for(const char *s = text; *s; s++) {
		byte ac = ToUpper(*s);
		if(ac < 128 && ac >= 'A' && ac <= 'Z' && (Ctrl::AccessKeyBit(ac) & used) == 0)
			return ac;
	}
	return 0;
}