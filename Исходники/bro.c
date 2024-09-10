int main(int argc, char** argv) {
  char *input_path = 0;
  char *output_path = 0;
  char *dictionary_path = 0;
  int force = 0;
  int quality = 11;
  int decompress = 0;
  int repeat = 1;
  int verbose = 0;
  int lgwin = 0;
  clock_t clock_start;
  int i;
  ParseArgv(argc, argv, &input_path, &output_path, &dictionary_path, &force,
            &quality, &decompress, &repeat, &verbose, &lgwin);
  clock_start = clock();
  for (i = 0; i < repeat; ++i) {
    FILE* fin = OpenInputFile(input_path);
    FILE* fout = OpenOutputFile(output_path, force || repeat);
    int is_ok = 0;
    if (decompress) {
      is_ok = Decompress(fin, fout, dictionary_path);
    } else {
      is_ok = Compress(quality, lgwin, fin, fout, dictionary_path);
    }
    if (!is_ok) {
      unlink(output_path);
      exit(1);
    }
    if (fclose(fin) != 0) {
      perror("fclose");
      exit(1);
    }
    if (fclose(fout) != 0) {
      perror("fclose");
      exit(1);
    }
  }
  if (verbose) {
    clock_t clock_end = clock();
    double duration = (double)(clock_end - clock_start) / CLOCKS_PER_SEC;
    int64_t uncompressed_size;
    double uncompressed_bytes_in_MB;
    if (duration < 1e-9) {
      duration = 1e-9;
    }
    uncompressed_size = FileSize(decompress ? output_path : input_path);
    if (uncompressed_size == -1) {
      fprintf(stderr, "failed to determine uncompressed file size\n");
      exit(1);
    }
    uncompressed_bytes_in_MB =
        (double)(repeat * uncompressed_size) / (1024.0 * 1024.0);
    if (decompress) {
      printf("Brotli decompression speed: ");
    } else {
      printf("Brotli compression speed: ");
    }
    printf("%g MB/s\n", uncompressed_bytes_in_MB / duration);
  }
  return 0;
}