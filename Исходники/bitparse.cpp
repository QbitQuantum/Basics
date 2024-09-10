int main(int argc, char**args)
{

  FILE_STYLE in_style  = STYLE_BIT;
  FILE_STYLE out_style = STYLE_BIT;
  uint64_t sum = 0L;
  unsigned int i;

  const char * outfile = NULL;
  while(true)
    {
      switch(getopt(argc, args, "?i:vo:O:"))
	{
	case -1: goto args_done;
	case 'i':
          if (BitFile::styleFromString(optarg, &in_style))
	    {
	      fprintf(stderr, "Unknown format \"%s\"\n", optarg);
	      usage();
	    }
	  break;

	case 'o':
          if (BitFile::styleFromString(optarg, &out_style))
	    {
	      fprintf(stderr, "Unknown format \"%s\"\n", optarg);
	      usage();
	    }
	  break;

	case 'O':
	  outfile = optarg;
	  break;
	case '?':
	case 'h':
	default:
	  usage();
	}
    }
 args_done:
  argc -= optind;
  args += optind;
  if(argc < 1)
    usage();
  try {
    BitFile  file;
    FILE* fp;

    if (*args[0] == '-')
      fp = stdin;
    else
      {
	fp=fopen(args[0],"rb");
	if(!fp)
	  {
	    fprintf(stderr, "Can't open datafile %s: %s\n", args[0], 
		    strerror(errno));
	  return 1;
	  }
      }
    file.readFile(fp, in_style);
    fprintf(stderr, "Created from NCD file: %s\n",file.getNCDFilename());
    fprintf(stderr, "Target device: %s\n",file.getPartName());
    fprintf(stderr, "Created: %s %s\n",file.getDate(),file.getTime());
    fprintf(stderr, "Bitstream length: %u bits %u bytes(0x%06x)\n", 
            file.getLength(),file.getLength()/8,file.getLength()/8);

    for (i = 0; i < file.getLength()/8; i++)
    {
        /* Umprogrammed Bytes are 0xff, so invert
           to not count them
        */
        sum += (file.getData()[i]) ^0xff;
    }
    fprintf(stderr, "64-bit sum: %" PRIu64 "\n", sum);
    
    if(outfile) {
      if(outfile[0] == '-')
	fp = stdout;
      else
	fp = fopen(outfile,"wb");
      if (fp)
	{
	  file.saveAs(out_style,file.getPartName(), fp);
	  fprintf(stderr, "Bitstream saved in format %s as file: %s\n",
                  BitFile::styleToString(out_style), outfile);
	}
      else
	  fprintf(stderr," Can't open %s: %s  \n", outfile, strerror(errno));
      }
    }
    catch(io_exception& e) {
      fprintf(stderr, "IOException: %s", e.getMessage().c_str());
      return  1;
    }
}