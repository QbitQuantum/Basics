int main(int argc, char* argv[])
{    

  
    if (argc != 4)
    {
        printf("Usage: copy infile outfile\n");
        return 1;
    }
  
    int n = atoi(argv[1]);
    if (n <= 0 || n > 100) {
        printf("Try again");
    }

    // remember filenames
    char* infile = argv[2];
    char* outfile = argv[3];

    // open input file 
    FILE* inptr = fopen(infile, "r");
    if (inptr == NULL)
    {
        printf("Could not open %s.\n", infile);
        return 2;
    }

    // open output file
    FILE* outptr = fopen(outfile, "w");
    if (outptr == NULL)
    {
        fclose(inptr);
        fprintf(stderr, "Could not create %s.\n", outfile);
        return 3;
    }

    // read infile's BITMAPFILEHEADER
    BITMAPFILEHEADER bf;
    fread(&bf, sizeof(BITMAPFILEHEADER), 1, inptr);

    // read infile's BITMAPINFOHEADER
    BITMAPINFOHEADER bi;
    fread(&bi, sizeof(BITMAPINFOHEADER), 1, inptr);

    // ensure infile is (likely) a 24-bit uncompressed BMP 4.0
    if (bf.bfType != 0x4d42 || bf.bfOffBits != MAX || bi.biSize != 40 || 
        bi.biBitCount != 24 || bi.biCompression != 0)
    {
        fclose(outptr);
        fclose(inptr);
        fprintf(stderr, "Unsupported file format.\n");
        return 4;
    }

    int prevWidth = bi.biWidth;
    int prevHeight = bi.biHeight;
    bi.biWidth = prevWidth*n;
    bi.biHeight = prevHeight*n;

    int prevPad = (4 - (prevWidth*sizeof(RGBTRIPLE))%4)%4;
    int curPad =  (4 - (bi.biWidth*sizeof(RGBTRIPLE))%4)%4;
    bi.biSizeImage = (bi.biWidth*sizeof(RGBTRIPLE)+curPad)*abs(bi.biHeight);
    bf.bfSize = (bi.biSizeImage)+MAX; 
    
   
    // write outfile's BITMAPFILEHEADER
    fwrite(&bf,sizeof(BITMAPFILEHEADER),1,outptr);
    // write outfile's BITMAPINFOHEADER
    fwrite(&bi,sizeof(BITMAPINFOHEADER),1,outptr);
    int prevHeight1 = abs(prevHeight);
        
    // iterate over infile's scanlines
    for (int i = 0; i<prevHeight1; i++)
    {
        for (int l = 0; l<n; l++) {
            fseek(inptr,(MAX+((prevWidth*3+prevPad)*i)),SEEK_SET);
            for (int j = 0;j<prevWidth;j++) {

                // temporary storage
                RGBTRIPLE triple;

                // read RGB triple from infile
                fread(&triple, sizeof(RGBTRIPLE), 1, inptr);

                // write RGB triple to outfile
                for (int k = 0; k < n; k++)
                    fwrite(&triple, sizeof(RGBTRIPLE), 1, outptr);                   
            }
            // add curPad
            for (int m=0;m<curPad;m++)
                fputc(0x00, outptr);
        }
    }

    // close infile
    fclose(inptr);

    // close outfile
    fclose(outptr);

    // that's all folks
    return 0;
}