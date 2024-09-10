int main(int argc, char **argv) {
  struct radixdb db;
  if (argc != 2) {
    fprintf(stderr, "usage: radixdbdump f\n");
    return 1;
  }
  openfile(argv[1], &db);
  radixdb_dump2dot(&db);
  closefile(&db);
  return 0;
}