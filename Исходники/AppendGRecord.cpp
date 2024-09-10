int
main(int argc, char **argv)
{
  Args args(argc, argv, "FILE.igc");
  tstring path = args.ExpectNextT();
  args.ExpectEnd();

  GRecord g;
  g.Initialize();

  if (!g.LoadFileToBuffer(path.c_str())) {
    fprintf(stderr, "Failed to read file\n");
    return 2;
  }

  g.FinalizeBuffer();

  if (!g.AppendGRecordToFile(path.c_str())) {
    fprintf(stderr, "Failed to write file\n");
    return 2;
  }

  return 0;
}