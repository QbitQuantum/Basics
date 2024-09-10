static void parse_wiggle_format_line(WIGGLE_READER_T *reader, const char *line) {

  reader->format = INVALID_FMT;
  int status = regexec(
    &fixed_format_regex,
    line,
    NUM_MATCHES,
    matches,
    0
  );
  if (!status) {
    reader->format = FIXED_WIGGLE_FMT;
  }
  else if (status != REG_NOMATCH ) {
    regerror(status, &fixed_format_regex, error_message, ERROR_MESSAGE_SIZE);
    die(
      "Error checking for fixed step wiggle file: %s\n"
      "error message is %s\n",
      reader->filename, 
      error_message
    );
  }
  else {
    status = regexec(&var_format_regex, line, NUM_MATCHES, matches, 0);
    if (!status) {
      reader->format = VAR_WIGGLE_FMT;
    }
    else if (status != REG_NOMATCH ) {
      regerror(status, &var_format_regex, error_message, ERROR_MESSAGE_SIZE);
      die(
        "Error checking for variable step wiggle file: %s\n"
        "error message is %s\n",
        reader->filename, 
        error_message
      );
    }
  }

  if (reader->format == FIXED_WIGGLE_FMT) {
    const int CHROM_GROUP = 1;
    int len = matches[CHROM_GROUP].rm_eo - matches[CHROM_GROUP].rm_so;
    catch_match_too_long(len, line, reader->filename);
    myfree(reader->chrom);
    reader->chrom = mm_malloc(len + 1);
    char *last 
      = strncpy(reader->chrom, line + matches[CHROM_GROUP].rm_so, len) + len;
    *last = 0; // Terminate string
    const int START_GROUP = 2;
    len = matches[START_GROUP].rm_eo - matches[START_GROUP].rm_so;
    catch_match_too_long(len, line, reader->filename);
    last = strncpy(buffer, line + matches[START_GROUP].rm_so, len) + len;
    *last = 0; // Terminate string
    reader->start = strtod(buffer, NULL);
    const int STEP_GROUP = 3;
    len = matches[STEP_GROUP].rm_eo - matches[STEP_GROUP].rm_so;
    catch_match_too_long(len, line, reader->filename);
    last = strncpy(buffer, line + matches[STEP_GROUP].rm_so, len) + len;
    *last = 0; // Terminate string
    reader->step = strtod(buffer, NULL);
    // Optional match, may not be present
    const int SPAN_GROUP = 5;
    len = matches[SPAN_GROUP].rm_eo - matches[SPAN_GROUP].rm_so;
    if (len > 0) {
      catch_match_too_long(len, line, reader->filename);
      last = strncpy(buffer, line + matches[SPAN_GROUP].rm_so, len) + len;
      *last = 0; // Terminate string
      reader->span = strtod(buffer, NULL);
    }
  }
  else if (reader->format == VAR_WIGGLE_FMT) {
    const int CHROM_GROUP = 1;
    int len = matches[CHROM_GROUP].rm_eo - matches[CHROM_GROUP].rm_so;
    catch_match_too_long(len, line, reader->filename);
    // Check if chromosome has changed since last call.
    if (reader->chrom == NULL 
        || strncmp(reader->chrom, line + matches[CHROM_GROUP].rm_so, len) != 0) {
      myfree(reader->chrom);
      reader->chrom = mm_malloc(len + 1);
    }
    char *last 
      = strncpy(reader->chrom, line + matches[CHROM_GROUP].rm_so, len) + len;
    *last = 0; // Terminate string
    // Optional match, may not be present
    const int SPAN_GROUP = 3;
    len = matches[SPAN_GROUP].rm_eo - matches[SPAN_GROUP].rm_so;
    if (len > 0) {
      catch_match_too_long(len, line, reader->filename);
      last = strncpy(buffer, line + matches[SPAN_GROUP].rm_so, len) + len;
      *last = 0; // Terminate string
      reader->span = strtod(buffer, NULL);
    }
  }
  else {
    die(
      "Unable to determine type of wiggle format in %s.\n",
      reader->filename
    );
  }
}