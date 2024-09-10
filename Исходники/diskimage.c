DiskImage *di_load_image(char *name) {
  FILE *file;
  unsigned int filesize;
  size_t l, read;
  DiskImage *di;

  /* open image */
  if (fopen_s(&file, name, "rb") != 0) {
    return NULL;
  }

  /* get file size*/
  if (fseek(file, 0, SEEK_END)) {
    fclose(file);
    return NULL;
  }
  filesize = ftell(file);
  fseek(file, 0, SEEK_SET);

  if ((di = malloc(sizeof(*di))) == NULL) {
    fclose(file);
    return NULL;
  }

  di->size = filesize;

  /* allocate buffer for image */
  if ((di->image = malloc(filesize)) == NULL) {
    free(di);
    fclose(file);
    return NULL;
  }

  /* read file into buffer */
  read = 0;
  while (read < filesize) {
	l = fread(di->image, 1, filesize - read, file);
	if (l) {
      read += l;
    } else {
      free(di->image);
      free(di);
      fclose(file);
      return NULL;
    }
  }

  fclose(file);

  di->errinfo = NULL;

  /* check image type */
  switch (filesize) {
  case D64ERRSIZE: /* D64 with error info */
    di->errinfo = &(di->image[D64SIZE]);
  case D64SIZE: /* standard D64 */
    di->type = D64;
    di->bam.track = 18;
    di->bam.sector = 0;
    di->dir = di->bam;
    break;

  case D71ERRSIZE: /* D71 with error info */
    di->errinfo = &(di->image[D71SIZE]);
  case D71SIZE:
    di->type = D71;
    di->bam.track = 18;
    di->bam.sector = 0;
    di->bam2.track = 53;
    di->bam2.sector = 0;
    di->dir = di->bam;
    break;

  case D81ERRSIZE: /* D81 with error info */
    di->errinfo = &(di->image[D81SIZE]);
  case D81SIZE:
    di->type = D81;
    di->bam.track = 40;
    di->bam.sector = 1;
    di->bam2.track = 40;
    di->bam2.sector = 2;
    di->dir.track = 40;
    di->dir.sector = 0;
    break;

  default:
    free(di->image);
    free(di);
    return NULL;
  }

  size_t filenameLen = strlen(name) + 1;
  if ((di->filename = malloc(filenameLen)) == NULL) {
    free(di->image);
    free(di);
	return NULL;
  }
  strcpy_s(di->filename, filenameLen, name);
  di->openfiles = 0;
  di->blocksfree = blocks_free(di);
  di->modified = 0;
  di->interleave = interleave(di->type);
  set_status(di, 254, 0, 0);
  return di;
}