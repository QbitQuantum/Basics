static char *
subWord(register char *s, register char *store)
{ *store++ = makeLower(*s);
  s++;

  for(;;)
  { if (*s == EOS)
    { *store = EOS;
      return s;
    }
    if (*s == '_')
    { *store = EOS;
      return ++s;
    }
    if (isLower(s[-1]) && isUpper(s[0]) )
    { *store = EOS;
      return s;
    }
    *store++ = *s++;
  }
}    