static char * hexdump8(char * out,unsigned address,const char * msg,int from,int to)
{
	unsigned max = (to-from)*16;
	if (!IsBadReadPtr((const void*)(address+(from*16)),max))
	{
		out += sprintf(out,"%s (%08Xh):",msg,address);
		unsigned n;
		const unsigned char * src = (const unsigned char*)(address)+(from*16);
		
		for(n=0;n<max;n++)
		{
			if (n%16==0)
			{
				out += sprintf(out,"\n%08Xh: ",src);
			}

			out += sprintf(out," %02X",*(src++));
		}
		*(out++) = '\n';
		*out=0;
	}
	return out;
}