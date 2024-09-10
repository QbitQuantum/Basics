int
main (int argc, char *argv[]) {
   const struct option long_options[] = {
      {"help", no_argument, 0, 'h'},
      {"verbose", no_argument, 0, 'v'},
      {"version", no_argument, 0, 'V'},
      {"bruteforce", required_argument, 0, 'B'},
      {"charset", required_argument, 0, 'c'},
      {"dictionary", required_argument, 0, 'd'},
      {"norteluser", required_argument, 0, 'u'},
      {0, 0, 0, 0}
   };
   const char *short_options = "hvVB:c:d:u:";
   int arg;
   int options_index=0;
   int verbose=0;
   unsigned brute_len=0; /* Bruteforce len.  0=dictionary attack (default) */
   const char *charset = NULL;
   char dict_file_name[MAXLINE];	/* Dictionary file name */
   char *nortel_user = NULL; /* For cracking Nortel Contivity passwords only */
   FILE *dictionary_file=NULL;	/* Dictionary file */
   IKE_UINT64 iterations=0;
   struct timeval start_time;	/* Program start time */
   struct timeval end_time;	/* Program end time */
   struct timeval elapsed_time; /* Elapsed time as timeval */
   double elapsed_seconds;	/* Elapsed time in seconds */
   unsigned psk_idx;		/* Index into psk list */
   unsigned psk_count;		/* Number of PSK entries in the list */
   unsigned psk_uncracked;	/* Number of uncracked PSK entries */
   unsigned char *hash_r;
   char line[MAXLINE];

   dict_file_name[0] = '\0';	/* Initialise to empty string */
/*
 *      Process options and arguments.
 */
   while ((arg=getopt_long_only(argc, argv, short_options, long_options, &options_index)) != -1) {
      switch (arg) {
         case 'h':      /* --help */
            psk_crack_usage(EXIT_SUCCESS);
            break;	/* NOTREACHED */
         case 'v':      /* --verbose */
            verbose++;
            break;
         case 'V':      /* --version */
            fprintf(stderr, "psk-crack (%s)\n\n", PACKAGE_STRING);
            fprintf(stderr, "Copyright (C) 2003-2007 Roy Hills, NTA Monitor Ltd.\n");
            fprintf(stderr, "ike-scan comes with NO WARRANTY to the extent permitted by law.\n");
            fprintf(stderr, "You may redistribute copies of ike-scan under the terms of the GNU\n");
            fprintf(stderr, "General Public License.\n");
            fprintf(stderr, "For more information about these matters, see the file named COPYING.\n");
            fprintf(stderr, "\n");
            exit(EXIT_SUCCESS);
            break;	/* NOTREACHED */
         case 'B':      /* --bruteforce */
            brute_len=Strtoul(optarg, 10);
            break;
         case 'c':      /* --charset */
            charset=make_message("%s", optarg);
            break;
         case 'd':      /* --dictionary */
            strlcpy(dict_file_name, optarg, sizeof(dict_file_name));
            brute_len = 0;
            break;
         case 'u':      /* --norteluser */
            nortel_user = make_message("%s", optarg);
            break;
         default:       /* Unknown option */
            psk_crack_usage(EXIT_FAILURE);
            break;	/* NOTREACHED */
      }
   } /* End While */

/*
 *	Check that we've got exactly one argument.
 */
   if ((argc - optind) != 1) {
      psk_crack_usage(EXIT_FAILURE);
   }
/*
 *	Display the starting message.
 */
   printf("Starting psk-crack [%s] (http://www.nta-monitor.com/tools/ike-scan/)\n",
          PACKAGE_STRING);
/*
 *	If the character set has not been specified, use the default one.
 */
   if (!charset)
      charset = default_charset;
/*
 *	Load the PSK entries from the data file.
 */
   psk_count = load_psk_params(argv[optind], nortel_user);
   if (verbose)
      printf("Loaded %u PSK entries from %s\n", psk_count, argv[optind]);
   if (psk_count < 1)
      err_msg("ERROR: No pre-shared keys to crack");
/*
 *	Open dictionary file if required.
 */
   if (!brute_len)	/* If not bruteforcing */
      dictionary_file = open_dict_file(dict_file_name);
/*
 *	Get program start time for statistics displayed on completion.
 */
   if (brute_len) {
      printf("Running in brute-force cracking mode\n");
   } else {
      printf("Running in dictionary cracking mode\n");
   }
   Gettimeofday(&start_time);
/*
 *	Cracking loop.
 */
   psk_uncracked = psk_count;
   if (brute_len) {	/* Brute force cracking */
      IKE_UINT64 max;
      unsigned base;
      unsigned i;
      IKE_UINT64 loop;
      IKE_UINT64 val;
      unsigned digit;

      base = strlen(charset);
      max = base;
      for (i=1; i<brute_len; i++)
         max *= base;	/* max = base^brute_len without using pow() */
      printf("Brute force with %u chars up to length %u will take up to "
             IKE_UINT64_FORMAT " iterations\n", base, brute_len, max);

      for (loop=0; psk_uncracked && loop<max; loop++) {
         char *line_p;

         val = loop;
         line_p = line;
         do {
            digit = val % base;
            val /= base;
            *line_p++ = charset[digit];
         } while (val);
         *line_p = '\0';
         if (verbose > 1)
            printf("Trying key \"%s\"\n", line);
         iterations++;
         for (psk_idx=0; psk_idx<psk_count; psk_idx++) {
            if (psk_list[psk_idx].live) {
               hash_r = compute_hash(&psk_list[psk_idx], line);
               if (!memcmp(hash_r, psk_list[psk_idx].hash_r,
                   psk_list[psk_idx].hash_r_len)) {
                  printf("key \"%s\" matches %s hash %s\n", line,
                         psk_list[psk_idx].hash_name,
                         psk_list[psk_idx].hash_r_hex);
                  psk_uncracked--;
                  psk_list[psk_idx].live=0;
               }
            }
         }
      }
   } else {	/* Dictionary cracking */
      while (psk_uncracked && fgets(line, MAXLINE, dictionary_file)) {
         char *line_p;
         for (line_p = line; !isspace((unsigned char)*line_p) &&
              *line_p != '\0'; line_p++)
            ;
         *line_p = '\0';
         if (verbose > 1)
            printf("Trying key \"%s\"\n", line);
         iterations++;
         for (psk_idx=0; psk_idx<psk_count; psk_idx++) {
            if (psk_list[psk_idx].live) {
               hash_r = compute_hash(&psk_list[psk_idx], line);
               if (!memcmp(hash_r, psk_list[psk_idx].hash_r,
                           psk_list[psk_idx].hash_r_len)) {
                  printf("key \"%s\" matches %s hash %s\n", line,
                         psk_list[psk_idx].hash_name,
                         psk_list[psk_idx].hash_r_hex);
                  psk_uncracked--;
                  psk_list[psk_idx].live=0;
               }
            }
         }
      }
   }
/*
 *	Display any hashes that we've not cracked.
 */
   for (psk_idx=0; psk_idx<psk_count; psk_idx++) {
      if (psk_list[psk_idx].live)
         printf("no match found for %s hash %s\n",
                psk_list[psk_idx].hash_name,
                psk_list[psk_idx].hash_r_hex);
   }
/*
 *      Get program end time and calculate elapsed time.
 */
   Gettimeofday(&end_time);
   timeval_diff(&end_time, &start_time, &elapsed_time);
   elapsed_seconds = (elapsed_time.tv_sec*1000 +
                      elapsed_time.tv_usec/1000.0) / 1000.0;
   if (elapsed_seconds < 0.000001)
      elapsed_seconds = 0.000001;	/* Avoid div by zero */
   printf("Ending psk-crack: " IKE_UINT64_FORMAT
          " iterations in %.3f seconds (%.2f iterations/sec)\n",
          iterations, elapsed_seconds, iterations/elapsed_seconds);
  
   if (!brute_len)
      fclose(dictionary_file);

   return 0;
}