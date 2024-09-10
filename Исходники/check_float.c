int main(int argc, char **argv)
{
	int opt;
	char *ptr;
	int linenr, posnr, diff;
	char line1[MAXLINELEN], line2[MAXLINELEN];
	char *ptr1, *ptr2;
	int pos1, pos2;
	int read1, read2, n1, n2;
	flt f1, f2;
	flt absdiff, reldiff;

	progname = argv[0];

	/* Parse command-line options */
	abs_prec = default_abs_prec;
	rel_prec = default_rel_prec;
	show_help = show_version = 0;
	opterr = 0;
	while ( (opt = getopt_long(argc,argv,"a:r:",long_opts,(int *) 0))!=-1 ) {
		switch ( opt ) {
		case 0:   /* long-only option */
			break;
		case 'a': /* absolute precision */
			abs_prec = strtold(optarg,&ptr);
			if ( *ptr!=0 || ptr==(char *)&optarg )
				error(errno,"incorrect absolute precision specified");
			break;
		case 'r': /* relative precision */
			rel_prec = strtold(optarg,&ptr);
			if ( *ptr!=0 || ptr==(char *)&optarg )
				error(errno,"incorrect relative precision specified");
			break;
		case ':': /* getopt error */
		case '?':
			error(0,"unknown option or missing argument `%c'",optopt);
			break;
		default:
			error(0,"getopt returned character code `%c' ??",(char)opt);
		}
	}
	if ( show_help ) usage();
	if ( show_version ) version();

	if ( argc<optind+3 ) error(0,"not enough arguments given");

	file1name = argv[optind+1];
	file2name = argv[optind+2];

	if ( strcmp(file1name,"-")==0 && strcmp(file2name,"-")==0 ) {
		error(0,"both files specified as standard input");
	}

	if ( strcmp(file1name,"-")==0 ) {
		file1 = stdin;
	} else {
		if ( (file1 = fopen(file1name,"r"))==NULL ) error(errno,"cannot open '%s'",file1name);
	}
	if ( strcmp(file2name,"-")==0 ) {
		file2 = stdin;
	} else {
		if ( (file2 = fopen(file2name,"r"))==NULL ) error(errno,"cannot open '%s'",file2name);
	}

	linenr = 0;
	diff = 0;

	while ( 1 ) {
		linenr++;
		ptr1 = fgets(line1,MAXLINELEN,file1);
		ptr2 = fgets(line2,MAXLINELEN,file2);

		if ( ptr1==NULL && ptr2==NULL ) break;

		if ( ptr1==NULL && ptr2!=NULL ) {
			printf("line %3d: file 1 ended before 2.\n",linenr);
			diff++;
			break;
		}
		if ( ptr1!=NULL && ptr2==NULL ) {
			printf("line %3d: file 2 ended before 1.\n",linenr);
			diff++;
			break;
		}

		pos1 = pos2 = 0;
		posnr = 0;
		while ( 1 ) {
			posnr++;

			read1 = sscanf(&line1[pos1],"%Lf",&f1);
			read2 = sscanf(&line2[pos2],"%Lf",&f2);
			sscanf(&line1[pos1],"%*f%n",&n1);
			sscanf(&line2[pos2],"%*f%n",&n2);
			pos1 += n1;
			pos2 += n2;

			if ( read1==EOF && read2==EOF ) break;

			if ( read1!=1 && read2==1 ) {
				printf("line %3d: file 1 misses %d-th float.\n",linenr,posnr);
				diff++;
				break;
			}
			if ( read1==1 && read2!=1 ) {
				printf("line %3d: file 1 has excess %d-th float.\n",linenr,posnr);
				diff++;
				break;
			}

			if ( read1==0 ) {
				printf("line %3d: file 1, %d-th entry cannot be parsed as float.\n",
				       linenr,posnr);
				diff++;
				break;
			}
			if ( read2==0 ) {
				printf("line %3d: file 2, %d-th entry cannot be parsed as float.\n",
				       linenr,posnr);
				diff++;
				break;
			}

			if ( !(read1==1 && read2==1) ) {
				error(0,"error reading float on line %d",linenr);
			}


			if ( ! equal(f1,f2) ) {
				diff++;
				printf("line %3d: %d-th float differs: %8LG != %-8LG",
				       linenr,posnr,f1,f2);
				if ( isfinite(f1) && isfinite(f2) ) {
					absdiff = fabsl(f1-f2);
					reldiff = fabsl((f1-f2)/f2);
					if ( absdiff>abs_prec ) printf("  absdiff = %9.5LE",absdiff);
					if ( reldiff>rel_prec ) printf("  reldiff = %9.5LE",reldiff);
				}
				printf("\n");
			}
		}
	}

	fclose(file1);
	fclose(file2);

	if ( diff > 0 ) printf("Found %d differences in %d lines\n",diff,linenr-1);

	return 0;
}