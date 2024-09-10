void carregar_texturas(void) {
    IMAGE *img;
    GLenum gluerr;

    /* textura do plano */
    glGenTextures(1, &textura_plano);
    glBindTexture(GL_TEXTURE_2D, textura_plano);

    if (!(img = ImageLoad(TEXTURA_DO_PLANO))) {
        fprintf(stderr, "Error reading a texture.\n");
        exit(-1);
    }

    gluerr = gluBuild2DMipmaps(GL_TEXTURE_2D, 3,
            img->sizeX, img->sizeY,
            GL_RGB, GL_UNSIGNED_BYTE,
            (GLvoid *) (img->data));
    if (gluerr) {
        fprintf(stderr, "GLULib%s\n", gluErrorString(gluerr));
        exit(-1);
    }

    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_DECAL);

    /* textura do aviao */
    glGenTextures(1, &textura_aviao);
    glBindTexture(GL_TEXTURE_2D, textura_aviao);


    if (!(img = ImageLoad(TEXTURA_DO_AVIAO))) {
        fprintf(stderr, "Error reading a texture.\n");
        exit(-1);
    }

    gluerr = gluBuild2DMipmaps(GL_TEXTURE_2D, 3,
            img->sizeX, img->sizeY,
            GL_RGB, GL_UNSIGNED_BYTE,
            (GLvoid *) (img->data));
    if (gluerr) {
        fprintf(stderr, "GLULib%s\n", gluErrorString(gluerr));
        exit(-1);
    }

    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_DECAL);

}