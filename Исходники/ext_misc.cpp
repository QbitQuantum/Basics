Variant f_constant(CStrRef name) {
  if (!name.get()) return uninit_null();
  const char *data = name.data();
  int len = name.length();

  // slice off starting backslash
  bool hadInitialBackslash = false;
  if (len > 0 && data[0] == '\\') {
    data += 1;
    len -= 1;
    hadInitialBackslash = true;
  }

  char *colon;
  if ((colon = (char*)memchr(data, ':', len)) && colon[1] == ':') {
    // class constant
    int classNameLen = colon - data;
    char *constantName = colon + 2;
    Class* cls = getClassByName(data, classNameLen);
    if (cls) {
      String cnsName(constantName, data + len - constantName, CopyString);
      TypedValue* tv = cls->clsCnsGet(cnsName.get());
      if (tv) {
        return tvAsCVarRef(tv);
      }
    }
    raise_warning("Couldn't find constant %s", data);
  } else {
    TypedValue* cns;
    if (hadInitialBackslash) {
      String s(data, len, CopyString);
      cns = Unit::loadCns(s.get());
    } else {
      cns = Unit::loadCns(name.get());
    }
    if (cns) return tvAsVariant(cns);
  }

  return uninit_null();
}