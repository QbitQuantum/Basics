/** \brief parse configuration file.
*
* \param[in,out] as Pointer to session handle
* \param[in] filename Path to the configuration file
* \return 0 if parsing was successful, -1 if an error occured.
*/
int parse_config_file(struct auto_handle *as, const char *filename) {
  FILE *fp = NULL;
  char *line = NULL;
  char opt[MAX_OPT_LEN + 1];
  char *param = NULL;
  char erbuf[100];
  char c;		/* for the "" and '' check */
  int line_num = 0;
  int line_pos;	/* line pos */
  int opt_pos;	/* opt pos */
  int param_pos;	/* param pos */
  int parse_error = 0;
  int opt_good = 0;
  int param_good = 0;
  struct stat fs;
  option_type type;

  if(stat(filename, &fs) == -1)  {
    return -1;
  }
  dbg_printf(P_INFO2, "Configuration file size: %d", fs.st_size);

  if ((fp = fopen(filename, "rb")) == NULL) {
    perror("fopen");
    return -1;
  }

  if ((line = am_malloc(fs.st_size + 1)) == NULL) {
    dbg_printf(P_ERROR, "Can't allocate memory for 'line': %s (%ldb)", strerror(errno), fs.st_size + 1);
    return -1;
  }

  if(fread(line, fs.st_size, 1, fp) != 1) {
    perror("fread");
    fclose(fp);
    am_free(line);
    return -1;
  }
  if(fp) {
    fclose(fp);
  }
  line_pos = 0;

  param = (char*)am_malloc(MAX_PARAM_LEN + 1);
  if(!param) {
    dbg_printf(P_ERROR, "Can't allocate memory for 'param': %s (%ldb)", strerror(errno), MAX_PARAM_LEN + 1);
    am_free(line);
    return -1;
  }

  while(line_pos != fs.st_size) {
    /* skip whitespaces */
    while (isspace(line[line_pos])) {
      if(line[line_pos] == '\n') {
        dbg_printf(P_INFO2, "skipping newline (line %d)", line_num);
        line_num++;
      }
      ++line_pos;
    }

    if(line_pos >= fs.st_size) {
      break;
    }

    /* comment */
    if (line[line_pos] == '#') {
      dbg_printf(P_INFO2, "skipping comment (line %d)", line_num);
      while (line[line_pos] != '\n') {
        ++line_pos;
      }
      ++line_num;
      ++line_pos;  /* skip the newline as well */
      continue;
    }

    /* read option */
    for (opt_pos = 0; isprint(line[line_pos]) && line[line_pos] != ' ' &&
      line[line_pos] != '#' && line[line_pos] != '='; /* NOTHING */) {
        opt[opt_pos++] = line[line_pos++];
        if (opt_pos >= MAX_OPT_LEN) {
          dbg_printf(P_ERROR, "too long option at line %d", line_num);
          parse_error = 1;
          opt_good = 0;
        }
    }
    if (opt_pos == 0 || parse_error == 1) {
      dbg_printf(P_ERROR, "parse error at line %d (pos: %d)", line_num, line_pos);
      parse_error = 1;
      break;
    } else {
      opt[opt_pos] = '\0';
      opt_good = 1;
    }
    /* skip whitespaces */
    while (isspace(line[line_pos])) {
      if(line[line_pos] == '\n') {
        line_num++;
        dbg_printf(P_INFO2, "skipping newline (line %d)", line_num);
      }
      ++line_pos;
    }

    if(line_pos >= fs.st_size) {
      break;
    }

    /* check for '=' */
    if (line[line_pos++] != '=') {
      snprintf(erbuf, sizeof(erbuf), "Option '%s' needs a parameter (line %d)", opt, line_num);
      parse_error = 1;
      break;
    }

    /* skip whitespaces */
    while (isspace(line[line_pos])) {
      if(line[line_pos] == '\n') {
        line_num++;
        dbg_printf(P_INFO2, "skipping newline (line %d)", line_num);
      }
      ++line_pos;
    }

    if(line_pos >= fs.st_size) {
      break;
    }

    /* read the parameter */

    /* case 1: single string, no linebreaks allowed */
    if (line[line_pos] == '"' || line[line_pos] == '\'') {
      c = line[line_pos]; /* single or double quote */
      ++line_pos;  /* skip quote */
      parse_error = 0;
      for (param_pos = 0; line[line_pos] != c; /* NOTHING */) {
        if(line_pos < fs.st_size && param_pos < MAX_PARAM_LEN && line[line_pos] != '\n') {
          param[param_pos++] = line[line_pos++];
        } else {
          snprintf(erbuf, sizeof(erbuf), "Option %s has a too long parameter (line %d)\n",opt, line_num);
          parse_error = 1;
          break;
        }
      }
      if(parse_error == 0) {
        line_pos++;	/* skip the closing " or ' */
        type = CONF_TYPE_STRING;
      } else {
        break;
      }
      /* case 2: multiple items, linebreaks allowed */
    } else if (line[line_pos] == '{') {
      dbg_printf(P_INFO2, "reading multiline param", line_num);
      ++line_pos;
      parse_error = 0;
      for (param_pos = 0; line[line_pos] != '}'; /* NOTHING */) {
        if(line_pos < fs.st_size && param_pos < MAX_PARAM_LEN) {
          param[param_pos++] = line[line_pos++];
          if(line[line_pos] == '\n')
            line_num++;
        } else {
          snprintf(erbuf, sizeof(erbuf), "Option %s has a too long parameter (line %d)\n", opt, line_num);
          parse_error = 1;
          break;
        }
      }
      dbg_printf(P_INFO2, "multiline param: param_good=%d", param_good);
      if(parse_error == 0) {
        line_pos++;	/* skip the closing '}' */
        type = CONF_TYPE_STRINGLIST;
      } else {
        break;
      }
      /* Case 3: integers */
    } else {
      parse_error = 0;
      for (param_pos = 0; isprint(line[line_pos]) && !isspace(line[line_pos])
        && line[line_pos] != '#'; /* NOTHING */) {
          param[param_pos++] = line[line_pos++];
          if (param_pos >= MAX_PARAM_LEN) {
            snprintf(erbuf, sizeof(erbuf), "Option %s has a too long parameter (line %d)\n", opt, line_num);
            parse_error = 1;
            break;
          }
      }
      if(parse_error == 0) {
        type = CONF_TYPE_INT;
      } else {
        break;
      }
    }
    param[param_pos] = '\0';
    dbg_printf(P_INFO2, "[parse_config_file] option: %s", opt);
    dbg_printf(P_INFO2, "[parse_config_file] param: %s (%d byte)", param, strlen(param));
    dbg_printf(P_INFO2, "[parse_config_file] -----------------");
    set_option(as, opt, param, type);

    /* skip whitespaces */
    while (isspace(line[line_pos])) {
      if(line[line_pos] == '\n')
        line_num++;
      ++line_pos;
    }
    if(line_pos >= fs.st_size) {
      break;
    }
  }

  am_free(line);
  am_free(param);

  return (parse_error == 1) ? -1 : 0;
}