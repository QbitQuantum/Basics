static EMatch does_parm_match(SwigType *type, SwigType *partial_parm_type, const char *partial_parm_type_base, Symtab *tscope, int *specialization_priority) {
  static const int EXACT_MATCH_PRIORITY = 99999; /* a number bigger than the length of any conceivable type */
  int matches;
  int substitutions;
  EMatch match;
  SwigType *ty = Swig_symbol_typedef_reduce(type, tscope);
  String *base = SwigType_base(ty);
  SwigType *t = Copy(partial_parm_type);
  substitutions = Replaceid(t, partial_parm_type_base, base); /* eg: Replaceid("p.$1", "$1", "int") returns t="p.int" */
  matches = Equal(ty, t);
  *specialization_priority = -1;
  if (substitutions == 1) {
    /* we have a non-explicit specialized parameter (in partial_parm_type) because a substitution for $1, $2... etc has taken place */
    SwigType *tt = Copy(partial_parm_type);
    int len;
    /*
       check for match to partial specialization type, for example, all of the following could match the type in the %template:
       template <typename T> struct XX {};
       template <typename T> struct XX<T &> {};         // r.$1
       template <typename T> struct XX<T const&> {};    // r.q(const).$1
       template <typename T> struct XX<T *const&> {};   // r.q(const).p.$1
       %template(XXX) XX<int *const&>;                  // r.q(const).p.int

       where type="r.q(const).p.int" will match either of tt="r.", tt="r.q(const)" tt="r.q(const).p"
    */
    Replaceid(tt, partial_parm_type_base, ""); /* remove the $1, $2 etc, eg tt="p.$1" => "p." */
    len = Len(tt);
    if (Strncmp(tt, ty, len) == 0) {
      match = PartiallySpecializedMatch;
      *specialization_priority = len;
    } else {
      match = PartiallySpecializedNoMatch;
    }
    Delete(tt);
  } else {
    match = matches ? ExactMatch : ExactNoMatch;
    if (matches)
      *specialization_priority = EXACT_MATCH_PRIORITY; /* exact matches always take precedence */
  }
  /*
  Printf(stdout, "      does_parm_match %2d %5d [%s] [%s]\n", match, *specialization_priority, type, partial_parm_type);
  */
  Delete(t);
  Delete(base);
  Delete(ty);
  return match;
}