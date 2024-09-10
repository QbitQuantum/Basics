gliGenericImage *
gliReadTGA(FILE *fp, char *name)
{
  TgaHeader tgaHeader;
  TgaFooter tgaFooter;
  char horzrev, vertrev;
  int width, height, bpp;
  int start, end, dir;
  int i, j, k;
  int pelbytes, wbytes;
  GLenum format;
  int components;
  RLEstate rleRec;
  RLEstate *rleInfo;
  int rle;
  int index, colors, length;
  GLubyte *cmap, *pixels, *data;
  int (*myfread)(RLEstate *rleInfo, void*, size_t, size_t, FILE*);
  gliGenericImage *genericImage;

  /* Check the footer. */
  if (fseek(fp, 0L - sizeof(tgaFooter), SEEK_END)
      || fread(&tgaFooter, sizeof(tgaFooter), 1, fp) != 1) {
    sprintf(error, "TGA: Cannot read footer from \"%s\"", name);
    if (verbose) printf("%s\n", error);
    return NULL;
  }  

  /* Check the signature. */
  if (memcmp(tgaFooter.signature, TGA_SIGNATURE,
             sizeof(tgaFooter.signature)) == 0) {
    if (verbose) printf("TGA: found New TGA\n");
  } else {
    if (verbose) printf("TGA: found Original TGA\n");
  }

  if (fseek(fp, 0, SEEK_SET) ||
      fread(&tgaHeader, sizeof(tgaHeader), 1, fp) != 1) {
    sprintf(error, "TGA: Cannot read header from \"%s\"", name);
    if (verbose) printf("%s\n", error);
    return NULL;
  }

  if (verbose && tgaHeader.idLength) {
    char *idString = (char*) malloc(tgaHeader.idLength);
    
    if (fread(idString, tgaHeader.idLength, 1, fp) != 1) {
      sprintf(error, "TGA: Cannot read ID field in \"%s\"", name);
      printf("%s\n", error);
    } else {
      printf("TGA: ID field: \"%*s\"\n", tgaHeader.idLength, idString);
    }
    free(idString);
  } else {
    /* Skip the image ID field. */
    if (tgaHeader.idLength && fseek(fp, tgaHeader.idLength, SEEK_CUR)) {
      sprintf(error, "TGA: Cannot skip ID field in \"%s\"", name);
      if (verbose) printf("%s\n", error);
      return NULL;
    }
  }
  
  /* Reassemble the multi-byte values correctly, regardless of
     host endianness. */
  width = (tgaHeader.widthHi << 8) | tgaHeader.widthLo;
  height = (tgaHeader.heightHi << 8) | tgaHeader.heightLo;
  bpp = tgaHeader.bpp;
  if (verbose) {
    printf("TGA: width=%d, height=%d, bpp=%d\n", width, height, bpp);
  }

  horzrev = tgaHeader.descriptor & TGA_DESC_HORIZONTAL;
  vertrev = !(tgaHeader.descriptor & TGA_DESC_VERTICAL);
  if (verbose && horzrev) printf("TGA: horizontal reversed\n");
  if (verbose && vertrev) printf("TGA: vertical reversed\n");

  rle = 0;
  switch (tgaHeader.imageType) {
  case TGA_TYPE_MAPPED_RLE:
    rle = 1;
    if (verbose) printf("TGA: run-length encoded\n");
  case TGA_TYPE_MAPPED:
    /* Test for alpha channel. */
    format = GL_COLOR_INDEX;
    components = 1;
    if (verbose) {
      printf("TGA: %d bit indexed image (%d bit palette)\n",
        tgaHeader.colorMapSize, bpp);
    }
    break;

  case TGA_TYPE_GRAY_RLE:
    rle = 1;
    if (verbose) printf("TGA: run-length encoded\n");
  case TGA_TYPE_GRAY:
    format = GL_LUMINANCE;
    components = 1;
    if (verbose) printf("TGA: %d bit grayscale image\n", bpp);
    break;

  case TGA_TYPE_COLOR_RLE:
    rle = 1;
    if (verbose) printf("TGA: run-length encoded\n");
  case TGA_TYPE_COLOR:
    /* Test for alpha channel. */
    if (bpp == 32) {
      format = GL_BGRA_EXT;
      components = 4;
      if (verbose) {
        printf("TGA: %d bit color image with alpha channel\n", bpp);
      }
    } else {
      format = GL_BGR_EXT;
      components = 3;
      if (verbose) printf("TGA: %d bit color image\n", bpp);
    }
    break;

  default:
    sprintf(error,
      "TGA: unrecognized image type %d\n", tgaHeader.imageType);
    if (verbose) printf("%s\n", error);
    return NULL;
  }

  if ((format == GL_BGRA_EXT && bpp != 32) ||
      (format == GL_BGR_EXT && bpp != 24) ||
      ((format == GL_LUMINANCE || format == GL_COLOR_INDEX) && bpp != 8)) {
    /* FIXME: We haven't implemented bit-packed fields yet. */
    sprintf(error, "TGA: channel sizes other than 8 bits are unimplemented");
    if (verbose) printf("%s\n", error);
    return NULL;
  }

  /* Check that we have a color map only when we need it. */
  if (format == GL_COLOR_INDEX) {
    if (tgaHeader.colorMapType != 1) {
      sprintf(error, "TGA: indexed image has invalid color map type %d\n",
        tgaHeader.colorMapType);
      if (verbose) printf("%s\n", error);
      return NULL;
    }
  } else if (tgaHeader.colorMapType != 0) {
    sprintf(error, "TGA: non-indexed image has invalid color map type %d\n",
      tgaHeader.colorMapType);
    if (verbose) printf("%s\n", error);
    return NULL;
  }

  if (tgaHeader.colorMapType == 1) {
    /* We need to read in the colormap. */
    index = (tgaHeader.colorMapIndexHi << 8) | tgaHeader.colorMapIndexLo;
    length = (tgaHeader.colorMapLengthHi << 8) | tgaHeader.colorMapLengthLo;

    if (verbose) {
      printf("TGA: reading color map (%d + %d) * (%d / 8)\n",
        index, length, tgaHeader.colorMapSize);
    }
    if (length == 0) {
      sprintf(error, "TGA: invalid color map length %d", length);
      if (verbose) printf("%s\n", error);
      return NULL;
    }
    if (tgaHeader.colorMapSize != 24) {
      /* We haven't implemented bit-packed fields yet. */
      sprintf(error, "TGA: channel sizes other than 8 bits are unimplemented");
      if (verbose) printf("%s\n", error);
      return NULL;
    }

    pelbytes = tgaHeader.colorMapSize / 8;
    colors = length + index;
    cmap = malloc (colors * pelbytes);

    /* Zero the entries up to the beginning of the map. */
    memset(cmap, 0, index * pelbytes);

    /* Read in the rest of the colormap. */
    if (fread(cmap, pelbytes, length, fp) != (size_t) length) {
      sprintf(error, "TGA: error reading colormap (ftell == %ld)\n",
        ftell (fp));
      if (verbose) printf("%s\n", error);
      return NULL;
    }

    if (pelbytes >= 3) {
      /* Rearrange the colors from BGR to RGB. */
      int tmp;
      for (j = index; j < length * pelbytes; j += pelbytes) {
        tmp = cmap[j];
        cmap[j] = cmap[j + 2];
        cmap[j + 2] = tmp;
      }
    }
  } else {
    colors = 0;
    cmap = NULL;
  }

  /* Allocate the data. */
  pelbytes = bpp / 8;
  pixels = (unsigned char *) malloc (width * height * pelbytes);

  if (rle) {
    rleRec.statebuf = 0;
    rleRec.statelen = 0;
    rleRec.laststate = 0;
    rleInfo = &rleRec;
    myfread = rle_fread;
  } else {
    rleInfo = NULL;
    myfread = std_fread;
  }

  wbytes = width * pelbytes;

  if (vertrev) {
    start = 0;
    end = height;
    dir = 1;
  } else {
    /* We need to reverse loading order of rows. */
    start = height-1;
    end = -1;
    dir = -1;
  }

  for (i = start; i != end; i += dir) {
    data = pixels + i*wbytes;

    /* Suck in the data one row at a time. */
    if (myfread(rleInfo, data, pelbytes, width, fp) != width) {
      /* Probably premature end of file. */
      if (verbose) {
        printf ("TGA: error reading (ftell == %ld, width=%d)\n",
          ftell(fp), width);
      }
      return NULL;
    }  

    if (horzrev) {
      /* We need to mirror row horizontally. */
      for (j = 0; j < width/2; j++) {
        GLubyte tmp;

        for (k = 0; k < pelbytes; k++) {
          tmp = data[j*pelbytes+k];
          data[j*pelbytes+k] = data[(width-j-1)*pelbytes+k];
          data[(width-j-1)*pelbytes+k] = tmp;
        }
      }
    }
  }

  if (rle) {
    free(rleInfo->statebuf);
  }

  if (fgetc (fp) != EOF) {
    if (verbose) printf ("TGA: too much input data, ignoring extra...\n");
  }

  genericImage = (gliGenericImage*) malloc(sizeof(gliGenericImage));
  genericImage->width = width;
  genericImage->height = height;
  genericImage->format = format;
  genericImage->components = components;
  genericImage->cmapEntries = colors;
  genericImage->cmapFormat = GL_BGR_EXT;  // XXX fix me
  genericImage->cmap = cmap;
  genericImage->pixels = pixels;

  return genericImage;
}