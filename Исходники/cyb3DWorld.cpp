// Load Bitmaps And Convert To Textures
inline void Cyb3DWorld::loadBMPTexture(char* path, int idTex)
{
    CybParameters *cybCore = CybParameters::getInstance();

    // Load Texture
    Image *image;

    // allocate space for texture
    image = (Image *) malloc(sizeof(Image));
    if (image == NULL)
    {
        printf("Error allocating space for image");
        exit(0);
    }

    if (!ImageLoad(path, image))
    {
        exit(1);
    }

    // Create Texture
    glGenTextures(1, &(cybCore->texture[idTex]));
    glBindTexture(GL_TEXTURE_2D, cybCore->texture[idTex]);   // 2d texture (x and y size)

    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR); // scale linearly when image bigger than texture
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR); // scale linearly when image smalled than texture

    // 2d texture, level of detail 0 (normal), 3 components (red, green, blue), x size from image, y size from image,
    // border 0 (normal), rgb color data, unsigned byte data, and finally the data itself.
    glTexImage2D(GL_TEXTURE_2D, 0, 3, image->sizeX, image->sizeY, 0, GL_RGB, GL_UNSIGNED_BYTE, image->data);
};