static void
pcre_regexp_init(mrb_state *mrb, mrb_value self, mrb_value str, mrb_value flag) {
  mrb_value regexp;
  struct mrb_pcre_regexp *reg;
  int cflag = 0;
  int erroff = 0;
  const char *errstr = NULL;

  regexp = mrb_iv_get(mrb, self, mrb_intern_lit(mrb, "@regexp"));
  if (mrb_nil_p(regexp)) {
    reg = malloc(sizeof(struct mrb_pcre_regexp));
    memset(reg, 0, sizeof(struct mrb_pcre_regexp));
    mrb_iv_set(mrb, self, mrb_intern_lit(mrb, "@regexp"), mrb_obj_value(
        Data_Wrap_Struct(mrb, mrb->object_class,
          &mrb_pcre_regexp_type, (void*) reg)));
  }else{
    Data_Get_Struct(mrb, regexp, &mrb_pcre_regexp_type, reg);
    pcre_free(reg->re);
  }

  if (mrb_nil_p(flag))
    cflag = 0;
  else if (mrb_fixnum_p(flag)) {
    int nflag = mrb_fixnum(flag);
    if (nflag & 1) cflag |= PCRE_CASELESS;
    if (nflag & 2) cflag |= PCRE_EXTENDED;
    if (nflag & 4) cflag |= PCRE_MULTILINE | PCRE_DOTALL;
  } else if (mrb_type(flag) == MRB_TT_TRUE)
    cflag |= PCRE_CASELESS;
  else if (mrb_string_p(flag)) {
    if (STRCHR(RSTRING_PTR(flag), 'i')) cflag |= PCRE_CASELESS;
    if (STRCHR(RSTRING_PTR(flag), 'x')) cflag |= PCRE_EXTENDED;
    if (STRCHR(RSTRING_PTR(flag), 'm')) cflag |= PCRE_MULTILINE | PCRE_DOTALL;
  }
  reg->flag = cflag;
  reg->re = pcre_compile(RSTRING_PTR(str), cflag, &errstr, &erroff, NULL);
  if (!reg->re) {
    mrb_raisef(mrb, E_ARGUMENT_ERROR, "'%S' is an invalid regular expression because %S.",
      mrb_str_new_cstr(mrb, RSTRING_PTR(str) + erroff), mrb_str_new_cstr(mrb, errstr));
  }
  mrb_iv_set(mrb, self, mrb_intern_lit(mrb, "@source"), str);
}