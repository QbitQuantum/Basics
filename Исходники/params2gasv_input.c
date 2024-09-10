// num_skipped counts the number of reads that do not show up in output. Used by validate to account for all the input reads.
b2g_error_t params2gasv_input(char *BAM_PATH, char *OUTPUT_PREFIX, int MAPPING_QUALITY, int WRITE_CONCORDANT, int WRITE_LOWQ, int LOW_MEMORY, int AMBIGUOUS, int LIB_SEP, int VERBOSE, int CUTOFF_X, int CUTOFF_Y, b2g_cutoff_lminlmax_mode_t CUTOFF_MODE, char *CUTOFF_NAME, int PROPER_LENGTH, int USE_NUMBER_READS, int DEBUG_LEVEL, int WRITE_SPLITREAD, int MIN_ALIGNED_PCT, char *CHROMOSOME_NAMING, b2g_platform_t PLATFORM, int VALIDATION_STRINGENCY, int GASV_PRO, int IGNORE_DUPLICATES, int QNAME_SORTED, int SPLIT_BY_CHROMOSOME, unsigned int *num_skipped) {
  assert(BAM_PATH && OUTPUT_PREFIX && in_range(MAPPING_QUALITY, 0, 255) && is_bool(WRITE_CONCORDANT) && is_bool(WRITE_LOWQ) && is_bool(LOW_MEMORY) && is_bool(AMBIGUOUS) && is_bool(LIB_SEP) && is_bool(VERBOSE) && CUTOFF_MODE && (FILENAME != CUTOFF_MODE || CUTOFF_NAME) && is_nonnegative(PROPER_LENGTH) && is_positive(USE_NUMBER_READS) && is_bool(WRITE_SPLITREAD) && in_range(MIN_ALIGNED_PCT, 50, 100) && is_bool(GASV_PRO) && is_bool(IGNORE_DUPLICATES) && is_bool(SPLIT_BY_CHROMOSOME));

  b2g_error_t ERR = B2GERR_NO_ERROR;
  hash_t *pairtable = NULL;
  samfile_t *in = NULL, *lowq_file = NULL, *split_file = NULL;
  FILE *chromosome_naming_file = NULL, *cutoff_file = NULL, *info_file = NULL, *gasv_file = NULL, *gasvpro_file = NULL;
  unsigned long GENOME_LENGTH = DEFAULT_GENOME_LENGTH;
  if (GASV_PRO && !WRITE_CONCORDANT) {
    if (VERBOSE) printf("-WRITE_CONCORDANT is required for -GASVPRO output. Automatically enabling.\n\n");
    WRITE_CONCORDANT = 1;    
  }
  if (AMBIGUOUS && !QNAME_SORTED) {
    if (VERBOSE) printf("-QNAME_SORTED is required for -AMBIGUOUS output. Automatically enabling.\n\n");
    QNAME_SORTED = 1; 
  }
  if (FILENAME == CUTOFF_MODE && !LIB_SEP) {
    if (VERBOSE) printf("-LIB_SEP sep is required for -CUTOFF_LMINLMAX FILE=... output. Automatically enabling.\n\n");
    LIB_SEP = 1;     
  }
  if (AMBIGUOUS && (WRITE_LOWQ || WRITE_SPLITREAD)) {
    if (VERBOSE) printf("-WRITE_LOWQ and -WRITE_SPLITREAD behavior are undefined for -AMBIGUOUS. Automatically disabling\n\n");
    WRITE_LOWQ = WRITE_SPLITREAD = 0; 
  }

  // Open all external resources and abort if failure.
  if ((ERR = _open_files(&in, &chromosome_naming_file, &cutoff_file, &lowq_file, &split_file, &info_file, &gasv_file, &gasvpro_file, BAM_PATH, OUTPUT_PREFIX, CHROMOSOME_NAMING, CUTOFF_MODE, CUTOFF_NAME, WRITE_LOWQ, WRITE_SPLITREAD, GASV_PRO))) return _cleanup(in, chromosome_naming_file, cutoff_file, lowq_file, split_file, info_file, gasv_file, gasvpro_file, pairtable, ERR);

  // Allocate hash table
  struct stat st;
  stat(BAM_PATH, &st);  
  if (!(pairtable = hash(!QNAME_SORTED * ((st.st_size / B2G_HASH_SIZE) / (LOW_MEMORY ? MAX_BAM_FILES : 1))))) return _cleanup(in, chromosome_naming_file, cutoff_file, lowq_file, split_file, info_file, gasv_file, gasvpro_file, pairtable, B2GERR_OUT_OF_MEMORY);

  // Calculate required space for bam_header metadata,
  int NUM_CHROMOSOMES, NUM_READGROUPS, NUM_LIBRARIES;
  b2g_bam_header_counts(in->header, &NUM_CHROMOSOMES, &NUM_READGROUPS, &NUM_LIBRARIES, &LIB_SEP, PROPER_LENGTH);
    
  // allocate memory for said data,
  b2g_cutoff_lminlmax_t cutoff_lminlmax = {CUTOFF_MODE, CUTOFF_X , CUTOFF_Y, CUTOFF_NAME};
  int chromosome_numbers[NUM_CHROMOSOMES];
  b2g_chromosomes_t chromosomes = {NUM_CHROMOSOMES, chromosome_numbers};
  b2g_readgroup2library_t rgs2libs[NUM_READGROUPS];
  b2g_library_t libs[NUM_LIBRARIES];
  b2g_libraries_t libraries = {NUM_READGROUPS, NUM_LIBRARIES, &rgs2libs[0], &libs[0]};

  // and read the header into that memory.
  if ((ERR = b2g_bam_header_read(in->header, &chromosomes, &libraries, &GENOME_LENGTH, cutoff_lminlmax, chromosome_naming_file, cutoff_file, LIB_SEP, USE_NUMBER_READS, PROPER_LENGTH, VERBOSE))) return _cleanup(in, chromosome_naming_file, cutoff_file, lowq_file, split_file, info_file, gasv_file, gasvpro_file, pairtable, ERR);

  // Do all the main program logic of splitting the bam file, sorting the contents, merging the final output, and dumping the statistics.
  if ((ERR = _split_sort_merge_dump(BAM_PATH, OUTPUT_PREFIX, MAPPING_QUALITY, WRITE_CONCORDANT, WRITE_LOWQ, LOW_MEMORY, AMBIGUOUS, LIB_SEP, VERBOSE, CUTOFF_X, CUTOFF_Y, CUTOFF_MODE, CUTOFF_NAME, PROPER_LENGTH, USE_NUMBER_READS, DEBUG_LEVEL, WRITE_SPLITREAD, MIN_ALIGNED_PCT, CHROMOSOME_NAMING, PLATFORM, GASV_PRO, IGNORE_DUPLICATES, lowq_file, split_file, &libraries, &chromosomes, pairtable, info_file, gasv_file, gasvpro_file, GENOME_LENGTH, QNAME_SORTED, SPLIT_BY_CHROMOSOME, num_skipped))) return _cleanup(in, chromosome_naming_file, cutoff_file, lowq_file, split_file, info_file, gasv_file, gasvpro_file, pairtable, ERR);

  return _cleanup(in, chromosome_naming_file, cutoff_file, lowq_file, split_file, info_file, gasv_file, gasvpro_file, pairtable, B2GERR_NO_ERROR);
}