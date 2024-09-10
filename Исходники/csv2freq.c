int
main(int argc, char *argv[])
{
	FILE* infile;
	FILE* outfile;
	unsigned char c;
	unsigned char freq_s[128];
	double freq;
	unsigned char data[4];
	int freq_i;
	int ret;
	int notfirst=0;
	int ctr=0;
	int i;
	
	if (argc<2)
	{
		fprintf(stderr, "%s: Error: Invalid args\n", argv[0]);
		fprintf(stderr, "Syntax is: %s <infile> [outfile]\n", argv[0]);
		exit(1);
	}
	infile=fopen(argv[1], "rb");
	if (infile==NULL)
	{
		fprintf(stderr, "%s: Error: Unable to open input file '%s'\n", argv[0], argv[1]);
		exit(1);
	}
		
	if (argc>2)
	{
		outfile=fopen(argv[2], "w");
	}
	else
	{
		outfile=fopen("out.txt", "w");
	}
	if (outfile==NULL)
	{
		fprintf(stderr, "%s: Error: Unable to create output file\n", argv[0]);
		exit(1);
	}
	
	// read until we see a comma or EOF
	// Once we see comma or EOF, we can convert to FTW format
	i=0;
	while(1)
	{
		ret=fread(&c, 1, 1, infile);
		if ((ret!=1) || (c==',') || (c=='\n') || c=='\r' || (c==' '))
		{
			// We have seen a separator or whitespace or EOF
			if (i==0) // no characters read?
			{
				if (ret!=1) // EOF
				{
					// we're done
					break;
				}
				continue;
			}
			else
			{
				// some characters were read. Convert to FTW
				freq_s[i]='\0'; // terminate the string
				i=0;
				sscanf(freq_s, "%lf", &freq);
				freq_i=(int)freq;
				//freq2ftw(freq, data); // data array now contains the 4-byte FTW
				if (notfirst)
				{
					fprintf(outfile, ", ");
				}
				else
				{
					notfirst=1;
				}
				if (ctr%10==0) // do a newline every so often
				{
					fprintf(outfile, "\n");
				}
				ctr++;
				fprintf(outfile, "%d", freq_i);
			}
		}
		else
		{
			freq_s[i]=c;
			i++;
		}
	} // end while(1)
	
	fclose(infile);
	fclose(outfile);
	
	return(0);
}