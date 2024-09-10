int cbf_swab(const void * src, void * dst, size_t len) 
{

#ifndef USE_SWAB
	unsigned char *p1;
	unsigned char *p2;
#endif
	
	if (len&1) return CBF_ARGUMENT;

#ifndef USE_SWAB
	p1 = (unsigned char *)src;
	p2 = (unsigned char *)dst;
	
	while (len) {
	  p2[1] = p1[0];
	  p2[0] = p1[1];
	  p1+=2; p2+=2;
	  len -=2;	
	}
#else
    swab(src,dst,len);
#endif
	
	return 0;

}