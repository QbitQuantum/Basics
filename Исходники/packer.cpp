int main(int argc, char*argv[]) {
  if (argc < 2) { return 1; }
  bool unpack = strstr(argv[1], ".pack") != nullptr;
  FILE* fptr = fopen(argv[1], "rb");
  if (!fptr) { printf("Could not open %s\n", argv[1]); return 1; }
  fseek(fptr, 0, SEEK_END);
  u32 size = ftell(fptr);
  fseek(fptr, 0, SEEK_SET);
  int os = 0;
  CompressionParameters params;
  memset(&params, 0, sizeof(params));
  if (unpack) {
    fread(&os, 4, 1, fptr);
    fread(&params.contextCount, 1, 1, fptr);
    fread(params.weights, params.contextCount, 1, fptr);
    fread(params.contexts, params.contextCount, 1, fptr);
    size -= ftell(fptr);
  }
  u8* data = (u8*)malloc(size + 10);
  memset(data, 0, size + 10);
  data += 10;  // Ugly, but we can ensure we have a few zero bytes at the beginning of the input.
  fread(data, 1, size, fptr);
  fclose(fptr);

  char ofn[256];
  strcpy(ofn, argv[1]);
  if (unpack) {
    *strrchr(ofn, '.') = 0;
    strcat(ofn, ".unpack");
  } else {
    strcat(ofn, ".pack");
  }
  
  u8* out = (u8*)malloc(65536);
  memset(out, 0, 65536);
  out += 10;  // Ugly, but we can ensure we have a few zero bytes at the beginning of the output.
  FILE* ofptr = fopen(ofn, "wb");
  if (!ofptr) { printf("Could not open %s\n", argv[1]); return 1; }

  if (unpack) {
    Compressor* comp = new Compressor();
    comp->Decompress(&params, &data[size - 4], out, os);
    fwrite(out, os, 1, ofptr);
  } else {
    Compressor* comp = new Compressor();
    os = 65528;
    comp->Compress(&params, data, size, out, &os);
    Invert(out, os);

    fwrite(&size, 4, 1, ofptr);
    fwrite(&params.contextCount, 1, 1, ofptr);
    fwrite(params.weights, params.contextCount, 1, ofptr);
    fwrite(params.contexts, params.contextCount, 1, ofptr);
    fwrite(out, os, 1, ofptr);
  }
  fclose(ofptr);
  return 0;
}