//// ini_parse() ////
void ini_parse(const ini_cfg_t* cfg)
{
  char line[INI_LINE_SIZE] = {0};
  int section = INI_SECTION_INVALID_ID;
  int line_status;

  // open ini file
  #ifdef INI_PARSER_TEST
  if ((ini_fp = fopen(cfg->filename, "rb")) == NULL) { 
  #else
  if (!RAOpen(&ini_file, cfg->filename)) {
  #endif
    ini_parser_debugf("Can't open file %s !", cfg->filename);
    return;
  }

  #ifdef INI_PARSER_TEST
  // save size
  fseek(ini_fp, 0L, SEEK_END);
  ini_size = ftell(ini_fp);
  fseek(ini_fp, 0L, SEEK_SET);
  #endif

  #ifdef INI_PARSER_TEST
  ini_parser_debugf("Opened file %s with size %d bytes.", cfg->filename, ini_size);
  #else
  ini_parser_debugf("Opened file %s with size %d bytes.", cfg->filename, ini_file.file.size);
  #endif

  // preload buffer
  #ifdef INI_PARSER_TEST
  fread(sector_buffer, sizeof(char), INI_BUF_SIZE, ini_fp);
  #else
  RARead(&ini_file, sector_buffer, INI_BUF_SIZE);
  #endif

  // parse ini
  while (1) {
    // get line
    line_status = ini_getline(line);
    // if valid line
    if (line_status != 1) {
      if (line[0] == INI_SECTION_START) {
        // if first char in line is INI_SECTION_START, get section
        section = ini_get_section(cfg, line);
      } else {
        // otherwise this is a variable, get it
        ini_get_var(cfg, section, line);
      }
    }
    // if end of file, stop
    if (line_status == INI_EOT) break;
  }

  #ifdef INI_PARSER_TEST
  // close file
  fclose(ini_fp);
  #endif
}


//// ini_save() ////
void ini_save(const ini_cfg_t* cfg)
{
  int section, var, ini_pt;
  char line[INI_LINE_SIZE] = {0};

  // open ini file
  #ifdef INI_PARSER_TEST
  if ((ini_fp = fopen(cfg->filename, "wb")) == NULL) {
  #else
  { //#error
  #endif
    ini_parser_debugf("Can't open file %s !", cfg->filename);
    return;
  }

  // loop over sections
  for (section=0; section<cfg->nsections; section++) {
    ini_parser_debugf("writing section %s ...", cfg->sections[section].name);
    siprintf(line, "[%s]\n", cfg->sections[section].name);
    ini_pt = ini_putline(line);
    // loop over vars
    for (var=0; var<cfg->nvars; var++) {
      if (cfg->vars[var].section_id == cfg->sections[section].id) {
        ini_parser_debugf("writing var %s", cfg->vars[var].name);
        switch (cfg->vars[var].type) {
          case UINT8:
          case UINT16:
          case UINT32:
            siprintf(line, "%s=%u\n", cfg->vars[var].name, *(uint32_t*)(cfg->vars[var].var));
            break;
          case INT8:
          case INT16:
          case INT32:
            siprintf(line, "%s=%d\n", cfg->vars[var].name, *(int32_t*)(cfg->vars[var].var));
            break;
          #ifdef INI_ENABLE_FLOAT
          case FLOAT:
            siprintf(line, "%s=%f\n", cfg->vars[var].name, *(float*)(cfg->vars[var].var));
            break;
          #endif
          case STRING:
            siprintf(line, "%s=\"%s\"\n", cfg->vars[var].name, (char*)(cfg->vars[var].var));
            break;
        }
        ini_pt = ini_putline(line);
      }
    }
  }

  // in case the buffer is not written yet, write it now
  if (ini_pt) {
    #ifdef INI_PARSER_TEST
    fwrite(sector_buffer, sizeof(char), ini_pt, ini_fp);
    #else
    //#error
    #endif
  }
}