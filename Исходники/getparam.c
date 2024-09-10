int main(int argc, string *argv)
{
  initparam(argv, defv);
  printf("program %s:\n", getprog());
  printf("  input = \"%s\" [%o]\n", getparam("input"),
	 getparamstat("input"));
  printf("  output = \"%s\" [%o]\n", getparam("output"),
	 getparamstat("output"));
  printf("  answer = %d [%o]\n", getiparam("answer"),
	 getparamstat("answer"));
  printf("  value = %g [%o]\n", getdparam("value"),
	 getparamstat("value"));
  printf("  flag = %s [%o]\n", getbparam("flag") ? "TRUE" : "FALSE",
	 getparamstat("flag"));
  printf("  foobar = \"%s\" [%o]\n", getparam("foobar"),
	 getparamstat("foobar"));
  printf("  VERSION = \"%s\" [%o]\n", getversion(),
	 getparamstat("VERSION"));
  if (getbparam("flag")) {
    printf("getparamstat(\"junk\") = %o\n", getparamstat("junk"));
    printf("calling getparam(\"junk\")\n");
    (void) getparam("junk");
  }
  return (0);
}