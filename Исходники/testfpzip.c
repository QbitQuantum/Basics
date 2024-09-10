int main(int argc, char* argv[])
{
  int type = FPZIP_TYPE_FLOAT;
  int prec = 0;
  int nx = 1;
  int ny = 1;
  int nz = 1;
  int nf = 1;
  char* infile = 0;
  char* outfile = 0;
  char* reconfile = 0;

  // parse command-line options
  switch (argc) {
    case 10:
      reconfile = argv[9];
      /*FALLTHROUGH*/
    case 9:
      outfile = argv[8];
      /*FALLTHROUGH*/
    case 8:
      infile = argv[7];
      /*FALLTHROUGH*/
    case 7:
      if (sscanf(argv[6], "%d", &prec) != 1)
        goto usage;
      /*FALLTHROUGH*/
    case 6:
      if (sscanf(argv[5], "%d", &nf) != 1)
        goto usage;
      /*FALLTHROUGH*/
    case 5:
      if (sscanf(argv[4], "%d", &nz) != 1)
        goto usage;
      /*FALLTHROUGH*/
    case 4:
      if (sscanf(argv[3], "%d", &ny) != 1)
        goto usage;
      /*FALLTHROUGH*/
    case 3:
      if (sscanf(argv[2], "%d", &nx) != 1)
        goto usage;
      /*FALLTHROUGH*/
    case 2:
      if (!strcmp(argv[1], "-f"))
        type = FPZIP_TYPE_FLOAT;
      else if (!strcmp(argv[1], "-d"))
        type = FPZIP_TYPE_DOUBLE;
      else
        goto usage;
      break;
    default:
    usage:
      fprintf(stderr, "Usage: testfpzip <-f|-d> [nx [ny [nz [nf [prec [infile [outfile [reconfile]]]]]]]]\n");
      return EXIT_FAILURE;
  }

  // initialize
  fprintf(stderr, "testing '%s a[%d][%d][%d][%d]'\n", type == FPZIP_TYPE_FLOAT ? "float" : "double", nf, nz, ny, nx);
  size_t count = (size_t)nx * ny * nz * nf;
  size_t size = (type == FPZIP_TYPE_FLOAT ? sizeof(float) : sizeof(double));
  size_t inbytes = count * size;
  size_t bufbytes = 1024 + inbytes;
  if (prec == 0)
    prec = CHAR_BIT * size;
  int lossless = (prec == CHAR_BIT * size);

  // allocate buffers
#ifdef __cplusplus
  void* data = (type == FPZIP_TYPE_FLOAT ? static_cast<void*>(new float[count]) : static_cast<void*>(new double[count]));
  void* copy = (type == FPZIP_TYPE_FLOAT ? static_cast<void*>(new float[count]) : static_cast<void*>(new double[count]));
  void* buffer = static_cast<void*>(new unsigned char[bufbytes]);
#else
  void* data = malloc(inbytes);
  void* copy = malloc(inbytes);
  void* buffer = malloc(bufbytes);
#endif

  // initialize scalar field
  if (infile) {
    // read raw data
    fprintf(stderr, "reading input file\n");
    FILE* file = fopen(infile, "rb");
    if (!file) {
      fprintf(stderr, "cannot open input file\n");
      return EXIT_FAILURE;
    }
    if (fread(data, size, count, file) != count) {
      fprintf(stderr, "read failed\n");
      return EXIT_FAILURE;
    }
    fclose(file);
  }
  else {
    // set scalar field to product of cosines
    const double pi = acos(-1.0);
    if (type == FPZIP_TYPE_FLOAT) {
      float* p = (float*)data;
      for (int f = 0; f < nf; f++)
        for (int z = 0; z < nz; z++)
          for (int y = 0; y < ny; y++)
            for (int x = 0; x < nx; x++)
              *p++ = cos(2 * pi * x / nx) * cos(2 * pi * y / ny) * cos(2 * pi * z / nz);
    }
    else {
      double* p = (double*)data;
      for (int f = 0; f < nf; f++)
        for (int z = 0; z < nz; z++)
          for (int y = 0; y < ny; y++)
            for (int x = 0; x < nx; x++)
              *p++ = cos(2 * pi * x / nx) * cos(2 * pi * y / ny) * cos(2 * pi * z / nz);
    }
  }

  // compress to memory
  FPZ* fpz = fpzip_write_to_buffer(buffer, bufbytes);
  fpz->type = type;
  fpz->prec = prec;
  fpz->nx = nx;
  fpz->ny = ny;
  fpz->nz = nz;
  fpz->nf = nf;
  if (!compress(fpz, data, inbytes, "memory"))
    return EXIT_FAILURE;
  fpzip_write_close(fpz);

  // decompress from memory
  fpz = fpzip_read_from_buffer(buffer);
#ifdef WITHOUT_HEADER
  // manually set array parameters since header is not stored
  fpz->type = type;
  fpz->prec = prec;
  fpz->nx = nx;
  fpz->ny = ny;
  fpz->nz = nz;
  fpz->nf = nf;
#endif
  if (!decompress(fpz, copy, inbytes, "memory"))
    return EXIT_FAILURE;
  fpzip_read_close(fpz);

  // perform validation
  if (!validate(data, copy, count, type, lossless))
    return EXIT_FAILURE;

  if (outfile) {
    // compress to file
    FILE* file = fopen(outfile, "wb");
    if (!file) {
      fprintf(stderr, "cannot create compressed file\n");
      return EXIT_FAILURE;
    }
    fpz = fpzip_write_to_file(file);
    fpz->type = type;
    fpz->prec = prec;
    fpz->nx = nx;
    fpz->ny = ny;
    fpz->nz = nz;
    fpz->nf = nf;
    if (!compress(fpz, data, inbytes, "file"))
      return EXIT_FAILURE;
    fpzip_write_close(fpz);
    fclose(file);

    // decompress from file
    file = fopen(outfile, "rb");
    if (!file) {
      fprintf(stderr, "cannot open compressed file\n");
      return EXIT_FAILURE;
    }
    fpz = fpzip_read_from_file(file);
#ifdef WITHOUT_HEADER
    // manually set array parameters since header is not stored
    fpz->type = type;
    fpz->prec = prec;
    fpz->nx = nx;
    fpz->ny = ny;
    fpz->nz = nz;
    fpz->nf = nf;
#endif
    if (!decompress(fpz, copy, inbytes, "file"))
      return EXIT_FAILURE;
    fpzip_read_close(fpz);
    fclose(file);

    // perform validation
    if (!validate(data, copy, count, type, lossless))
      return EXIT_FAILURE;

    if (reconfile) {
      // write reconstructed data to file
      FILE* file = fopen(reconfile, "wb");
      if (!file) {
        fprintf(stderr, "cannot open reconstructed file\n");
        return EXIT_FAILURE;
      }
      if (fwrite(copy, size, count, file) != count) {
        fprintf(stderr, "write failed\n");
        return EXIT_FAILURE;
      }
      fclose(file);
    }
  }

  // deallocate buffers
#ifdef __cplusplus
  if (type == FPZIP_TYPE_FLOAT) {
    delete[] static_cast<float*>(data);
    delete[] static_cast<float*>(copy);
  }
  else {
    delete[] static_cast<double*>(data);
    delete[] static_cast<double*>(copy);
  }
  delete[] static_cast<unsigned char*>(buffer);
#else
  free(data);
  free(copy);
  free(buffer);
#endif

  fprintf(stderr, "OK\n");

  return 0;
}