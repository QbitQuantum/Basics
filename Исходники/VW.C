int	dochunk(FILE *f1)
{
	unsigned u;
	int	a,b,c;
	long	chunkstart;
	chunkstart=ftell(f1);
	fread(&chunkheader,sizeof(chunkheader),1,f1);
	switch(chunkheader.type)
	{
		case 11 : /* FLI_COLOR */
			c=getw(f1);
			a=0;
			while(c--)
			{
				a+=getc(f1);
				b=getc(f1); if(!b) b=256;
				outp(0x3c8,a);
				while(b--)
				{
					outp(0x3c9,getc(f1));
					outp(0x3c9,getc(f1));
					outp(0x3c9,getc(f1));
				}
			}
			break;
		case 12 : /* FLI_LC */
			u=getw(f1)*lw;
			c=getw(f1);
			while(c--)
			{
				doline1(u,f1);
				u+=lw;
			}
			break;
		case 13 : /* FLI_BLACK */
			memset(vram,0,64000U);
			break;
		case 15 : /* FLI_BRUN */
			u=0;
			c=200;
			while(c--)
			{
				doline2(u,f1);
				u+=lw;
			}
			break;
		case 16 : /* FLI_COPY */
			fread(buf,1,64000U,f1);
			memcpy(vram,buf,64000U);
			break;
	}
	fseek(f1,chunkstart+chunkheader.size,SEEK_SET);
	return(0);
}