const curse_type *ct_find(const char *c)
{
  unsigned int hash = tolower(c[0]);
  quicklist *ctl = cursetypes[hash];
  int qi;

  for (qi = 0; ctl; ql_advance(&ctl, &qi, 1)) {
    curse_type *type = (curse_type *) ql_get(ctl, qi);

    if (strcmp(c, type->cname) == 0) {
      return type;
    } else {
      size_t k = _min(strlen(c), strlen(type->cname));
      if (!_memicmp(c, type->cname, k)) {
        return type;
      }
    }
  }
  return NULL;
}