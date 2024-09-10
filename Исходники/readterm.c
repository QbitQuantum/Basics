static xarg *setReadEnv(Term opts, FEnv *fe, struct renv *re, int inp_stream) {
  CACHE_REGS
  LOCAL_VarTable = NULL;
  LOCAL_AnonVarTable = NULL;
  fe->cmod = CurrentModule;
  fe->enc = GLOBAL_Stream[inp_stream].encoding;
  xarg *args = Yap_ArgListToVector(opts, read_defs, READ_END);
  if (args == NULL) {
    return NULL;
  }

  re->bq = getBackQuotesFlag();
  if (args[READ_MODULE].used) {
    CurrentModule = args[READ_MODULE].tvalue;
  }
  if (args[READ_BACKQUOTED_STRING].used) {
    if (!setBackQuotesFlag(args[READ_BACKQUOTED_STRING].tvalue))
      return false;
  }
  if (args[READ_QUASI_QUOTATIONS].used) {
    fe->qq = args[READ_QUASI_QUOTATIONS].tvalue;
  } else {
    fe->qq = 0;
  }
  if (args[READ_COMMENTS].used) {
    fe->tcomms = args[READ_COMMENTS].tvalue;
    if (fe->tcomms == TermProlog)
      fe->tcomms = PROLOG_MODULE;
  } else {
    fe->tcomms = 0;
  }
  if (args[READ_TERM_POSITION].used) {
    fe->tp = args[READ_TERM_POSITION].tvalue;
  } else {
    fe->tp = 0;
  }
  if (args[READ_SINGLETONS].used) {
    fe->sp = args[READ_SINGLETONS].tvalue;
  } else {
    fe->sp = 0;
  }
  if (args[READ_SYNTAX_ERRORS].used) {
    re->sy = args[READ_SYNTAX_ERRORS].tvalue;
  } else {
    re->sy = TermError; // getYapFlag( MkAtomTerm(AtomSyntaxErrors) );
  }
  if (args[READ_VARIABLES].used) {
    fe->vp = args[READ_VARIABLES].tvalue;
  } else {
    fe->vp = 0;
  }
  if (args[READ_VARIABLE_NAMES].used) {
    fe->np = args[READ_VARIABLE_NAMES].tvalue;
  } else {
    fe->np = 0;
  }
  if (args[READ_CHARACTER_ESCAPES].used ||
      Yap_CharacterEscapes(CurrentModule)) {
    fe->ce = true;
  } else {
    fe->ce = false;
  }
  re->seekable = (GLOBAL_Stream[inp_stream].status & Seekable_Stream_f) != 0;
  if (re->seekable) {
#if HAVE_FGETPOS
    fgetpos(GLOBAL_Stream[inp_stream].file, &re->rpos);
#else
    re->cpos = GLOBAL_Stream[inp_stream].charcount;
#endif
  }
  if (args[READ_PRIORITY].used) {
    re->prio = IntegerOfTerm(args[READ_PRIORITY].tvalue);
    if (re->prio > GLOBAL_MaxPriority) {
      Yap_Error(DOMAIN_ERROR_OPERATOR_PRIORITY, opts,
                "max priority in Prolog is %d, not %ld", GLOBAL_MaxPriority,
                re->prio);
    }
  } else {
    re->prio = LOCAL_default_priority;
  }
  return args;
}