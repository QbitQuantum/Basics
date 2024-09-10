#ifdef MCP_DEBUG
	fprintf(stderr, __FILE__ ": (samptomono)\n");
	fprintf(stderr, __FILE__ ": s->ptr=%p\n", s->ptr);
#endif
	s->type&=~mcpSampStereo;
	s->type|=mcpSampRedStereo;
	if (s->type&mcpSampFloat)
		for (i=0; i<l; i++)
			((float *)s->ptr)[i]=(((float *)s->ptr)[2*i]+((float *)s->ptr)[2*i+1])/2;
	else if (s->type&mcpSamp16Bit)
		for (i=0; i<l; i++)
			((int16_t *)s->ptr)[i]=(((int16_t *)s->ptr)[2*i]+((int16_t *)s->ptr)[2*i+1])>>1;
	else
		for (i=0; i<l; i++)
			((int8_t *)s->ptr)[i]=(((int8_t *)s->ptr)[2*i]+((int8_t *)s->ptr)[2*i+1])>>1;
	newptr=realloc(s->ptr,l<<sampsizefac(s->type));
#ifdef MCP_DEBUG
	fprintf(stderr, __FILE__ ": realloced buffer=%p\n", newptr);
#endif
	if (!newptr)
	{
		fprintf(stderr, __FILE__ " samptomono(): warning, realloc() failed\n"); /* safe to continue when buffer-shrink failes */
	} else
		s->ptr=newptr;
}


static int samptofloat(struct sampleinfo *s)
{
	int i;
	int l=s->length<<sampsizefac(s->type&mcpSampStereo);