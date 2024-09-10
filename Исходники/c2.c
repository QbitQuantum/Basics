/**
 * Parse the pattern part of a leaf.
 */
static int
c2_parse_pattern(session_t *ps, const char *pattern, int offset, c2_ptr_t *presult) {
  c2_l_t * const pleaf = presult->l;

  // Exists operator cannot have pattern
  if (!pleaf->op)
    return offset;

  C2H_SKIP_SPACES();

  char *endptr = NULL;
  // Check for boolean patterns
  if (!strcmp_wd("true", &pattern[offset])) {
    pleaf->ptntype = C2_L_PTINT;
    pleaf->ptnint = true;
    offset += strlen("true");
  }
  else if (!strcmp_wd("false", &pattern[offset])) {
    pleaf->ptntype = C2_L_PTINT;
    pleaf->ptnint = false;
    offset += strlen("false");
  }
  // Check for integer patterns
  else if (pleaf->ptnint = strtol(pattern + offset, &endptr, 0),
      pattern + offset != endptr) {
    pleaf->ptntype = C2_L_PTINT;
    offset = endptr - pattern;
    // Make sure we are stopping at the end of a word
    if (isalnum(pattern[offset]))
      c2_error("Trailing characters after a numeric pattern.");
  }
  // Check for string patterns
  else {
    bool raw = false;
    char delim = '\0';

    // String flags
    if ('r' == tolower(pattern[offset])) {
      raw = true;
      ++offset;
      C2H_SKIP_SPACES();
    }

    // Check for delimiters
    if ('\"' == pattern[offset] || '\'' == pattern[offset]) {
      pleaf->ptntype = C2_L_PTSTRING;
      delim = pattern[offset];
      ++offset;
    }

    if (C2_L_PTSTRING != pleaf->ptntype)
      c2_error("Invalid pattern type.");

    // Parse the string now
    // We can't determine the length of the pattern, so we use the length
    // to the end of the pattern string -- currently escape sequences
    // cannot be converted to a string longer than itself.
    char *tptnstr = malloc((strlen(pattern + offset) + 1) * sizeof(char));
    char *ptptnstr = tptnstr;
    pleaf->ptnstr = tptnstr;
    for (; pattern[offset] && delim != pattern[offset]; ++offset) {
      // Handle escape sequences if it's not a raw string
      if ('\\' == pattern[offset] && !raw) {
        switch(pattern[++offset]) {
          case '\\':  *(ptptnstr++) = '\\'; break;
          case '\'':  *(ptptnstr++) = '\''; break;
          case '\"':  *(ptptnstr++) = '\"'; break;
          case 'a':   *(ptptnstr++) = '\a'; break;
          case 'b':   *(ptptnstr++) = '\b'; break;
          case 'f':   *(ptptnstr++) = '\f'; break;
          case 'n':   *(ptptnstr++) = '\n'; break;
          case 'r':   *(ptptnstr++) = '\r'; break;
          case 't':   *(ptptnstr++) = '\t'; break;
          case 'v':   *(ptptnstr++) = '\v'; break;
          case 'o':
          case 'x':
                      {
                        char *tstr = mstrncpy(pattern + offset + 1, 2);
                        char *pstr = NULL;
                        long val = strtol(tstr, &pstr,
                            ('o' == pattern[offset] ? 8: 16));
                        free(tstr);
                        if (pstr != &tstr[2] || val <= 0)
                          c2_error("Invalid octal/hex escape sequence.");
                        assert(val < 256 && val >= 0);
                        *(ptptnstr++) = val;
                        offset += 2;
                        break;
                      }
          default:   c2_error("Invalid escape sequence.");
        }
      }
      else {
        *(ptptnstr++) = pattern[offset];
      }
    }
    if (!pattern[offset])
      c2_error("Premature end of pattern string.");
    ++offset;
    *ptptnstr = '\0';
    pleaf->ptnstr = mstrcpy(tptnstr);
    free(tptnstr);
  }

  C2H_SKIP_SPACES();

  if (!pleaf->ptntype)
    c2_error("Invalid pattern type.");

  // Check if the type is correct
  if (!(((C2_L_TSTRING == pleaf->type
            || C2_L_TATOM == pleaf->type)
          && C2_L_PTSTRING == pleaf->ptntype)
        || ((C2_L_TCARDINAL == pleaf->type
            || C2_L_TWINDOW == pleaf->type
            || C2_L_TDRAWABLE == pleaf->type)
          && C2_L_PTINT == pleaf->ptntype)))
    c2_error("Pattern type incompatible with target type.");

  if (C2_L_PTINT == pleaf->ptntype && pleaf->match)
    c2_error("Integer/boolean pattern cannot have operator qualifiers.");

  if (C2_L_PTINT == pleaf->ptntype && pleaf->match_ignorecase)
    c2_error("Integer/boolean pattern cannot have flags.");

  if (C2_L_PTSTRING == pleaf->ptntype
      && (C2_L_OGT == pleaf->op || C2_L_OGTEQ == pleaf->op
        || C2_L_OLT == pleaf->op || C2_L_OLTEQ == pleaf->op))
    c2_error("String pattern cannot have an arithmetic operator.");

  return offset;
}