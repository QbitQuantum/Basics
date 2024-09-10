int main( int argc, char *argv[]) {

	PKCS7 *p7;
	PKCS7_SIGNER_INFO *si;
	X509_STORE_CTX cert_ctx;
	X509_STORE *cert_store=NULL;

	BIO *data = NULL, *p7bio=NULL;
	BIO *signature = NULL;

	int cmd=-1;
        char *infile=NULL;
        /* char *outfile=NULL; */
        char *certfile=NULL;
        char *keyfile=NULL;
        char *key=NULL;
	int nodetach=0;

	char *datafile = NULL;
	char *outfile = NULL;
	char *signaturefile = NULL;

	char buf[1024*4];
	char **pp = NULL;
	int badops=0, outdata=0, err=0, version=0, i;

	 /* default certificates dir */
	 /* char *certsdir="/usr/local/OpenCA/certs"; */

	 /* default certificates file */
	 /* char *certsfile="/usr/local/OpenCA/cacert.pem"; */

	char *certsdir = NULL;
	char *certsfile = NULL;

	STACK_OF(PKCS7_SIGNER_INFO) *sk;

	if ((bio_err=BIO_new(BIO_s_file())) != NULL)
		BIO_set_fp(bio_err,stderr,BIO_NOCLOSE|BIO_FP_TEXT);

	bio_err=BIO_new_fp(stderr,BIO_NOCLOSE);
	bio_out=BIO_new_fp(stdout,BIO_NOCLOSE);

#ifndef NO_MD5
        EVP_add_digest(EVP_md5());
#endif
#ifndef NO_SHA1
        EVP_add_digest(EVP_sha1());
#endif

	if( argc <= 1 ) {
		printVersion( bio_err, INFO );
		printf("ERROR: needed command and arguments missing\n\n");
		badops=1;
		goto badops;
	}

	if( ( cmd = getCommand( argc, argv ) ) == -1 ) {
		printVersion( bio_err, INFO );
		printf("ERROR: unknown command %s\n\n", argv[1] );
		badops=1;
		goto badops;
	}

	if( argc >= 1 ) {
		argc--;
		argv++;

		if( argc <= 1 )
		{
			printVersion( bio_err, INFO );
			printf("ERROR: needed at least one argument!\n\n" );
	                badops=1;
        	        goto badops;
		}
	}

	while (argc > 1) {
		argc--;
		argv++;
		if (strcmp(*argv,"-verbose") == 0)
                        {
			verbose=1;
			}
		else if (strcmp(*argv,"-print_data") == 0)
                        {
			outdata=1;
			}
		else if (strcmp(*argv,"-no_chain") == 0)
                        {
			chainVerify=0;
			}
		else if (strcmp(*argv,"-data") == 0)
			{
                        if (--argc < 1) goto bad;
			datafile= *( ++argv );
			}
		else if (strcmp(*argv,"-d") == 0)
			{
			/* Present for compatibility reasons ... */
                        if (--argc < 1) goto bad;
			datafile= *( ++argv );
			}
		else if (strcmp(*argv,"-in") == 0)
			{
                        if (--argc < 1) goto bad;
			infile= *( ++argv );
			}
		else if (strcmp(*argv,"-out") == 0)
			{
                        if (--argc < 1) goto bad;
			outfile= *( ++argv );
			}
		else if (strcmp(*argv,"-cd") == 0)
			{
                        if (--argc < 1) goto bad;
                        certsdir = *(++argv);
			}
		else if (strcmp(*argv,"-cf") == 0)
			{
                        if (--argc < 1) goto bad;
                        certsfile = *( ++argv );
			}
		else if (strcmp(*argv,"-cert") == 0)
			{
                        if (--argc < 1) goto bad;
                        certfile = *( ++argv );
			}
		else if (strcmp(*argv,"-keyfile") == 0)
			{
                        if (--argc < 1) goto bad;
                        keyfile = *( ++argv );
			}
		else if (strcmp(*argv,"-key") == 0)
			{
                        if (--argc < 1) goto bad;
                        key = *( ++argv );
			}
		else if (strcmp(*argv,"-nd") == 0)
                        {
			nodetach=1;
			}
		else if (strcmp(*argv,"-h") == 0)
			{
			   badops=1;
			   break;
			}
		else
			{
			if( argc == 2 ) {
				datafile = *argv;
				argc--;
				continue;
			}
bad:
			printVersion( bio_err, INFO );
                        BIO_printf(bio_err,"ERROR: unknown option %s\n\n",*argv);
                        badops=1;
                        break;
			}
	}

badops:
        if (badops) {
                for (pp=usage; (*pp != NULL); pp++)
                        BIO_printf(bio_err,*pp);
                        exit(1);
        }

	if( cmd == 1 ) {
		generateSignature( verbose, infile, outfile, certfile, keyfile, key, nodetach );
	} else if ( cmd == 2 )
		{
		verifySignature( verbose, infile, outfile, outdata, 
				chainVerify, datafile, certsdir, certsfile);
		}
	else if ( cmd == 3 )
		{
		sign2nd( verbose, infile, outfile, datafile, outdata );
		}
	exit(0);
}