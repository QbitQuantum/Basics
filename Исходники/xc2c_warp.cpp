int main(int argc, char**args)
{
  bool verbose = false;
  bool revert  = false;
  const char * outfile = NULL;
  FILE_STYLE  in_style = STYLE_BIT;
  FILE_STYLE out_style = STYLE_BIT;
  char device[256]= "";
  FILE *fp = NULL;
  const char * mapdir = NULL;
  fprintf(stderr, "Release $Rev: 237 $\n"
	  "Please provide feedback on success/failure/enhancement requests!\n"
	  "Check Sourceforge SVN for updates!\n");

  while(true) {
    switch(getopt(argc, args, "?m:i:vo:O:")) {
    case -1:
     goto args_done;

    case 'v':
      verbose = true;
      break;

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
      
    case 'm':
      mapdir = optarg;
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
  MapFile_XC2C map;
  JedecFile  fuses;
  BitFile bits;
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
  
  if (fuses.readFile(fp) == 0)
    {
      if (verbose)
	fprintf(stderr,"Jedecfile %s for %s: %d Fuses, Checksum: 0x%04x\n", 
		args[0], fuses.getDevice(), fuses.getLength(),
		fuses.getChecksum());
      strncpy(device, fuses.getDevice(), 255);
    }
  else
    {
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
      if (bits.readFile(fp, in_style) == 0 )
	{
	  if (verbose)
	    fprintf(stderr,"Got Bitfile for Device %s: %ld Fuses\n", 
		    bits.getPartName(), bits.getLength());
	  revert = true;
	  strncpy(device, bits.getPartName(), 255);
	}
      
      else
	{
	  fprintf(stderr, "File %s not recognized as Bit- or Jedecfile\n",
		  args[0]);
	  return 3;
	}
    }
  if (map.loadmapfile(mapdir, device))
    {
      fprintf(stderr, "failed to load Mapfile %s, aborting\n",
	      map.GetFilename());
      return 2;
    }
  if(outfile)
    {
      fp = fopen(outfile,"wb");
      if (!fp)
	{
	  fprintf(stderr, "failed to open %s: %s\n", outfile,
		  strerror(errno));
	  return 1;
	}
    }
  else return 0;
  if (revert)
    {
      map.bitfile2jedecfile(&bits, &fuses);
      fprintf(stderr, "Device %s: %d Fuses, Checksum calculated: 0x%04x,"
	      " Checksum from file 0x%04x\n",
		 fuses.getDevice(), fuses.getLength(), fuses.calcChecksum(),
	      fuses.getChecksum());
      fuses.saveAsJed( device, fp);
    }
  else
    {
      map.jedecfile2bitfile(&fuses, &bits);
      bits.saveAs(out_style, device, fp);
     }
  return 0; 
}