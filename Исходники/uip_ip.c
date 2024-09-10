s32_t uip_ipaton(const u8_t *cp,struct in_addr *addr)
{
	u32_t val;
	u8_t c;
	u32_t parts[4];
	u32_t *pp = parts;
	int base,n;

	c = *cp;
	for(;;) {
		if(!isdigit(c)) return 0;
		
		val = 0; base = 10;
		if(c=='0') {
			c = *++cp;
			if(c=='x' || c=='X')
				base = 16, c = *++cp;
			else
				base = 8;
		}
		for(;;) {
			if(isdigit(c)) {
				val = (val*base)+(int)(c-'0');
				c = *++cp;
			} else if(base==16 && isxdigit(c)) {
				val = (val<<4)|(int)(c+10-(islower(c)?'a':'A'));
				c = *++cp;
			} else 
				break;
		}
		if(c=='.') {
			if(pp>=parts+3) return 0;
			*pp++ = val;
			c = *++cp;
		} else
			break;
	}

	if(c!='\0' && (!isascii(c) || isspace(c))) return 0;

	n = pp-parts+1;
	switch(n) {
		case 0:
			return 0;
		case 1:
			break;
		case 2:
			if(val>0x00ffffff) return 0;

			val |= (parts[0]<<24);
			break;
		case 3:
			if(val>0x0000ffff) return 0;

			val |= (parts[0]<<24)|(parts[1]<<16);
			break;
		case 4:
			if(val>0x000000ff) return 0;

			val |= (parts[0]<<24)|(parts[1]<<16)|(parts[2]<<8);
			break;
	}
	if(addr)
		addr->s_addr = htonl(val);

	return 1;
}