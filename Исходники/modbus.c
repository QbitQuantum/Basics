float mb_read_float(const unsigned char *buf)
{
	if(!buf) return(nanf(""));
	// Convert MODBus float (see 2.11.1) into native single-precision float
	/* You are not expected to understand this */
	bool s=buf[2]&0x80;
	int8_t e=(((buf[2]&0x7f)<<1)|((buf[3]>>7)&1))-127;
	uint32_t m=(1<<23)|((buf[3]&0x7f)<<16)|(buf[0]<<8)|buf[1];
	float f=ldexpf(m, e-23);
	return(copysignf(f, s?-1:1));
}