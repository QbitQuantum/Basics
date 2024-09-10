/* Main Program */
INT4 main ( INT4 argc, CHAR *argv[] ) {

  static LALStatus status;
  INT4 c;
  UINT4 i;
  REAL8 dt, totTime;
  REAL8 sampleRate = -1;
  REAL8 totalMass = -1, massRatio = -1;
  REAL8 lowFreq = -1, df, fLow;
  CHAR  *outFile = NULL, *outFileLong = NULL, tail[50];
  size_t optarg_len;
  REAL8 eta;
  REAL8 newtonianChirpTime, PN1ChirpTime, mergTime;
  UINT4 numPts;
  LIGOTimeGPS epoch;
  REAL8 offset;

  PhenomCoeffs coeffs;
  PhenomParams params;

  REAL4FrequencySeries     *Aeff   = NULL, *Phieff  = NULL;
  COMPLEX8Vector           *uFPlus = NULL, *uFCross = NULL;

  COMPLEX8 num;

  REAL4Vector      *hPlus = NULL, *hCross = NULL;
  REAL4TimeSeries  *hP = NULL, *hC = NULL;
  /*  REAL4TimeSeries  *hP = NULL, *hC = NULL;*/
  REAL4FFTPlan     *prevPlus = NULL, *prevCross = NULL;

  /*REAL4Vector      *Freq = NULL;*/

  UINT4 windowLength;
  INT4 hPLength;
  REAL8 linearWindow;

  /* getopt arguments */
  struct option long_options[] =
  {
    {"mass-ratio",              required_argument, 0,                'q'},
    {"low-freq (Hz)",           required_argument, 0,                'f'},
    {"total-mass (M_sun)",      required_argument, 0,                'm'},
    {"sample-rate",             required_argument, 0,                's'},
    {"output-file",             required_argument, 0,                'o'},
    {"help",                    no_argument,       0,                'h'},
    {"version",                 no_argument,       0,                'V'},
    {0, 0, 0, 0}
  };

  /* parse the arguments */
  while ( 1 )
  {
    /* getopt_long stores long option here */
    int option_index = 0;

    /* parse command line arguments */
    c = getopt_long_only( argc, argv, "q:t:d:hV",
        long_options, &option_index );

    /* detect the end of the options */
    if ( c == -1 )
      {
	break;
      }

    switch ( c )
    {
      case 0:
        fprintf( stderr, "Error parsing option '%s' with argument '%s'\n",
            long_options[option_index].name, optarg );
        exit( 1 );
        break;

      case 'h':
        /* help message */
        print_usage( argv[0] );
        exit( 0 );
        break;

      case 'V':
        /* print version information and exit */
        fprintf( stdout, "%s - Compute Ajith's Phenomenological Waveforms " \
		 "(arXiv:0710.2335) and output them to a plain text file\n" \
            "CVS Version: %s\nCVS Tag: %s\n", PROGRAM_NAME, CVS_ID_STRING, \
            CVS_NAME_STRING );
        exit( 0 );
        break;

      case 'q':
        /* set mass ratio */
        massRatio = atof( optarg );
        break;

      case 'f':
        /* set low freq */
        lowFreq = atof( optarg );
        break;

      case 'm':
        /* set total mass */
        totalMass = atof( optarg );
        break;

      case 's':
        /* set sample rate */
        sampleRate = atof( optarg );
        break;

      case 'o':
	/* set name of output file */
        optarg_len = strlen(optarg) + 1;
        outFile = (CHAR *)calloc(optarg_len, sizeof(CHAR));
        memcpy(outFile, optarg, optarg_len);
	break;

      case '?':
        print_usage( argv[0] );
        exit( 1 );
        break;

      default:
        fprintf( stderr, "ERROR: Unknown error while parsing options\n" );
        print_usage( argv[0] );
        exit( 1 );
    }
  }

  if ( optind < argc )
  {
    fprintf( stderr, "ERROR: Extraneous command line arguments:\n" );
    while ( optind < argc )
      {
	fprintf ( stderr, "%s\n", argv[optind++] );
      }
    exit( 1 );
  }


  /* * * * * * * * */
  /* Main Program  */
  /* * * * * * * * */

  eta = massRatio / pow(1. + massRatio, 2.);

  /* This freq low is the one used for the FFT */
  /* fLow = 2.E-3/(totalMass*LAL_MTSUN_SI); */
  fLow = lowFreq;       /* Changed by Ajith. 5 May 2008 */

  /* Phenomenological coefficients as in Ajith et. al */
  GetPhenomCoeffsLongJena( &coeffs );

  /* Compute phenomenologial parameters */
  ComputeParamsFromCoeffs( &params, &coeffs, eta, totalMass );


  /* Check validity of arguments */

  /* check we have freqs */
  if ( totalMass < 0 )
    {
      fprintf( stderr, "ERROR: --total-mass must be specified\n" );
      exit( 1 );
    }

  /* check we have mass ratio and delta t*/
  if ( massRatio < 0 )
    {
      fprintf( stderr, "ERROR: --mass-ratio must be specified\n" );
      exit( 1 );
    }
  if ( lowFreq < 0 )
    {
      fprintf( stderr, "ERROR: --low-freq must be specified\n" );
      exit( 1 );
    }
  if ( sampleRate < 0 )
    {
      fprintf( stderr, "ERROR: --sample-rate must be specified\n" );
      exit( 1 );
    }
  if ( lowFreq > params.fCut )
    {
      fprintf( stderr, "\nERROR in --low-freq\n"\
	       "The value chosen for the low frequency is larger "\
	       "than the frequency at the merger.\n"
	       "Frequency at the merger: %4.2f Hz\nPick either a lower value"\
	       " for --low-freq or a lower total mass\n\n", params.fCut);
      exit(1);
    }
  if ( lowFreq < fLow )
    {
      fprintf( stderr, "\nERROR in --low-freq\n"\
	       "The value chosen for the low frequency is lower "\
	       "than the lowest frequency computed\nby the implemented FFT.\n"
	       "Lowest frequency allowed: %4.2f Hz\nPick either a higher value"\
	       " for --low-freq or a higher total mass\n\n", fLow);
      exit(1);
    }
  if ( outFile == NULL )
    {
      fprintf( stderr, "ERROR: --output-file must be specified\n" );
      exit( 1 );
    }

  /* Complete file name with details of the input variables */
  sprintf(tail, "%s-Phenom_M%3.1f_R%2.1f.dat", outFile, totalMass, massRatio);
  optarg_len = strlen(tail) + strlen(outFile) + 1;
  outFileLong = (CHAR *)calloc(optarg_len, sizeof(CHAR));
  strcpy(outFileLong, tail);

  /* check sample rate is enough */
  if (sampleRate > 4.*params.fCut)   /* Changed by Ajith. 5 May 2008 */
    {
      dt = 1./sampleRate;
    }
  else
    {
      sampleRate = 4.*params.fCut;
      dt = 1./sampleRate;
    }

  /* Estimation of the time duration of the binary           */
  /* See Sathya (1994) for the Newtonian and PN1 chirp times */
  /* The merger time is overestimated                        */
  newtonianChirpTime =
    (5./(256.*eta))*pow(totalMass*LAL_MTSUN_SI,-5./3.)*pow(LAL_PI*fLow,-8./3.);
  PN1ChirpTime =
    5.*(743.+924.*eta)/(64512.*eta*totalMass*LAL_MTSUN_SI*pow(LAL_PI*fLow,2.));
  mergTime = 2000.*totalMass*LAL_MTSUN_SI;
  totTime = 1.2 * (newtonianChirpTime + PN1ChirpTime + mergTime);

  numPts = (UINT4) ceil(totTime/dt);
  df = 1/(numPts * dt);

  /* Compute Amplitude and Phase from the paper (Eq. 4.19) */
  Aeff = XLALHybridP1Amplitude(&params, fLow, df, eta, totalMass, numPts/2+1);
  Phieff = XLALHybridP1Phase(&params, fLow, df, eta, totalMass, numPts/2 +1);

  /* Construct u(f) = Aeff*e^(i*Phieff) */
  XLALComputeComplexVector(&uFPlus, &uFCross, Aeff, Phieff);

  /* Scale this to units of M */
  for (i = 0; i < numPts/2 + 1; i++) {
    num = uFPlus->data[i];
    num.re *= 1./(dt*totalMass*LAL_MTSUN_SI);
    num.im *= 1./(dt*totalMass*LAL_MTSUN_SI);
    uFPlus->data[i] = num;
    num = uFCross->data[i];
    num.re *= 1./(dt*totalMass*LAL_MTSUN_SI);
    num.im *= 1./(dt*totalMass*LAL_MTSUN_SI);
    uFCross->data[i] = num;
  }

  /* Inverse Fourier transform */
  LALCreateReverseREAL4FFTPlan( &status, &prevPlus, numPts, 0 );
  LALCreateReverseREAL4FFTPlan( &status, &prevCross, numPts, 0 );
  hPlus = XLALCreateREAL4Vector(numPts);
  hCross = XLALCreateREAL4Vector(numPts);

  LALReverseREAL4FFT( &status, hPlus, uFPlus, prevPlus );
  LALReverseREAL4FFT( &status, hCross, uFCross, prevCross );

  /* The LAL implementation of the FFT omits the factor 1/n */
  for (i = 0; i < numPts; i++) {
    hPlus->data[i] /= numPts;
    hCross->data[i] /= numPts;
  }

  /* Create TimeSeries to store more info about the waveforms */
  /* Note: it could be done easier using LALFreqTimeFFT instead of ReverseFFT */
  epoch.gpsSeconds = 0;
  epoch.gpsNanoSeconds = 0;

  hP =
    XLALCreateREAL4TimeSeries("", &epoch, 0, dt, &lalDimensionlessUnit, numPts);
  hP->data = hPlus;
  hC =
    XLALCreateREAL4TimeSeries("", &epoch, 0, dt, &lalDimensionlessUnit, numPts);
  hC->data = hCross;

  /* Cutting off the part of the waveform with f < fLow */
  /*  Freq = XLALComputeFreq( hP, hC);
      hP = XLALCutAtFreq( hP, Freq, lowFreq);
      hC = XLALCutAtFreq( hC, Freq, lowFreq); */

  /* multiply the last few samples of the time-series by a linearly
   * dropping window function in order to avid edges in the data
   * Added by Ajith 6 May 2008 */

  hPLength = hP->data->length;
  windowLength = (UINT4) (20.*totalMass * LAL_MTSUN_SI/dt);
  for (i=1; i<= windowLength; i++){
    linearWindow =  (i-1.)/windowLength;
    hP->data->data[hPLength-i] *= linearWindow;
    hC->data->data[hPLength-i] *= linearWindow;
  }

  /* Convert t column to units of (1/M) */
  /*  offset *= (1./(totalMass * LAL_MTSUN_SI));
      hP->deltaT *= (1./(totalMass * LAL_MTSUN_SI)); */

  /* Set t = 0 at the merger (defined as the max of the NR wave) */
  XLALFindNRCoalescenceTimeFromhoft( &offset, hP);
  XLALGPSAdd( &(hP->epoch), -offset);
  XLALGPSAdd( &(hC->epoch), -offset);

  /* Print waveforms to file */
  LALPrintHPlusCross( hP, hC, outFileLong );

  /* Free Memory */

  XLALDestroyREAL4FrequencySeries(Aeff);
  XLALDestroyREAL4FrequencySeries(Phieff);

  XLALDestroyREAL4FFTPlan(prevPlus);
  XLALDestroyREAL4FFTPlan(prevCross);

  XLALDestroyCOMPLEX8Vector(uFPlus);
  XLALDestroyCOMPLEX8Vector(uFCross);
  XLALDestroyREAL4TimeSeries(hP);
  XLALDestroyREAL4TimeSeries(hC);
  /*  XLALDestroyREAL4TimeSeries(hP); */
  /*  XLALDestroyREAL4TimeSeries(hC); */

  return(0);

}