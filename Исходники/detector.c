const char *disambiguate_m(SourceFile *sourcefile) {
  char *p, *pe;
  int length;

  // Attempt to detect based on a weighted heuristic of file contents.
  int matlab_score = 0;
  int objective_c_score = 0;
  int limbo_score = 0;
  int octave_syntax_detected = 0;

  int i, has_h_headers = 0, has_c_files = 0;
  char **filenames = sourcefile->filenames;
  if (filenames) {
    for (i = 0; filenames[i] != NULL; i++) {
      p = filenames[i];
      pe = p + strlen(p);
      if (pe - p >= 4) {
        if (*(pe - 4) == '.' && *(pe - 3) == 'c' &&
            ((*(pe - 2) == 'p' && *(pe - 1) == 'p') ||
             (*(pe - 2) == '+' && *(pe - 1) == '+') ||
             (*(pe - 2) == 'x' && *(pe - 1) == 'x'))) {
          has_c_files = 1;
          break; // short circuit
        }
      } else if (pe - p >= 3) {
        if (*(pe - 3) == '.' && *(pe - 2) == 'c' && *(pe - 1) == 'c') {
          has_c_files = 1;
          break; // short circuit
        }
      } else if (pe - p >= 2) {
        if (*(pe - 2) == '.') {
          if (*(pe - 1) == 'h')
            has_h_headers = 1;
          else if (*(pe - 1) == 'c' || *(pe - 1) == 'C') {
            has_c_files = 1;
            break; // short circuit
          }
        }
      }
    }
  }
  if (has_h_headers && !has_c_files)
    objective_c_score += 5;

  char line[81], buf[81];
  p = ohcount_sourcefile_get_contents(sourcefile);
  pe = p;
  char *eof = p + ohcount_sourcefile_get_contents_size(sourcefile);
  while (pe < eof) {
    // Get a line at a time.
    while (pe < eof && *pe != '\r' && *pe != '\n') pe++;
    length = (pe - p <= sizeof(line)) ? pe - p : sizeof(line);
    strncpy(line, p, length);
    line[length] = '\0';
    char *eol = line + strlen(line);
    char *line_end = pe;

    // Look for tell-tale lines.
    p = line;
    while (*p == ' ' || *p == '\t') p++;
    if (*p == '%') { // Matlab comment
      matlab_score++;
		} else if (*p == '#' && strncmp(p, "#import", 7) == 0) { // Objective C
			objective_c_score++;
    } else if (*p == '#') { // Limbo or Octave comment
      while (*p == '#') p++;
      if (*p == ' ' || *p == '\t') {
        limbo_score++;
        matlab_score++;
        octave_syntax_detected = 1;
      }
    } else if (*p == '/' && *(p + 1) == '/' || *(p + 1) == '*') {
      objective_c_score++; // Objective C comment
    } else if (*p == '+' || *p == '-') { // Objective C method signature
      objective_c_score++;
    } else if (*p == '@' || *p == '#') { // Objective C method signature
      if (strncmp(p, "@implementation", 15) == 0 ||
          strncmp(p, "@interface", 10) == 0)
        objective_c_score++;
    } else if (strncmp(p, "function", 8) == 0) { // Matlab or Octave function
      p += 8;
      while (*p == ' ' || *p == '\t') p++;
      if (*p == '(')
        matlab_score++;
    } else if (strncmp(p, "include", 7) == 0) { // Limbo include
      // /^include[ \t]+"[^"]+\.m";/
      p += 7;
      if (*p == ' ' || *p == '\t') {
        while (*p == ' ' || *p == '\t') p++;
        if (*p == '"') {
          while (*p != '"' && p < eol) p++;
          if (*p == '"' && *(p - 2) == '.' && *(p - 1) == 'm')
            limbo_score++;
        }
      }
    }

    // Look for Octave keywords.
    p = line;
    while (p < eol) {
      if (islower(*p) && p != line && !isalnum(*(p - 1))) {
        pe = p;
        while (islower(*pe) || *pe == '_') pe++;
        if (!isalnum(*pe)) {
          length = pe - p;
          strncpy(buf, p, length);
          buf[length] = '\0';
          if (strcmp(buf, "end_try_catch") == 0 ||
              strcmp(buf, "end_unwind_protect") == 0 ||
              strcmp(buf, "endfunction") == 0 ||
              strcmp(buf, "endwhile") == 0)
            octave_syntax_detected = 1;
        }
        p = pe + 1;
      } else p++;
    }

    // Look for Limbo declarations
    p = line;
    while (p < eol) {
      if (*p == ':' && (*(p + 1) == ' ' || *(p + 1) == '\t')) {
        // /:[ \t]+(module|adt|fn ?\(|con[ \t])/
        p += 2;
        if (strncmp(p, "module", 6) == 0 && !isalnum(*(p + 6)) ||
            strncmp(p, "adt", 3) == 0 && !isalnum(*(p + 3)) ||
            strncmp(p, "fn", 2) == 0 &&
              (*(p + 2) == ' ' && *(p + 3) == '(' || *(p + 2) == '(') ||
            strncmp(p, "con", 3) == 0 &&
              (*(p + 3) == ' ' || *(p + 3) == '\t'))
          limbo_score++;
      } else p++;
    }

    // Next line.
    pe = line_end;
    while (*pe == '\r' || *pe == '\n') pe++;
    p = pe;
  }

  if (limbo_score > objective_c_score && limbo_score > matlab_score)
    return LANG_LIMBO;
  else if (objective_c_score > matlab_score)
    return LANG_OBJECTIVE_C;
  else
    return octave_syntax_detected ? LANG_OCTAVE : LANG_MATLAB;
}