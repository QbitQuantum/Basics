//
// Handle command line arguments
//
void parseScanOptions(int argc, char** argv)
{

	std::string bamlistfile =  "";
	std::string rev = "";

	Headers hd;
    for (char c; (c = getopt_long(argc, argv, shortopts, longopts, NULL)) != -1;)
    {
        std::istringstream arg(optarg != NULL ? optarg : "");
        switch (c)
        {
            case 'f':
            	arg >> bamlistfile; break;
            case 'o':
            	arg >> opt::outputfile; break;
            case 'H':
            	opt::writerheader=false; break;
            case 'm':
                opt::mergerg = true; break;
            case 'u':
                opt::ignorerg = true; break;
            case 'w':
                opt::onebam = true; break;
            case 'h':
        		for(size_t h=0; h<hd.headers.size();h++){
        			std::cout << hd.headers[h] << ScanParameters::FIELD_SEP;
        		}
        		std::cout << "\n";
        		exit(EXIT_SUCCESS);
            case 'k':
            	arg >> opt::tel_k;
            	break;
            case 'r':
				arg >> ScanParameters::READ_LENGTH;
				if(ScanParameters::READ_LENGTH <= 0 || ScanParameters::READ_LENGTH > 100000){
					std::cerr << "please specify valid read length that is greater than 0 and length than 100kb" << "\n";
					exit(EXIT_FAILURE);
				}
				break;
            case 'p':

				break;
            case 'z':
            	arg >> ScanParameters::PATTERN;
				ScanParameters::PATTERN_REVCOMP = reverseComplement(ScanParameters::PATTERN);
				std::cerr << "use user specified pattern " <<  ScanParameters::PATTERN << "\n";
				std::cerr << "reverse complement " <<  ScanParameters::PATTERN_REVCOMP << "\n";
            	break;
            case 'e':
            	arg >> opt::exomebedfile;
            	opt::exomebed = readBedAsVector(opt::exomebedfile);
            	std::cout << "loaded "<< opt::exomebed.size() << " exome regions \n"<< std::endl;
//            	std::cout << opt::exomebed << "\n";
            	break;

            case OPT_HELP:
                std::cout << TELSEQ_USAGE_MESSAGE;
                exit(EXIT_SUCCESS);
            case OPT_VERSION:
                std::cout << TELSEQ_VERSION_MESSAGE;
                exit(EXIT_SUCCESS);
        }
    }

    update_pattern();

    // deal with cases of API usage:
    // telseq a.bam b.bam c.bam ...
    // | telseq
    // telseq -f

    if (argc - optind < 1) // no argument specified
    {
    	// check if it is from pipe
		if(!isatty(fileno(stdin))){
			std::string line;
			while (std::getline(std::cin, line))
			{
				if(line.empty()){
					continue;
				}
				opt::bamlist.push_back(line);
			}
		}else if(bamlistfile.empty() ){ // check if not from a pipe, -f must be spceified
//    		std::cerr << SUBPROGRAM ": No BAM specified. Please specify BAM either directly, by using -f option or piping BAM file path.\n";
    		std::cout << TELSEQ_USAGE_MESSAGE;
    		exit(EXIT_FAILURE);
    	}
    }

    else if (argc - optind >= 1) // if arguments are specified
    {
    	// -f has higher priority, when specified, ignore arguments.
    	if(bamlistfile.empty()){
    		for(int i = optind; i < argc; ++i ){
    		    opt::bamlist.push_back(argv[i]);
    		}
    	}
    }

    // read in bamlist
    if(!bamlistfile.empty()){
        size_t filesize = getFilesize(bamlistfile);
        if(filesize == 0)
        {
            std::cerr << PROGRAM_BIN ": BAMLIST file specified by -f is empty\n";
            exit(EXIT_FAILURE);
        }

        std::istream* pReader = createReader(bamlistfile);
        std::string line;

        while(getline(*pReader, line))
        {
        	if(line.empty()){
        		continue;
        	}
            opt::bamlist.push_back(line);
        }

        size_t bamsize = opt::bamlist.size();
        if(bamsize == 0 ){
            std::cerr << PROGRAM_BIN ": Could find any sample in BAMLIST file specified.\n";
            exit(EXIT_FAILURE);
        }
        delete pReader;
    }

    // check output
//    for(size_t i = 0; i < opt::bamlist.size(); ++i ){
//    	std::cerr << "opt::bamlist:" << opt::bamlist[i] << "\n";
//    }
//    std::cerr << "opt::bamlistfile:" << bamlistfile << "\n";
//    std::cerr << "opt::writerheader:" << opt::writerheader << "\n";
//    std::cerr << "opt::tel_k:" << opt::tel_k << "\n";
//    std::cerr << "opt::outputdir:" << opt::outputfile << "\n";

}