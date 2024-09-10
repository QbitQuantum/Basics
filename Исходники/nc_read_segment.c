size_t NaClReadHexTextWithPc(FILE* file, NaClPcAddress* pc,
                             uint8_t* mbase, size_t mbase_size) {
  char input_line[NACL_MAX_INPUT_LINE];
  *pc = 0;  /* Default if no input. */
  while (1) {
    if (fgets(input_line, NACL_MAX_INPUT_LINE, file) == NULL) return 0;
    if (input_line[0] == '#') {
      /* i.e. treat line as a comment. */
      continue;
    } else if (input_line[0] == '@') {
      *pc = (NaClPcAddress) STRTOULL(&input_line[1], NULL, 16);
    } else {
      return NaClReadHexData(file, mbase, mbase_size, input_line);
    }
  }
  /* NOT REACHED */
  return 0;
}