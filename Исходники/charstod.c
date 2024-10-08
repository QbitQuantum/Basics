double
charstod(int(*f)(void*), void *vp)
{
	char str[400], *s, *e, *start;
	int c;

	s = str;
	e = str + sizeof str - 1;
	c = (*f)(vp);
	while(c == ' ' || c == '\t')
		c = (*f)(vp);
	if(c == '-' || c == '+'){
		ADVANCE;
	}
	start = s;
	while(c >= '0' && c <= '9'){
		ADVANCE;
	}
	if(c == '.'){
		ADVANCE;
		while(c >= '0' && c <= '9'){
			ADVANCE;
		}
	}
	if(s > start && (c == 'e' || c == 'E')){
		ADVANCE;
		if(c == '-' || c == '+'){
			ADVANCE;
		}
		while(c >= '0' && c <= '9'){
			ADVANCE;
		}
	}else if(s == start && (c == 'i' || c == 'I')){
		ADVANCE;
		if(c != 'n' && c != 'N')
			return NaN();
		ADVANCE;
		if(c != 'f' && c != 'F')
			return NaN();
		ADVANCE;
		if(c != 'i' && c != 'I')
			return NaN();
		ADVANCE;
		if(c != 'n' && c != 'N')
			return NaN();
		ADVANCE;
		if(c != 'i' && c != 'I')
			return NaN();
		ADVANCE;
		if(c != 't' && c != 'T')
			return NaN();
		ADVANCE;
		if(c != 'y' && c != 'Y')
			return NaN();
		ADVANCE;  /* so caller can back up uniformly */
		USED(c);
	}else if(s == str && (c == 'n' || c == 'N')){
		ADVANCE;
		if(c != 'a' && c != 'A')
			return NaN();
		ADVANCE;
		if(c != 'n' && c != 'N')
			return NaN();
		ADVANCE;  /* so caller can back up uniformly */
		USED(c);
	}
	*s = 0;
	return strtod(str, &s);
}