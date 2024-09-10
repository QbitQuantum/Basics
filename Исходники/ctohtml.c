void convert_file(char *source_filename) {
  char html_filename[NAME_MAX + 1];
  char *relative_filename;
  char *base_filename;
  char *ext, *p;
  int is_c = 0;
  int is_asm = 0;
  FILE *src;
  FILE *out;
  int line_num;
  char line[STRSIZE];
  char filename[STRSIZE];
  char token[STRSIZE];
  char url[STRSIZE];
  int in_comment;
  
  relative_filename = source_filename + source_prefix_len;
  ext = "";
  base_filename = relative_filename;
  p = relative_filename;
  while (*p) {
    if (*p == '/') {
      base_filename = p + 1;
      ext = "";
    }
    if (*p == '.') ext = p;
    p++;
  }
  
  strcpy(html_filename, output_dir);
  strcat(html_filename, "/");
  strcat(html_filename, relative_filename);
  strcat(html_filename, ".html");

  if (strcmp(ext, ".c") == 0) is_c = 1;
  if (strcmp(ext, ".h") == 0) is_c = 1;
  if (strcmp(ext, ".cpp") == 0) is_c = 1;
  if (strcmp(ext, ".asm") == 0) is_asm = 1;
  if (strcmp(ext, ".s") == 0) is_asm = 1;

  if (!is_c && !is_asm) return;
  
  src = fopen(source_filename, "rt");
  if (!src) {
    perror(source_filename);
    return;
  }
  
  out = fopen(html_filename, "wb");
  if (!out) {
    perror(html_filename);
    return;
  }

  fprintf(out, "<html>\r\n");
  fprintf(out, "<head>\r\n");
  fprintf(out, "<title>%s - %s</title>\r\n", base_filename, title);
  fprintf(out, "<style type='text/css'>\r\n");
  fprintf(out, "a:link {text-decoration: none; color:inherit}\r\n");
  fprintf(out, "a:visited {text-decoration: none; color:inherit}\r\n");
  fprintf(out, "a:active {text-decoration: none; color:inherit}\r\n");
  fprintf(out, "</style>\r\n");
  fprintf(out, "</head>\r\n");
  fprintf(out, "<body>\r\n");
  if (source_index) {
    fprintf(out, "<p style='float: right'><a href='/sanos/source/index.html'>Goto sanos source index</a></p>");
  }
  fprintf(out, "<pre>\r\n");
  
  line_num = 1;
  in_comment = 0;
  while (fgets(line, sizeof line, src)) {
    char *p = line;
    char *end = line;
    while (*end && *end != '\r' && *end != '\n') end++;
    *end = 0;
    
    if (in_comment) {
      char *comment_start = p;
      fprintf(out, "<font color='green'>");
      while (p < end) {
        if (p[0] == '*' && p[1] == '/') {
          p += 2;
          output_html(out, comment_start, p);
          in_comment = 0;
          fprintf(out, "</font>");
          break;
        }
        p++;
      }
    }

    fprintf(out, "<a name=':%d'></a>", line_num);
    
    if (!is_c) {
      output_html(out, p, end);
      p = end;
    }

    while (p < end) {
      if (p[0] == '/' && p[1] == '/') {
        fprintf(out, "<font color='green'>");
        output_html(out, p, end);
        fprintf(out, "</font>");
        p = end;
      } else if (p[0] == '/' && p[1] == '*') {
        char *comment_start = p;
        fprintf(out, "<font color='green'>");
        while (p < end) {
          if (p[0] == '*' && p[1] == '/') {
            p += 2;
            output_html(out, comment_start, p);
            in_comment = 0;
            fprintf(out, "</font>");
            break;
          }
          p++;
        }
      } else if (*p == '\'' || *p == '"') {
        char *start = p++;
        while (*p && *p != *start) {
          if (*p == '\\' && *(p + 1)) p++;
          p++;
        }
        if (*p) p++;
        fprintf(out, "<font color='brown'>");
        output_html(out, start, p);
        fprintf(out, "</font>");
      } else if (*p == '#' || *p == '_' || isalpha(*p)) {
        char *start = p++;
        while (*p && (*p == '_' || isalnum(*p))) p++;
        memcpy(token, start, p - start);
        token[p - start] = 0;
        if (is_keyword(token)) {
          fprintf(out, "<font color='blue'>");
          output_html(out, start, p);
          fprintf(out, "</font>");
          
          if (strncmp(start, "#include", 8) == 0) {
            start = p;
            while (isspace(*p)) p++;
            output_html(out, start, p);
            
            if (*p == '"' || *p == '<') {
              int stdincl = *p == '<';
              output_html(out, p, p + 1);
              start = ++p;
              while (*p && *p != '>' && *p != '"') p++;
              if (stdincl) {
                char *base;
                
                strcpy(filename, include_dir);
                strcat(filename, "/");
                base = filename + strlen(filename);
                memcpy(base, start, p - start);
                base[p - start] = 0;
              } else {
                int pathlen = base_filename - relative_filename;
                int fnlen = p - start;
                memcpy(filename, relative_filename, pathlen);
                memcpy(filename + pathlen, start, fnlen);
                filename[pathlen + fnlen] = 0;
              }
              relative_url(relative_filename, filename, url);
              fprintf(out, "<a href='%s.html'>", url);
              output_html(out, start, p);
              fprintf(out, "</a>");
              if (*p) {
                output_html(out, p, p + 1);
                p++;
              }
            }
          }
        } else {
          struct tag *tag = find_tag(token, relative_filename);
          if (tag) {
            int self;
            
            relative_url(relative_filename, tag->file, url);
            self = strcmp(url, base_filename) == 0 && tag->line == line_num;
            if (!self) fprintf(out, "<a href='%s.html#:%d'>", url, tag->line);
            output_html(out, start, p);
            if (!self) fprintf(out, "</a>");
          } else {
            output_html(out, start, p);
          }
        }
      } else {
        output_html(out, p, p + 1);
        p++;
      }
    }
    if (in_comment) fprintf(out, "</font>");
    fprintf(out, "\r\n", line);
    line_num++;
  }
  
  fprintf(out, "</pre>\r\n");
  fprintf(out, "</body>\r\n");
  fprintf(out, "</html>\r\n");

  fclose(src);
  fclose(out);
}