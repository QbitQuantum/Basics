void check_string_literal( FILE* fp, const char* s, char *buf, ... ) {

  char * b;
  va_list ap;
  va_start(ap,buf);

  printf(s); // expected-warning {{format string is not a string literal}}
  // expected-note@-1{{treat the string as an argument to avoid this}}
  vprintf(s,ap); // expected-warning {{format string is not a string literal}}
  fprintf(fp,s); // expected-warning {{format string is not a string literal}}
  // expected-note@-1{{treat the string as an argument to avoid this}}
  vfprintf(fp,s,ap); // expected-warning {{format string is not a string literal}}
  asprintf(&b,s); // expected-warning {{format string is not a string lit}}
  // expected-note@-1{{treat the string as an argument to avoid this}}
  vasprintf(&b,s,ap); // expected-warning {{format string is not a string literal}}
  sprintf(buf,s); // expected-warning {{format string is not a string literal}}
  // expected-note@-1{{treat the string as an argument to avoid this}}
  snprintf(buf,2,s); // expected-warning {{format string is not a string lit}}
  // expected-note@-1{{treat the string as an argument to avoid this}}
  __builtin___sprintf_chk(buf,0,-1,s); // expected-warning {{format string is not a string literal}}
  // expected-note@-1{{treat the string as an argument to avoid this}}
  __builtin___snprintf_chk(buf,2,0,-1,s); // expected-warning {{format string is not a string lit}}
  // expected-note@-1{{treat the string as an argument to avoid this}}
  vsprintf(buf,s,ap); // expected-warning {{format string is not a string lit}}
  vsnprintf(buf,2,s,ap); // expected-warning {{format string is not a string lit}}
  vsnprintf(buf,2,global_fmt,ap); // expected-warning {{format string is not a string literal}}
  __builtin___vsnprintf_chk(buf,2,0,-1,s,ap); // expected-warning {{format string is not a string lit}}
  __builtin___vsnprintf_chk(buf,2,0,-1,global_fmt,ap); // expected-warning {{format string is not a string literal}}

  vscanf(s, ap); // expected-warning {{format string is not a string literal}}

  const char *const fmt = "%d"; // FIXME -- defined here
  printf(fmt, 1, 2); // expected-warning{{data argument not used}}

  // rdar://6079877
  printf("abc"
         "%*d", 1, 1); // no-warning
  printf("abc\
def"
         "%*d", 1, 1); // no-warning
         
  // <rdar://problem/6079850>, allow 'unsigned' (instead of 'int') to be used for both
  // the field width and precision.  This deviates from C99, but is reasonably safe
  // and is also accepted by GCC.
  printf("%*d", (unsigned) 1, 1); // no-warning  
}