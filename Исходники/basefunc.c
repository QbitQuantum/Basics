static __inline__ int comp_name(void * src,void * desc)
{
	return Strncmp(src,desc,DIGEST_SIZE);
}