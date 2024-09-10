int main(int argc, char **argv)
{
    gdImagePtr A, B, C;
    unsigned char black, white;
    unsigned int minSX, minSY, maxSX, maxSY;
    bool rc;
#ifdef HAVE_GD_PNG
    FILE *f;
#endif

    if (argc < 3) {
        fprintf(stderr, "Usage: diffimg image1 image2 [outimage]\n");
        exit(EX_USAGE);
    }
    A = imageLoad(argv[1]);
    B = imageLoad(argv[2]);

    minSX = (gdImageSX(A) < gdImageSX(B)) ? gdImageSX(A) : gdImageSX(B);
    minSY = (gdImageSY(A) < gdImageSY(B)) ? gdImageSY(A) : gdImageSY(B);
    maxSX = (gdImageSX(A) > gdImageSX(B)) ? gdImageSX(A) : gdImageSX(B);
    maxSY = (gdImageSY(A) > gdImageSY(B)) ? gdImageSY(A) : gdImageSY(B);
    
    C = gdImageCreatePalette (maxSX, maxSY);

    white = gdImageColorAllocate(C, gdRedMax, gdGreenMax, gdBlueMax);
    black = gdImageColorAllocate(C, 0, 0, 0);

    if (maxSX > minSX && maxSY > minSY)
	gdImageFilledRectangle(C, minSX, minSY, maxSX-1, maxSY-1, black);

    rc = imageDiff (A, B, C, minSX, minSY, black, white);

#ifdef HAVE_GD_PNG
    if ((argc > 3) && ((f = fopen(argv[3], "wb")))) {
	gdImagePng (C, f);
	fclose(f);
    }
    else
        gdImagePng (C, stdout);
#else

    fprintf(stderr, "PNG output support is not available\n");
#endif

    gdImageDestroy(A);
    gdImageDestroy(B);
    gdImageDestroy(C);

    return (rc ? EXIT_FAILURE : EXIT_SUCCESS);
}