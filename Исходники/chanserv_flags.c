u_int64_t cs_accountflagmap_str(char *flags) {
  reguser r2, *r = &r2;

  setflags(&r->flags, QUFLAG_ALL, flags, ruflags, REJECT_NONE);

  return cs_accountflagmap(r);
}