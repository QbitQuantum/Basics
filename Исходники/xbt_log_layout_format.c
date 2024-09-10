static int xbt_log_layout_format_doit(xbt_log_layout_t l,
                                      xbt_log_event_t ev,
                                      const char *msg_fmt)
{
  char *p = ev->buffer;
  int rem_size = ev->buffer_size;
  int precision = -1;
  int length = -1;
  char *q;

  for (q = l->data ; *q != '\0' ; q++) {
    if (*q == '%') {
      q++;
    handle_modifier:
      switch (*q) {
      case '\0':
        fprintf(stderr, "Layout format (%s) ending with %%\n", (char *)l->data);
        xbt_abort();
      case '%':
        *p = '%';
        check_overflow(1);
        break;
      case 'n':         /* platform-dependant line separator; LOG4J compliant */
        *p = '\n';
        check_overflow(1);
        break;
      case 'e':                 /* plain space; SimGrid extension */
        *p = ' ';
        check_overflow(1);
        break;
      case '.':                 /* precision specifier */
        precision = strtol(q + 1, &q, 10);
        goto handle_modifier;
      case '0':
      case '1':
      case '2':
      case '3':
      case '4':
      case '5':
      case '6':
      case '7':
      case '8':
      case '9':                 /* length modifier */
        length = strtol(q, &q, 10);
        goto handle_modifier;
      case 'c':                 /* category name; LOG4J compliant
                                   should accept a precision postfix to show the
                                   hierarchy */
        show_string(ev->cat->name);
        break;
      case 'p':                 /* priority name; LOG4J compliant */
        show_string(xbt_log_priority_names[ev->priority]);
        break;
      case 'h':                 /* host name; SimGrid extension */
        show_string(SIMIX_host_self_get_name());
        break;
      case 't':                 /* thread name; LOG4J compliant */
        show_string(xbt_thread_self_name());
        break;
      case 'P':                 /* process name; SimGrid extension */
        show_string(xbt_procname());
        break;
      case 'i':                 /* process PID name; SimGrid extension */
        show_int(xbt_getpid());
        break;
      case 'F':                 /* file name; LOG4J compliant */
        show_string(ev->fileName);
        break;
      case 'l': {               /* location; LOG4J compliant */
        int len, sz;
        set_sz_from_precision();
        len = snprintf(p, sz, "%s:%d", ev->fileName, ev->lineNum);
        check_overflow(MIN(sz, len));
        break;
      }
      case 'L':                 /* line number; LOG4J compliant */
        show_int(ev->lineNum);
        break;
      case 'M':                /* method (ie, function) name; LOG4J compliant */
        show_string(ev->functionName);
        break;
      case 'b':                 /* backtrace; called %throwable in LOG4J */
      case 'B':         /* short backtrace; called %throwable{short} in LOG4J */
#if defined(HAVE_EXECINFO_H) && defined(HAVE_POPEN) && defined(ADDR2LINE)
        {
          xbt_ex_t e;

          e.used = backtrace((void **) e.bt, XBT_BACKTRACE_SIZE);
          e.bt_strings = NULL;
          e.msg = NULL;
          xbt_ex_setup_backtrace(&e);
          if (*q == 'B') {
            show_string(e.bt_strings[1] + 8);
          } else {
            xbt_strbuff_t buff = xbt_strbuff_new();
            int i;
            xbt_strbuff_append(buff, e.bt_strings[1] + 8);
            for (i = 2; i < e.used; i++) {
              xbt_strbuff_append(buff, "\n");
              xbt_strbuff_append(buff, e.bt_strings[i] + 8);
            }
            show_string(buff->data);
            xbt_strbuff_free(buff);
          }
          xbt_ex_free(e);
        }
#else
        show_string("(no backtrace on this arch)");
#endif
        break;
      case 'd':                 /* date; LOG4J compliant */
        show_double(surf_get_clock());
        break;
      case 'r':                 /* application age; LOG4J compliant */
        show_double(surf_get_clock() - format_begin_of_time);
        break;
      case 'm': {               /* user-provided message; LOG4J compliant */
        int len, sz;
        set_sz_from_precision();
        len = vsnprintf(p, sz, msg_fmt, ev->ap);
        check_overflow(MIN(sz, len));
        break;
      }
      default:
        fprintf(stderr, ERRMSG, *q, (char *)l->data);
        xbt_abort();
      }
    } else {
      *p = *q;
      check_overflow(1);
    }
  }
  *p = '\0';

  return 1;
}