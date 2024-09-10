/*----------------------------------------------------------------------
  Parameters:

  Description:
  ----------------------------------------------------------------------*/
static int
get_option(int argc, char *argv[])
{
  int  nargs = 0 ;
  char *option ;
  
  option = argv[1] + 1 ;            /* past '-' */
  if (!stricmp(option, "dt"))
    {
    }
  else if (!stricmp(option, "debug_voxel"))
    {
      Gx = atoi(argv[2]) ; Gy = atoi(argv[3]) ; Gz = atoi(argv[4]) ;
      nargs = 3 ;
      printf("debugging voxel (%d, %d, %d)\n", Gx, Gy, Gz) ;
    }
  else if (!stricmp(option, "remove"))
    {
      lta = LTAread(argv[2]) ;
      if (lta == NULL)
	ErrorExit(ERROR_NOFILE, "%s: could not read transform from %s\n", Progname, argv[2]) ;
      printf("removing determinant of transform %s\n", argv[2]) ;
      nargs = 1 ;
    }
  else if (!stricmp(option, "tm3d"))
    {
      tm3dfile = 1;
      printf("The input morph originated from a tm3d (mri_cvs_register file).\n") ;
    }
  else switch (toupper(*option))
    {
    case 'A':
      atlas = 1 ;
      printf("outputing in atlas coords\n") ;
      break ;
    case 'W':
      write_areas = 1 ;
      printf("writing area volumes\n") ;
      break ;
    case 'L':
      use_log = 1 ;
      printf("taking log of jacobian values before saving\n") ;
      break ;
    case 'S':
      sigma = atof(argv[2]) ;
      printf("smoothing jacobian volume with sigma=%2.2f\n", sigma) ;
      nargs = 1 ;
      break ;
    case 'Z':
      zero_mean = 1 ;
      use_log = 1 ;
      printf("making log jacobian zero mean\n") ;
      break ;
    case '?':
    case 'U':
      usage_exit(0) ;
      break ;
    default:
      fprintf(stderr, "unknown option %s\n", argv[1]) ;
      exit(1) ;
      break ;
    }
  
  return(nargs) ;
}