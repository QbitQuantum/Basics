//-----------------------------------------------------------------------------
int main(int narg, char **arg)
{
	mglGraphZB gr;
	mglParse p(true);

	if(narg==1)
	{
		printf("mgl2gif convert mgl script to bitmap gif file.\n");
		printf("Current version is 1.%g\n",MGL_VERSION);
		printf("Usage:\tmgl2gif scriptfile [outputfile parameter(s)]\n");
		printf("\tParameters have format \"-Nval\".\n");
		printf("\tHere N=0,1...9 is parameter ID and val is its value.\n");
		printf("\tOption -Lval set locale to val.\n");
		printf("\tOption -Aval add value of $0 for making animation.\n");
		printf("\tOption -Cn1:n2 cycle from n1 to n2 for making animation.\n");
	}
	else
	{
		Str *head=0, *cur=0;
		FILE *fp = fopen(arg[1],"rb");
		if(fp==0)	{	printf("Couldn't open file %s\n",arg[1]);	return 1;	}
		wchar_t str[8192];
		char fname[2048], buf[2048];
		for(long i=2;i<narg;i++)	// add arguments for the script
		{
			if(arg[i][0]=='-' && arg[i][1]>='0' && arg[i][1]<='9')
				p.AddParam(arg[i][1]-'0',arg[i]+2);
			if(arg[i][0]=='-' && arg[i][1]=='L')
				setlocale(LC_CTYPE, arg[i]+2);
			if(arg[i][0]=='-' && arg[i][1]=='A')
			{
				if(cur)	cur = new Str(cur,arg[i]+2);
				else	head = cur = new Str(0,arg[i]+2);
			}
			if(arg[i][0]=='-' && arg[i][1]=='C')
			{
				int n,n1,n2;
				sscanf(arg[i]+2,"%d:%d",&n1,&n2);
				char str[64];
				for(n=n1;n<n2;n++)
				{
					sprintf(str,"%d",n);
					if(cur)	cur = new Str(cur,str);
					else	head = cur = new Str(0,str);
				}
			}
		}
		if(narg>2 && arg[2][0]!='-')	strcpy(fname,arg[2]);
		else
		{
			strcpy(fname,arg[1]);	strcat(fname,".gif");
			printf("Write output to %s\n",fname);
		}
		// first read animation parameters from file
		while(!feof(fp))
		{
			if(!fgetws(str,8192,fp))	break;
			wcstrim_mgl(str);
			if(str[0]=='#' && str[1]=='#' && str[2]=='a' && str[3]==' ')
			{
				if(cur)	cur = new Str(cur,str+4);
				else	head = cur = new Str(0,str+4);
			}
			if(str[0]=='#' && str[1]=='#' && str[2]=='c' && str[3]==' ')
			{
				float v1,v2,dv,v;
				wscanf(str+4,"%g %g %g",&v1,&v2,&dv);
				char ss[64];
				for(v=v1;v<v2;v+=dv)
				{
					sprintf(ss,"%g",v);
					if(cur)	cur = new Str(cur,ss);
					else	head = cur = new Str(0,ss);
				}
			}
		}
		// now execute it and save
		gr.Message = buf;	*buf=0;
		if(head)	// as animated gif
		{
			gr.StartGIF(fname);
			for(cur = head;cur!=0;cur=cur->next)
			{
				fseek(fp,0,SEEK_SET);
				gr.NewFrame();
				p.AddParam(0,cur->str);
				p.Execute(&gr,fp,true);
				gr.EndFrame();
			}
			gr.CloseGIF();
		}
		else	// simple gif
		{
			fseek(fp,0,SEEK_SET);
			p.Execute(&gr,fp,true);
			gr.WriteGIF(fname);
		}
		fclose(fp);
	}
	return 0;
}