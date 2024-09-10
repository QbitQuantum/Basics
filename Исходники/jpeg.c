int
main(int argc, char *argv[])
{
    OPENMAX_JPEG_DECODER *pDecoder;
    char           *sourceImage;
    size_t          imageSize;
    int             s;
    if (argc < 2) {
	printf("Usage: %s <filename>\n", argv[0]);
	return -1;
    }
    FILE           *fp = fopen(argv[1], "rb");
    if (!fp) {
	printf("File %s not found.\n", argv[1]);
    }
    fseek(fp, 0L, SEEK_END);
    imageSize = ftell(fp);
    fseek(fp, 0L, SEEK_SET);
    sourceImage = malloc(imageSize);
    assert(sourceImage != NULL);
    s = fread(sourceImage, 1, imageSize, fp);
    assert(s == imageSize);
    fclose(fp);
    bcm_host_init();
    s = setupOpenMaxJpegDecoder(&pDecoder);
    assert(s == 0);
    s = decodeImage(pDecoder, sourceImage, imageSize);
    assert(s == 0);
    cleanup(pDecoder);
    free(sourceImage);
    return 0;
}