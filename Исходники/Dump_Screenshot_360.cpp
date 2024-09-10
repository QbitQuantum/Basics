// ***********************************//
// ========= MAIN FUNCTION ========= //
// *********************************//
int main (int argc, char *argv[])
{
          
    // ***********************************//
    // ========== OPEN FILE ============ //
    // *********************************//
    unsigned char *f; // Store Whole File to Memory 
    unsigned char *fOrig;


    FILE *inFile, *outFile; 
    if(!(inFile = fopen (argv[1], "rb")))
    {
        printf("DOA5 Screenshot Converter\nBy: mario_kart64n\nDate: Sept 28 2012\n\nUsage: <Input> <Output>\n");
        return 1; 
    }

    if(!(outFile = fopen (argv[2], "wb")))
    { 
        printf("DOA5 Screenshot Converter\nBy: mario_kart64n\nDate: Sept 28 2012\n\nUsage: <Input> <Output>\n");
        return 2;
    }
    if(!(f=(unsigned char*) malloc(getfilesize (inFile))))
    { 
        printf("Not enough memory.\n"); 
        return(-1); 
    }
    if(!fread(f, 1, (getfilesize (inFile)), inFile))
    { 
        printf("Error reading file.\n"); 
        return(-1);
    }

    fOrig = f;

    // ***********************************//
    // ======== FILE OPERATION ========= //
    // *********************************//

    int cnt = 0;
    fseek(inFile, 0, SEEK_SET);
    fclose (inFile);

    f+=0xD010; // seek to texture data in the PIR
    int magic = readlong(f); 
    if (magic == 0x53584554)
    {
        f+=64;

        for (int i = 1; i-1 < 54; i++) 
        {
            fwrite(bmp_header+cnt, 1, 1, outFile);cnt+=1;	//Write BMP Header
        }

        for (int i = 0; i-1 < 230400; i++) { // 1280 x 0720 pixels
        cnt = ((untile_ARGB32_1280_0720b[i]-1)*4);

        fwrite(f+(cnt+3), 1, 1, outFile);	// Red
        fwrite(f+(cnt+2), 1, 1, outFile);	// Green
        fwrite(f+(cnt+1), 1, 1, outFile);	// Blue

        cnt+=4;

        fwrite(f+(cnt+3), 1, 1, outFile);	// Red
        fwrite(f+(cnt+2), 1, 1, outFile);	// Green
        fwrite(f+(cnt+1), 1, 1, outFile);	// Blue

        cnt+=4;

        fwrite(f+(cnt+3), 1, 1, outFile);	// Red
        fwrite(f+(cnt+2), 1, 1, outFile);	// Green
        fwrite(f+(cnt+1), 1, 1, outFile);	// Blue

        cnt+=4;

        fwrite(f+(cnt+3), 1, 1, outFile);	// Red
        fwrite(f+(cnt+2), 1, 1, outFile);	// Green
        fwrite(f+(cnt+1), 1, 1, outFile);	// Blue

        }
    } 
    else 
    {
        f+=0x1000;
        int magic = readlong(f); 
        if (magic == 0x53584554)
        {
            f+=64;

            for (int i = 1; i-1 < 54; i++)
            {
                fwrite(bmp_header+cnt, 1, 1, outFile);cnt+=1;	//Write BMP Header
            }

            for (int i = 0; i-1 < 230400; i++) { // 1280 x 0720 pixels
            cnt = ((untile_ARGB32_1280_0720c[i]-1)*4);

            fwrite(f+(cnt+3), 1, 1, outFile);	// Red
            fwrite(f+(cnt+2), 1, 1, outFile);	// Green
            fwrite(f+(cnt+1), 1, 1, outFile);	// Blue

            cnt+=4;

            fwrite(f+(cnt+3), 1, 1, outFile);	// Red
            fwrite(f+(cnt+2), 1, 1, outFile);	// Green
            fwrite(f+(cnt+1), 1, 1, outFile);	// Blue

            cnt+=4;

            fwrite(f+(cnt+3), 1, 1, outFile);	// Red
            fwrite(f+(cnt+2), 1, 1, outFile);	// Green
            fwrite(f+(cnt+1), 1, 1, outFile);	// Blue

            cnt+=4;

            fwrite(f+(cnt+3), 1, 1, outFile);	// Red
            fwrite(f+(cnt+2), 1, 1, outFile);	// Green
            fwrite(f+(cnt+1), 1, 1, outFile);	// Blue

            }
        }
    }

    fclose(outFile);

    free(fOrig);
    return (0);
}