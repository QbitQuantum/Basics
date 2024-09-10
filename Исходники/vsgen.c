int main(int cn, char *cl[])
{
  FILE *f1, *f2;
  fpos_t pos = { 0 };
  unsigned grab = 1, sizeS = 0, sizeD = 0, num = 0, off = 0, ins = 0, r = 0, w = 0;
  unsigned width = 352, height = 288, size = 152064, yuv = 0, loop = 0, n = 0;
  char *p = 0, *buf = 0, *dst = 0;
  enum scale scale = NONE;

  if (cn < 7) {
U:  puts("vsgen [options] <src.yuv> <dst.yuv>");
    puts("options:");
    puts("  -size n\tframe size [bytes]");
    puts("  -grab n\tgrab every n-th frame");
    puts("  -insert n\twrite each grabbed frame n times");
    puts("  -offset n\tdo not write first n frames");
    puts("  -num n\tnumber of frames to write (input is looped if required)");
    puts("  -[up|down]\tscales frame size (up = double size, down = half size");
    puts("  -to [422|420]\tconvert from YUV 4:2:0 to YUV 4:2:2 or vice versa");
    return EXIT_FAILURE;
  }

  while (++n < cn - 2) {
    p = cl[n];
    if (*p++ != '-') break;
    switch(*p) {
      case 's': if ((size = sizeS = strtoul(cl[++n], 0, 10)) == 0) goto U; break;
      case 'g': if ((grab = strtoul(cl[++n], 0, 10)) == 0) goto U; break;
      case 'i': ins = strtoul(cl[++n], 0, 10); break;
      case 'o': off = strtoul(cl[++n], 0, 10); break;
      case 'n': if ((num = strtoul(cl[++n], 0, 10)) == 0) goto U; break;
      case 'u': if (scale == DOWN) goto U; scale = UP; break;
      case 'd': if (scale == UP) goto U; scale = DOWN; break;
      case 't': if (420 != (yuv = strtoul(cl[++n], 0, 10)) && 422 != yuv) goto U; break;
      default : goto U;
    }
  }
  if (!sizeS || !num) goto U;

  if (scale || yuv) {
    if (sizeS == 704 * 288 * 3 / 2) {
      width = 704;
      height = 288;
    } else {
      width = sqrt(sizeS * 22 / 27);
      height = sqrt(sizeS * 6 / 11);
    }
    sizeD = scale == DOWN ? sizeS / 4 : sizeS * 4;
  }

  if ((f1 = fopen(cl[n], "rb")) == 0) goto A;
  if ((f2 = fopen(cl[n + 1], "wb")) == 0) goto B;
  if ((buf = malloc(sizeS)) == 0) goto E;
  if (scale) if ((dst = malloc(sizeD)) == 0) goto E;
  if (yuv == 422) {
    size = 4 * sizeS / 3;
    if ((buf = realloc(buf, size)) == 0) goto E;
  }

  fgetpos(f1, &pos);
  while (w < num) {
    if (1 != fread(buf, sizeS, 1, f1)) {
      if (ferror(f1)) goto C;
      if (feof(f1)) {
        if (0 != fsetpos(f1, &pos)) { perror("fsetpos"); break; }
        loop++;
        continue;
      }
    }
    if ((r++ % grab) == 0) {
      if (scale) scale_420(buf, width, height, dst, scale);
      if (yuv == 422) to422(buf, width, height);
      for (n = 0; n < ins + 1 && w < num; n++) {
        if (off == 0) {
          if (1 != fwrite(scale ? dst : buf, scale ? sizeD : size, 1, f2)) goto D;
	  w++;
	} else {
          off--;
	}
        printf("Frames: %u grabbed, %u written (input looped: %u times)\r", r, w, loop);
      }
    }
  }
  puts("");

  fclose(f1);
  fclose(f2);

  return 0;

A: fprintf(stderr, "\nError opening source video file.\n"); goto X;
B: fprintf(stderr, "\nError opening destination video file.\n"); goto X;
C: fprintf(stderr, "\nError reading source video file.\n"); goto X;
D: fprintf(stderr, "\nError writing destination video file.\n"); goto X;
E: fprintf(stderr, "\nNot enough memory.\n");

X: return EXIT_FAILURE;
}