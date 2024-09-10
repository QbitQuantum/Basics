int
main(int argc, char **argv)
{
  Args args(argc, argv, "FILE.igc");
  tstring path = args.ExpectNextT();
  args.ExpectEnd();

  GRecord g;
  g.Initialize();

  if (g.VerifyGRecordInFile(path.c_str())) {
    fprintf(stderr, "G record is ok\n");
    return 0;
  } else {
    fprintf(stderr, "G record is NOT ok\n");
    return 2;
  }
}