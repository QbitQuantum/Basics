static NEOERR* _hdf_read_string (HDF *hdf, const char **str, STRING *line,
                                 const char *path, int *lineno,
                                 int include_handle, int expect_end_brace) {
  NEOERR *err;
  HDF *lower;
  char *s;
  char *name, *value;
  HDF_ATTR *attr = NULL;

  while (**str != '\0')
  {
    /* Reset string length, but don't free the reserved buffer */
    line->len = 0;
    err = _copy_line_advance(str, line);
    if (err) return nerr_pass(err);
    attr = NULL;
    (*lineno)++;
    s = line->buf;
    SKIPWS(s);
    if ((!strncmp(s, "#include ", 9) || !strncmp(s, "-include ", 9)) && include_handle != INCLUDE_IGNORE)
    {
      int required = !strncmp(s, "#include ", 9);
      if (include_handle == INCLUDE_ERROR)
      {
	return nerr_raise (NERR_PARSE,
                           "[%d]: #include not supported in string parse",
                           *lineno);
      }
      else if (include_handle < INCLUDE_MAX_DEPTH)
      {
        int l;
        s += 9;
        name = neos_strip(s);
        l = strlen(name);
        if (name[0] == '"' && name[l-1] == '"')
        {
          name[l-1] = '\0';
          name++;
        }
        char fullpath[PATH_MAX];
        if (name[0] != '/') {
          memset(fullpath, 0, PATH_MAX);

          char *p = strrchr(path, '/');
          if (p == NULL) {
            char pwd[PATH_MAX];
            memset(pwd, 0, PATH_MAX);
            getcwd(pwd, PATH_MAX);
            snprintf(fullpath, PATH_MAX, "%s/%s", pwd, name);
          } else {
            int dir_len = p - path + 1;
            snprintf(fullpath, PATH_MAX, "%s", path);
            snprintf(fullpath + dir_len, PATH_MAX - dir_len, "%s", name);
          }
          name = fullpath;
        }
        err = hdf_read_file_internal(hdf, name, include_handle + 1);
        if (err != STATUS_OK && required)
        {
          return nerr_pass_ctx(err, "In file %s:%d", path, *lineno);
        }
      }
      else {
        return nerr_raise (NERR_MAX_RECURSION,
                           "[%d]: Too many recursion levels.",
                           *lineno
                           );
      }
    }
    else if (s[0] == '#')
    {
      /* comment: pass */
    }
    else if (s[0] == '}') /* up */
    {
      s = neos_strip(s);
      if (strcmp(s, "}"))
      {
        err = nerr_raise(NERR_PARSE,
	    "[%s:%d] Trailing garbage on line following }: %s", path, *lineno,
	    line->buf);
        return err;
      }
      return STATUS_OK;
    }
    else if (s[0])
    {
      /* Valid hdf name is [0-9a-zA-Z_.]+ */
      int splice = *s == '@';
      if (splice) s++;
      name = s;
      while (*s && (isalnum(*s) || *s == '_' || *s == '.' || *s == '*')) s++;
      SKIPWS(s);

      char num[16];
      static int counter = 0;
      if (*name == '*') {
        snprintf(num, sizeof(num), "%d", counter++);
        name = num;
      }

      if (s[0] == '[') /* attributes */
      {
	*s = '\0';
	name = neos_strip(name);
	s++;
	err = parse_attr(&s, &attr);
	if (err)
        {
          return nerr_pass_ctx(err, "In file %s:%d", path, *lineno);
        }
	SKIPWS(s);
      }
      if (splice) {
        name = neos_strip(name);
        HDF *h = hdf_get_obj(hdf->top, name);
        if (h) {
          HDF *c = hdf_obj_child(h);
          while (c) {
            err = hdf_copy (hdf, hdf_obj_name(c), c);
            if (err != STATUS_OK) break;
            c = hdf_obj_next(c);
          }
        }
	if (err != STATUS_OK)
        {
          return nerr_pass_ctx(err, "In file %s:%d", path, *lineno);
        }
      } else if (s[0] == '=') /* assignment */
      {
	*s = '\0';
	name = neos_strip(name);
	s++;
	value = neos_strip(s);
	err = _set_value (hdf, name, value, 1, 1, 0, attr, NULL);
	if (err != STATUS_OK)
        {
          return nerr_pass_ctx(err, "In file %s:%d", path, *lineno);
        }
      }
      else if (s[0] == ':' && s[1] == '=') /* copy */
      {
	*s = '\0';
	name = neos_strip(name);
	s+=2;
	value = neos_strip(s);
        HDF *h = hdf_get_obj(hdf->top, value);
        if (!h)
        {
	  err = nerr_raise(NERR_PARSE,
                           "[%s:%d] Failed to copy a node that is not loaded "
                           "yet: %s", path, *lineno, value);
          return err;
        }
        err = hdf_copy(hdf, name, h);
	if (err != STATUS_OK)
        {
          return nerr_pass_ctx(err, "In file %s:%d", path, *lineno);
        }
      }
      else if (s[0] == '!' && s[1] == '=') /* exec */
      {
	*s = '\0';
	name = neos_strip(name);
	s+=2;
	value = neos_strip(s);

        FILE *f = popen(value, "r");
	if (f == NULL)
        {
	  err = nerr_raise(NERR_PARSE,
                           "[%s:%d] Failed to exec specified command: %s",
                           path, *lineno, line->buf);
          return err;
        }
        char *content = _read_file(f);
        fclose(f);
        int len = strlen(content);
        if (len > 0 && content[len - 1] == '\n') {
          content[len - 1] = '\0'; // remove \n artifact
        }
	err = _set_value (hdf, name, content, 1, 1, 0, attr, NULL);
        free(content);

	if (err != STATUS_OK)
        {
          return nerr_pass_ctx(err, "In file %s:%d", path, *lineno);
        }
      }
      else if (s[0] == ':') /* link */
      {
	*s = '\0';
	name = neos_strip(name);
	s++;
	value = neos_strip(s);
	err = _set_value (hdf, name, value, 1, 1, 1, attr, NULL);
	if (err != STATUS_OK)
        {
          return nerr_pass_ctx(err, "In file %s:%d", path, *lineno);
        }
      }
      else if (s[0] == '{') /* deeper */
      {
	*s = '\0';
	name = neos_strip(name);
	lower = hdf_get_obj (hdf, name);
	if (lower == NULL)
	{
	  err = _set_value (hdf, name, NULL, 1, 1, 0, attr, &lower);
	}
	else
	{
	  err = _set_value (lower, NULL, lower->value, 1, 1, 0, attr, NULL);
	}
	if (err != STATUS_OK)
        {
          return nerr_pass_ctx(err, "In file %s:%d", path, *lineno);
        }
	err = _hdf_read_string (lower, str, line, path, lineno, include_handle,
                                1);
	if (err != STATUS_OK)
        {
          return nerr_pass_ctx(err, "In file %s:%d", path, *lineno);
        }
      }
      else if (s[0] == '<' && s[1] == '<') /* multi-line assignment */
      {
	char *m;
	int msize = 0;
	int mmax = 128;
	int l;

	*s = '\0';
	name = neos_strip(name);
	s+=2;
	value = neos_strip(s);
	l = strlen(value);
	if (l == 0)
        {
	  err = nerr_raise(NERR_PARSE,
	      "[%s:%d] No multi-assignment terminator given: %s", path, *lineno,
	      line->buf);
          return err;
        }
	m = (char *) malloc (mmax * sizeof(char));
	if (m == NULL)
        {
	  return nerr_raise(NERR_NOMEM,
	    "[%s:%d] Unable to allocate memory for multi-line assignment to %s",
	    path, *lineno, name);
        }
	while (_copy_line (str, m+msize, mmax-msize) != 0)
	{
          (*lineno)++;
	  if (!strncmp(value, m+msize, l) && isspace(m[msize+l]))
	  {
	    m[msize] = '\0';
	    break;
	  }
	  msize += strlen(m+msize);
	  if (msize + l + 10 > mmax)
	  {
	    void *new_ptr;
	    mmax += 128;
	    new_ptr = realloc (m, mmax * sizeof(char));
	    if (new_ptr == NULL)
	    {
        free(m);
	      return nerr_raise(NERR_NOMEM,
		  "[%s:%d] Unable to allocate memory for multi-line assignment to %s: size=%d",
		  path, *lineno, name, mmax);
      }
      m = (char *) new_ptr;
	  }
	}
	err = _set_value (hdf, name, m, 0, 1, 0, attr, NULL);
	if (err != STATUS_OK)
	{
	  free (m);
          return nerr_pass_ctx(err, "In file %s:%d", path, *lineno);
	}

      }
      else
      {
	err = nerr_raise(NERR_PARSE, "[%s:%d] Unable to parse line %s", path,
	    *lineno, line->buf);
        return err;
      }
    }
  }
  if (expect_end_brace) {
    err = nerr_raise(NERR_PARSE, "[%s:%d] Missing matching }", path, *lineno);
    return err;
  }
  return STATUS_OK;
}