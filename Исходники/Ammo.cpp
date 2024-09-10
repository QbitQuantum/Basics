void Ammo::LoadGLTextures()
{
    int w, h, c;
    glPixelStorei(GL_UNPACK_ALIGNMENT, 2);
    #if RAYGL == 1
    Image *image[1];
    for (c = 0; c < 1; c++) {
        image[c] = (Image *) malloc(sizeof(Image));
        if (image[c] == NULL) exit(0);
    }
    #else
    uchar*data;

    #endif

    #if RAYGL == 1
    if (!imageLoad("Data/red.ppm", image[0])) exit(0);
    #else
    data = PGM_FILE_READ("Data/red.ppm", &w, &h, &c); 
    #endif 
    
    // Load texture map for sphere.
    //data = PGM_FILE_READ("Data/image-1.ppm", &w, &h, &c); 
    /*BITMAPINFO *BitmapInfo; 
     * data = LoadDIBitmap("Data/perf_white.bmp",&BitmapInfo);
     * w = BitmapInfo->bmiHeader.biWidth; 
     * h = BitmapInfo->bmiHeader.biHeight;
     */
    glGenTextures(1, &EarthMap);
    glBindTexture(GL_TEXTURE_2D, EarthMap);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
    
    glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR );
    glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR_MIPMAP_LINEAR );   
    #if RAYGL == 1
    gluBuild2DMipmaps(GL_TEXTURE_2D,3, image[0]->sizeX, image[0]->sizeY,GL_RGB,GL_UNSIGNED_BYTE,image[0]->data);
    #else
    
    gluBuild2DMipmaps( GL_TEXTURE_2D, 3, w, h, GL_RGB, GL_UNSIGNED_BYTE, data );
    free(data);
    #endif
    

}