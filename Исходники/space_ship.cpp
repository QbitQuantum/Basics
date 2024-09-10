/*============LOAD TEXTURES=========================*/
void LoadGLTextures() {
    /* Load Texture*/
    Image *image1, *image2, *image3, *image4;

   /* allocate space for texture*/
    image1 = (Image *) malloc(sizeof(Image));
    if (image1 == NULL) {
	printf("Error allocating space for image");
	exit(0);
    }

    if (!ImageLoad("/home/raptor/data/boden.bmp", image1)) {
    exit(1);
    }

    /* Create Texture	*********************************************/
    glBindTexture(GL_TEXTURE_2D, texture[0]);   /* 2d texture (x and y size)*/

    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR); /* scale linearly when image bigger than texture*/
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR); /* scale linearly when image smalled than texture*/
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_T, GL_REPEAT);

    /* 2d texture, level of detail 0 (normal), 3 components (red, green, blue), x size from image, y size from image, */
    /* border 0 (normal), rgb color data, unsigned byte data, and finally the data itself.*/
    glTexImage2D(GL_TEXTURE_2D, 0, 3, image1->sizeX, image1->sizeY, 0, GL_RGB, GL_UNSIGNED_BYTE, image1->data);

    free(image1->data);
    free(image1);
}