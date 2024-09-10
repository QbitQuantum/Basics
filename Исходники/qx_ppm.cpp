int loadimage(float* out,unsigned char *out_u,char* file_name, int h_in, int w_in)
{	
	FILE * file_in;
	char line[LEN_MAX];
	int	i,imax,h,w;
	//file_in=fopen(file_name,"rb");
	fopen_s(&file_in,file_name,"rb");
	if(!file_in)
	{
		printf("Please check input file_name: %s\n",file_name);
		getchar();
		return(-1);
	}
	if(fgetc(file_in)=='P') 
		//fscanf(file_in,"%d\n",&i);
		fscanf_s(file_in,"%d\n",&i);
	else
	{ 
		printf("Bad	header in ppm file.\n");
		getchar();
		return(-1);
	}
	while(fgets(line,LEN_MAX,file_in)!=NULL)
	{
		if(line[0]=='#') continue;
		else
		{	
			//sscanf(line, "%d %d\n",	&w,	&h);
			sscanf_s(line, "%d %d\n",	&w,	&h);
			break;
		}
	}
	if(h!=h_in||w!=w_in)
	{
		printf("The allocated memory for the image is not correct!! It should be [%dx%d].\n",h,w);
		getchar();
		return(-1);
	}
	//fscanf(file_in, "%d\n", &imax);
	fscanf_s(file_in, "%d\n", &imax);
	switch (i)
	{
		case 2:
			get_ascii_pgm(out_u,file_in,w,h);
			for(i=0;i<h_in*w_in;i++) out[i]=(float)out_u[i];
			break;
		case 3:
			get_ascii_ppm(out_u,file_in,w,h);
			for(i=0;i<h_in*w_in*3;i++) out[i]=(float)out_u[i];
			break;
		case 5:
			fread(out_u,sizeof(unsigned char),w*h,file_in);
			for(i=0;i<h_in*w_in;i++) out[i]=(float)out_u[i];
			break;
		case 6:
			fread(out_u,sizeof(unsigned char),h*w*3,file_in);
			for(i=0;i<h_in*w_in*3;i++) 
				out[i]=(float)out_u[i];
			break;
		default:
			break;
	}	
	fclose(file_in);
	return(0);
}