int main (int argc, char** argv) {                                     
	int  ret, c;
	int i, repeat = 5;
	int cpu = 2;
	static int errortype = 1;
	static int verbose = 1;
	static int disableHuge = 0;
	static int madvisePoison = 0;
	static int poll_exit=0;
	static long length;
 	struct bitmask *nodes, *gnodes;
	int gpolicy;
	unsigned long error_opt;

	void *vaddrmin = (void *)-1UL, *vaddrmax = NULL;

        static size_t           pdcount=0;
        unsigned long           mattr, addrend, pages, count, nodeid, paddr = 0;
        unsigned long           addr_start=0, nodeid_start=-1, mattr_start=-1;
        unsigned int            pagesize = getpagesize();
        char                    pte_str[20];

        struct dlook_get_map_info req;
        static page_desc_t        *pdbegin=NULL;
        page_desc_t               *pd, *pdend;

	length = memsize("100k");
	nodes  = numa_allocate_nodemask();
	gnodes = numa_allocate_nodemask();
	progname = argv[0];


	while (1)
	{
		static struct option long_options[] =
		{
		  {"verbose",       no_argument,       &verbose, 1},
		  {"delay",         no_argument,       &delay, 1},
		  {"disableHuge",   no_argument,       &disableHuge, 1},
		  {"poll",          no_argument,       &poll_exit, 1},
		  {"madvisePoison", no_argument,       &madvisePoison, 1},
		  {"manual",        no_argument,       &manual, 1},
		  {"cpu",           required_argument, 0, 'c'},
		  {"errortype",     required_argument, 0, 'e'},
		  {"help",          no_argument,       0, 'h'},
		  {"length",        required_argument, 0, 'l'}
		};
		/* getopt_long stores the option index here. */
		int option_index = 0;

		c = getopt_long (argc, argv, "hc:e:l:",
			       long_options, &option_index);

		/* Detect the end of the options. */
		if (c == -1)
		break;

		switch (c)
		{
			case 'c':
                          cpu = atoi(optarg);
			  break;
			case 'e':
                          errortype = atoi(optarg);
			  break;
			case 'h':
			  help();
			case 'l':
			  /* Not exposed */
			  printf ("option -l with value `%s'\n", optarg);
			  length = memsize("optarg");
			  break;
			case '?':
			  /* getopt_long already printed an error message. */
			  exit(-1);
		}
	}

	cpu_process_setaffinity(getpid(), cpu);

	error_opt = get_etype(errortype);

	buf = mmap(NULL, length, PROT_READ|PROT_WRITE, MAP_PRIVATE|MAP_ANONYMOUS, 0, 0);

        if (mbind((void *)buf, length,  MPOL_DEFAULT, nodes->maskp, nodes->size, 0) < 0){
                perror("mbind error\n");
        } 
	/* Disable Hugepages */
	if (disableHuge)
		madvise((void *)buf, length, MADV_NOHUGEPAGE);

	if (madvisePoison)
		madvise((void *)buf, length,MADV_HWPOISON );

    	gpolicy = -1;
        if (get_mempolicy(&gpolicy, gnodes->maskp, gnodes->size, (void *)buf, MPOL_F_ADDR) < 0)
                perror("get_mempolicy");
        if (!numa_bitmask_equal(gnodes, nodes)) {
                printf("nodes differ %lx, %lx!\n", gnodes->maskp[0], nodes->maskp[0]);
        }

	strcpy(pte_str, "");
        addrend = ((unsigned long)buf)+length;        
        pages = (addrend-((unsigned long)buf))/pagesize;

        if (pages > pdcount) {
                pdbegin = realloc(pdbegin, sizeof(page_desc_t)*pages);
                pdcount = pages;
        }

        req.pid = getpid();
        req.start_vaddr = (unsigned long)buf;
        req.end_vaddr = addrend;
        req.pd = pdbegin;

	sigaction(SIGBUS, &recover_act, NULL);

	/*Fault in Pages */
	if(!poll_exit)
		hog((void *)buf, length);

	/* Get mmap phys_addrs */
	if ((fd = open(UVMCE_DEVICE, O_RDWR)) < 0) {                 
		printf("Failed to open: %s\n", UVMCE_DEVICE);  
		exit (1);                                     
	}                                               
	    
	if (ioctl(fd, UVMCE_DLOOK, &req ) < 0){        
		printf("Failed to INJECT_UCE\n");
		exit(1);                                      
	}                                               


	process_map(pd,pdbegin, pdend, pages, buf, addrend, pagesize, mattr,
		    nodeid, paddr, pte_str, nodeid_start, mattr_start, addr_start);

	printf("\n\tstart_vaddr\t 0x%016lx length\t 0x%x\n\tend_vaddr\t 0x%016lx pages\t %ld\n", 
		 buf , length, addrend, pages);


	uv_inject(pd,pdbegin, pdend, pages, (unsigned long)buf, addrend, pagesize, mattr,
		    nodeid, paddr, pte_str, nodeid_start, 
		    mattr_start, addr_start, error_opt);

	
	if (delay){
		printf("Enter char to consume bad memory..");
		getchar();
	}

	if (error_opt !=  UVMCE_PATROL_SCRUB_UCE){
		consume_it((void *)buf, length);
	}
out:
	close(fd);                                      
	return 0;                                       
}