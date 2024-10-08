int main(int argc,char **argv)
{
  FILE *fptr;
  struct stat statbuf;
  char *cpt;
  int chara;
  unsigned int linelen;
  unsigned int searchlen;
  unsigned int line_no;
  int first_line_no;
  bool put_title;
  unsigned int tries;
  unsigned int m;
  unsigned int n;
  unsigned int p;
  bool case_sens;
  int curr_arg;
  bool show_title;
  bool line_numbers;
  unsigned int string_arg;
  bool show_search_string;
  bool put_search_string;
  bool reverse;
  bool put_line;
  bool bStdin;
  bool ss_specified;
  bool t_specified;
  bool l_specified;
  bool bHex;
  bool bChop;
  unsigned int chop;
  bool bOffset;
  int nibbles[2];
  int which_nib;
  unsigned int num_special_chars;
  int bDateTime;
  int bWindow;
  int window;
  int bDebug;
  int last_grepped_line;
  struct pair special_chars[MAX_SPECIAL_CHARS];
  char buf[3];

  case_sens = false;
  ss_specified = false;
  t_specified = false;
  l_specified = false;
  reverse = false;
  bHex = false;
  bChop = false;
  bOffset = false;
  num_special_chars = 0;
  bDateTime = false;
  bWindow = false;
  bDebug = false;

  for (curr_arg = 1; curr_arg < argc; curr_arg++) {
    if (argv[curr_arg][0] != '-')
      break;

    if (!strcmp(argv[curr_arg],"-c"))
      case_sens = true;
    else if (!strcmp(argv[curr_arg],"-ss")) {
      show_search_string = true;
      ss_specified = true;
    }
    else if (!strcmp(argv[curr_arg],"-t")) {
      show_title = true;
      t_specified = true;
    }
    else if (!strcmp(argv[curr_arg],"-l")) {
      line_numbers = true;
      l_specified = true;
    }
    else if (!strcmp(argv[curr_arg],"-nss")) {
      show_search_string = false;
      ss_specified = true;
    }
    else if (!strcmp(argv[curr_arg],"-nt")) {
      show_title = false;
      t_specified = true;
    }
    else if (!strcmp(argv[curr_arg],"-nl")) {
      line_numbers = false;
      l_specified = true;
    }
    else if (!strcmp(argv[curr_arg],"-rev"))
      reverse = true;
    else if (!strcmp(argv[curr_arg],"-hex"))
      bHex = true;
    else if (!strncmp(argv[curr_arg],"-chop",5)) {
      bChop = true;
      sscanf(&argv[curr_arg][5],"%u",&chop);
    }
    else if (!strcmp(argv[curr_arg],"-off")) {
      bOffset = true;
      line_numbers = false;
      l_specified = true;
    }
    else if (!strncmp(argv[curr_arg],"-special_char",13)) {
      if (num_special_chars == MAX_SPECIAL_CHARS) {
        printf("num_special_chars may not exceed %d\n",MAX_SPECIAL_CHARS);
        return 1;
      }

      buf[0] = argv[curr_arg][13];
      buf[1] = argv[curr_arg][14];
      buf[2] = 0;

      sscanf(buf,"%x",&special_chars[num_special_chars].val1);
      sscanf(&argv[curr_arg][15],"%c",&special_chars[num_special_chars++].val2);
    }
    else if (!strcmp(argv[curr_arg],"-datetime"))
      bDateTime = true;
    else if (!strncmp(argv[curr_arg],"-window",7)) {
      bWindow = true;
      sscanf(&argv[curr_arg][7],"%u",&window);
    }
    else if (!strcmp(argv[curr_arg],"-dbg"))
      bDebug = true;
    else
      break;
  }

  if (curr_arg == argc) {
    printf(usage);
    return 2;
  }

  string_arg = curr_arg;

  if (bHex) {
    case_sens = true;
    searchlen = strlen(argv[string_arg]);

    if (searchlen % 2) {
      printf("hex string must have an even number of hex digits\n");
      return 3;
    }

    m = 0;

    for (n = 0; n < searchlen; n++) {
      which_nib = n % 2;

      if ((nibbles[which_nib] = get_nib(argv[string_arg][n])) == -1) {
        printf("illegal hex string\n");
        return 4;
      }

      if (which_nib)
        argv[string_arg][m++] = (nibbles[0] << 4) + nibbles[1];
    }

    argv[string_arg][m] = 0;
  }
  else if (num_special_chars || !case_sens) {
    for (n = 0; (chara = argv[string_arg][n]); n++) {
      for (p = 0; p < num_special_chars; p++) {
        if (chara == special_chars[p].val2) {
          argv[string_arg][n] = (char)special_chars[p].val1;
          break;
        }
      }

      if (!case_sens) {
        if ((chara >= 'A') && (chara <= 'Z'))
          argv[string_arg][n] = (char)(chara - 'A' + 'a');
      }
    }
  }

  searchlen = strlen(argv[string_arg]);

  if (!strcmp(argv[string_arg],"doublequote")) {
    argv[string_arg][0] = '"';
    searchlen = 1;
  }

  curr_arg++;

  if (curr_arg == argc) {
    bStdin = true;

    if (!ss_specified)
      show_search_string = false;

    /*if (!t_specified)*/
      show_title = false;

    if (!l_specified)
      line_numbers = false;
  }
  else {
    if (argc - curr_arg == 1) {
      /* if wildcard expansion failed, exit with no error message */
      for (n = 0; (chara = argv[curr_arg][n]); n++) {
        if (chara == '*')
          return 5;
      }
    }

    bStdin = false;

    if (!ss_specified) {
      if (argc - string_arg > 2)
        show_search_string = true;
      else
        show_search_string = false;
    }

    if (!t_specified) {
      if (argc - string_arg > 2)
        show_title = true;
      else
        show_title = false;
    }

    if (!l_specified)
      line_numbers = true;
  }

  if ((line = (char *)malloc(MAX_LINE_LEN)) == NULL) {
    printf("malloc of %u bytes failed\n",MAX_LINE_LEN);
    return 6;
  }

  if (show_search_string)
    put_search_string = false;

  /* start of argument loop: */
  for ( ; ; ) {

  if (bStdin)
    fptr = stdin;
  else {
    if ((fptr = fopen(argv[curr_arg],"r")) == NULL) {
      printf(couldnt_open,argv[curr_arg]);
      curr_arg++;

      if (curr_arg == argc)
        break;

      continue;
    }

    if (stat(argv[curr_arg],&statbuf)) {
      printf(couldnt_get_status,argv[curr_arg]);
      curr_arg++;

      if (curr_arg == argc)
        break;

      continue;
    }
  }

  if (show_title)
    put_title = false;

  if (bOffset)
    first_line_no = -1;

  line_no = 0;
  last_grepped_line = -1;

  for ( ; ; ) {
    GetLine(fptr,line,&linelen,MAX_LINE_LEN);

    if (feof(fptr)) {
      if (!bStdin) {
        if (show_title && put_title)
          putchar(0x0a);

        fclose(fptr);
      }

      break;
    }

    line_no++;

    if (bDebug)
      printf(dbg_fmt_str,line_no,line);

    put_line = false;

    if (linelen < searchlen) {
      if (reverse)
        put_line = true;
    }
    else {
      tries = linelen - searchlen + 1;

      for (m = 0; m < tries; m++) {
        for (n = 0; n < searchlen; n++) {
          chara = line[m+n];

          if (!case_sens)
            if ((chara >= 'A') && (chara <= 'Z'))
              chara -= 'A' - 'a';

          if (chara != argv[string_arg][n])
            break;
        }

        if (n == searchlen)
          break;
      }

      if (n == searchlen) {
        if (!reverse)
          put_line = true;
      }
      else if (reverse)
        put_line = true;
    }

    if (put_line && bWindow)
      last_grepped_line = line_no;

    if (bWindow && (last_grepped_line != -1)) {
      if (line_no < last_grepped_line + window)
        put_line = 1;
    }

    if (put_line) {
      if (show_search_string) {
        if (!put_search_string) {
          printf("search string: %s\n\n",argv[string_arg]);
          put_search_string = true;
        }
      }

      if (show_title) {
        if (!put_title) {
          if (bDateTime) {
            cpt = ctime(&statbuf.st_mtime);
            cpt[strlen(cpt) - 1] = 0;
            sprintf(exp_title,"%s %s",cpt,argv[curr_arg]);
          }
          else
            strcpy(exp_title,argv[curr_arg]);

          printf("%s\n",exp_title);

          for (n = strlen(exp_title); (n); n--)
            putchar('=');

          putchar(0x0a);

          put_title = true;
        }
      }

      if (bChop)
        line[chop] = 0;

      if (line_numbers)
        printf(fmt_str,line_no,line);
      else if (bOffset) {
        if (first_line_no == -1) {
          printf(fmt_str,0,line);
          first_line_no = line_no;
        }
        else
          printf(fmt_str,line_no - first_line_no,line);
      }
      else
        printf("%s\n",line);
    }
  }

  if (bStdin)
    break;
  else {
    curr_arg++;

    if (curr_arg == argc)
      break;
  }

  /* end of argument loop: */
  }

  free(line);

  return 0;
}