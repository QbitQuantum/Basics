BOOLEAN_T get_next_data_block_from_prior_reader_from_psp(
  DATA_BLOCK_READER_T *reader, 
  DATA_BLOCK_T *data_block
) {

  BOOLEAN_T result = FALSE;
  const int buffer_size = 100;
  char buffer[buffer_size];
  int num_read = 0;

  PSP_DATA_BLOCK_READER_T *psp_reader 
    = (PSP_DATA_BLOCK_READER_T *) get_data_block_reader_data(reader);

  double *output_prior = get_prior_from_data_block(data_block);
  *output_prior = NaN();

  int c = 0;

  // Skip over leading white space
  while((c = fgetc(psp_reader->psp_file)) != EOF) {

    if (isspace(c)) {
      if (c == '\n') {
        psp_reader->at_start_of_line = TRUE;
      }
      else {
        psp_reader->at_start_of_line = FALSE;
      }
      continue;
    }
    else {
      break;
    }
  }

  if (c == '>' && psp_reader->at_start_of_line == TRUE) {
    // We found the start of a new sequence while trying
    // to find a prior.
    c = ungetc(c, psp_reader->psp_file);
    if (ferror(psp_reader->psp_file)) {
      die(
        "Error reading file:%s.\nError message: %s\n", 
        psp_reader->filename,
        strerror(ferror(psp_reader->psp_file))
      );
    }
  }
  else {
    // We are at start of a prior.
    // Read prior string until next space or EOF.
    int buffer_index = 0;
    while(c != EOF && !isspace(c)) {
      buffer[buffer_index] = c;
      ++buffer_index;
      if (buffer_index >= (buffer_size - 1)) {
        // No prior string should be this long
        buffer[buffer_size - 1] = 0;
        die("File %s contains invalid prior value: %s\n", psp_reader->filename, buffer);
      }
      c = fgetc(psp_reader->psp_file);
    }

    if (c == '\n') {
      psp_reader->at_start_of_line = TRUE;
    }
    else {
      psp_reader->at_start_of_line = FALSE;
    }

    buffer[buffer_index] = '\0';

    // If the buffer is not empty, it should contain a string
    // representing the prior. Convert it to a double.
    if (buffer_index != 0) {
      char *end_ptr = NULL;
      double prior = strtod(buffer, &end_ptr);
      if (end_ptr == buffer 
          || *end_ptr != '\0' 
          || prior < 0.0L 
          || prior > 1.0L
      ) {
        die("File %s contains invalid prior value: %s\n", psp_reader->filename, buffer);
      }
      *output_prior = prior;
      num_read = 1;
      ++psp_reader->current_position;
      result = TRUE;
    }

  }

  if (c == EOF && ferror(psp_reader->psp_file)) {
    die(
      "Error while reading file:%s.\nError message: %s\n", 
      psp_reader->filename,
      strerror(ferror(psp_reader->psp_file))
    );
  }

  set_start_pos_for_data_block(data_block, psp_reader->current_position);
  set_num_read_into_data_block(data_block, num_read);
  return result;
}