bool cTIFFFile::Load(GLCD::cImage & image, const std::string & fileName)
{
    FILE         *fIN;
    TIFFTAG       tifftag;
    unsigned int  tiff_header, tiff_anztags, tiff_data;
    unsigned char cl,ch,y,i;
    unsigned char height, width, strip, invert;
    unsigned char fLittleEndian=0;
    int j;
    int t;
    unsigned char *bitmap = NULL;
    bool  bInvert = false;

    if (fileName.length() > 0)
    {
        fIN = fopen(fileName.c_str(), "rb");
        if (fIN)
        {
            //    isyslog("graphlcd plugin: try to load logo %s.", szFileName);
            if (fseek(fIN, 0, SEEK_SET)==EOF)
            {
                fclose(fIN);
                return false;
            }
            GETANDCHECK; cl=(unsigned char)t;
            GETANDCHECK; ch=(unsigned char)t;
            if ((cl==0x49) && (ch==0x49))
            {
                fLittleEndian=1;
            }

            if (fseek(fIN, 4, SEEK_SET)==EOF)
            {
                fclose(fIN);
                return false;
            }
            GETANDCHECK; cl=(unsigned char)t;
            GETANDCHECK; ch=(unsigned char)t;
            tiff_header = cl+256*ch;
            //printf("tiff_header:%d %x\n", tiff_header, tiff_header);

            if (fseek(fIN, tiff_header, SEEK_SET)==EOF)
            {
                fclose(fIN);
                return false;
            }

            GETANDCHECK; cl=(unsigned char)t;
            GETANDCHECK; ch=(unsigned char)t;
            tiff_anztags = cl+256*ch;
            //printf("tiff_anztags:%d %x\n", tiff_anztags, tiff_anztags);

            height=0;
            width=0;
            strip=0;
            invert=0;
            for (i=0; (i<tiff_anztags)&&(!height||!width||!strip||!invert); i++)
            {
                if (fread(&tifftag, sizeof(tifftag), 1, fIN)!=1)
                {
                    fclose(fIN);
                    return false;
                }
                if (tifftag.tag==0x0100) width=tifftag.off_val;
                if (tifftag.tag==0x0101) height=tifftag.off_val;
                if (tifftag.tag==0x0111) strip=tifftag.off_val;
                if (tifftag.tag==0x0106) invert=tifftag.off_val+1;
                //printf("tag%d: %d %d %ld %ld\n", i,tifftag.tag, tifftag.type, tifftag.length, tifftag.off_val );
            }

            if (fseek(fIN,strip, SEEK_SET)==EOF)
            {
                fclose(fIN);
                return false;
            }
            GETANDCHECK; cl=(unsigned char)t;
            GETANDCHECK; ch=(unsigned char)t;
            tiff_data = cl+256*ch;
            //printf("tiff_data:%d %x\n", tiff_data, tiff_data);

            if (fseek(fIN, tiff_data, SEEK_SET)==EOF)
            {
                fclose(fIN);
                return false;
            }


            image.Clear();
            image.SetWidth(width);
            image.SetHeight(height);
            image.SetDelay(100);
            bitmap = new unsigned char[height * ((width + 7) / 8)];
            if (bitmap)
            {
                if (fread(bitmap, height*((width+7)/8), 1, fIN)!=1)
                {
                    delete [] bitmap;
                    fclose(fIN);
                    image.Clear();
                    return false;
                }

                if (invert-1==1) bInvert = !bInvert; // 'Black is zero'
                if (bInvert)
                {
                    for (j=0; j < height * ((width+7)/8); j++)
                    {
                        (*(bitmap+j)) = (*(bitmap+j))^0xff;
                    }
                }

                // cut the rest of the line
                if (width%8)
                {
                    for (y=1; y<=height; y++) {
                        j=y*((width+7)/8)-1;
                        (*(bitmap+j)) = ((*(bitmap+j))>>(8-width%8))<<(8-width%8);
                    }
                }
                image.AddBitmap(new GLCD::cBitmap(width, height, bitmap));
            }
            else
            {
                fprintf(stderr, "ERROR: cannot allocate memory\n");
            }
            fclose(fIN);
        }