int SpriteCache::saveToFile(const char *filnam, int lastElement, bool compressOutput)
{
  FILE *output = fopen(filnam, "wb");
  if (output == NULL)
    return -1;

  if (compressOutput) {
    // re-open the file so that it can be seeked
    fclose(output);
    output = fopen(filnam, "r+b");
    if (output == NULL)
      return -1;
  }

  int spriteFileIDCheck = (int)time(NULL);

  // version 6
  putshort(6, output);

  fwrite(spriteFileSig, strlen(spriteFileSig), 1, output);

  fputc(compressOutput ? 1 : 0, output);
  putw(spriteFileIDCheck, output);

  int i, lastslot = 0;
  if (elements < lastElement)
    lastElement = elements;

  for (i = 1; i < lastElement; i++) {
    // slot empty
    if ((images[i] != NULL) || ((offsets[i] != 0) && (offsets[i] != sprite0InitialOffset)))
      lastslot = i;
  }

  putshort(lastslot, output);

  // allocate buffers to store the indexing info
  int numsprits = lastslot + 1;
  short *spritewidths = (short*)malloc(numsprits * sizeof(short));
  short *spriteheights = (short*)malloc(numsprits * sizeof(short));
  long *spriteoffs = (long*)malloc(numsprits * sizeof(long));

  const int memBufferSize = 100000;
  char *memBuffer = (char*)malloc(memBufferSize);

  for (i = 0; i <= lastslot; i++) {

    spriteoffs[i] = ftell(output);

    // if compressing uncompressed sprites, load the sprite into memory
    if ((images[i] == NULL) && (this->spritesAreCompressed != compressOutput))
      (*this)[i];

    if (images[i] != NULL) {
      // image in memory -- write it out
      pre_save_sprite(i);
      int bpss = bitmap_color_depth(images[i]) / 8;
      spritewidths[i] = images[i]->w;
      spriteheights[i] = images[i]->h;
      putshort(bpss, output);
      putshort(spritewidths[i], output);
      putshort(spriteheights[i], output);

      if (compressOutput) {
        long lenloc = ftell(output);
        // write some space for the length data
        putw(0, output);

        compressSprite(images[i], output);

        long fileSizeSoFar = ftell(output);
        // write the length of the compressed data
        fseek(output, lenloc, SEEK_SET);
        putw((fileSizeSoFar - lenloc) - 4, output);
        fseek(output, 0, SEEK_END);
      }
      else
        fwrite(&images[i]->line[0][0], spritewidths[i] * bpss, spriteheights[i], output);

      continue;
    }

    if ((offsets[i] == 0) || ((offsets[i] == sprite0InitialOffset) && (i > 0))) {
      // sprite doesn't exist
      putshort(0, output);
      spritewidths[i] = 0;
      spriteheights[i] = 0;
      spriteoffs[i] = 0;
      continue;
    }

    // not in memory -- seek to it in the source file
    seekToSprite(i);
    lastLoad = i;

    short colDepth = getshort(ff);
    putshort(colDepth, output);

    if (colDepth == 0) {
      continue;
    }

    if (this->spritesAreCompressed != compressOutput) {
      // shouldn't be able to get here
      free(memBuffer);
      fclose(output);
      return -2;
    }

    // and copy the data across
    int width = getshort(ff);
    int height = getshort(ff);

    spritewidths[i] = width;
    spriteheights[i] = height;

    putshort(width, output);
    putshort(height, output);

    int sizeToCopy;
    if (this->spritesAreCompressed) {
      sizeToCopy = getw(ff);
      putw(sizeToCopy, output);
    }
    else {
      sizeToCopy = width * height * (int)colDepth;
    }

    while (sizeToCopy > memBufferSize) {
      fread(memBuffer, memBufferSize, 1, ff);
      fwrite(memBuffer, memBufferSize, 1, output);
      sizeToCopy -= memBufferSize;
    }

    fread(memBuffer, sizeToCopy, 1, ff);
    fwrite(memBuffer, sizeToCopy, 1, output);
  }

  free(memBuffer);

  fclose(output);

  // write the sprite index file
  FILE *ooo = fopen(spindexfilename, "wb");
  // write "SPRINDEX" id
  fwrite(&spindexid[0], strlen(spindexid), 1, ooo);
  // write version (1)
  putw(2, ooo);
  putw(spriteFileIDCheck, ooo);
  // write last sprite number and num sprites, to verify that
  // it matches the spr file
  putw(lastslot, ooo);
  putw(numsprits, ooo);
  fwrite(&spritewidths[0], sizeof(short), numsprits, ooo);
  fwrite(&spriteheights[0], sizeof(short), numsprits, ooo);
  fwrite(&spriteoffs[0], sizeof(long), numsprits, ooo);
  fclose(ooo);

  free(spritewidths);
  free(spriteheights);
  free(spriteoffs);

  return 0;
}