mrb_debug_bptype
parse_breakcommand(mrdb_state *mrdb, const char **file, uint32_t *line, char **cname, char **method)
{
  mrb_debug_context *dbg = mrdb->dbg;
  char *args;
  char *body;
  mrb_debug_bptype type;
  uint32_t l;

  if(mrdb->wcnt <= 1) {
    puts(BREAK_ERR_MSG_BLANK);
    return MRB_DEBUG_BPTYPE_NONE;
  }

  args = mrdb->words[1];
  if((body = strrchr(args, ':')) == NULL) {
    body = args;
    type = check_bptype(body);
  } else {
    if(body == args) {
      printf(BREAK_ERR_MSG_INVALIDSTR, args);
      return MRB_DEBUG_BPTYPE_NONE;
    }
    *body = '\0';
    type = check_bptype(++body);
  }

  switch(type) {
    case MRB_DEBUG_BPTYPE_LINE:
      STRTOUL(l, body);
      if( l <= 65535 ) {
        *line = l;
        *file = (body == args)? mrb_debug_get_filename(dbg->irep, (uint32_t)(dbg->pc - dbg->irep->iseq)): args;
      } else {
        puts(BREAK_ERR_MSG_RANGEOVER);
        type = MRB_DEBUG_BPTYPE_NONE;
      }
      break;
    case MRB_DEBUG_BPTYPE_METHOD:
      if(body == args) {
        /* method only */
        if( ISUPPER(*body)||ISLOWER(*body)||(*body == '_') ) {
          *method = body;
          *cname = NULL;
        } else {
          printf(BREAK_ERR_MSG_INVALIDMETHOD, args);
          type = MRB_DEBUG_BPTYPE_NONE;
        }
      } else {
        if( ISUPPER(*args) ) {
          switch(*body) {
            case '@': case '$': case '?': case '.': case ',': case ':':
            case ';': case '#': case '\\': case '\'': case '\"':
            printf(BREAK_ERR_MSG_INVALIDMETHOD, body);
            type = MRB_DEBUG_BPTYPE_NONE;
            break;
          default:
            *method = body;
            *cname = args;
            break;
          }
        } else {
          printf(BREAK_ERR_MSG_INVALIDCLASS, args);
          type = MRB_DEBUG_BPTYPE_NONE;
        }
      }
      break;
    case MRB_DEBUG_BPTYPE_NONE:
    default:
      break;
  }

  return type;
}