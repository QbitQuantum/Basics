/* code provided by Rob Fletcher 2001 
 * http://www2.york.ac.uk/services/cserv/sw/graphics/OPENGL/L16.c
 */
GLvoid LoadTexture(GLvoid)
{	
Image *TextureImage;
    
    TextureImage = (Image *) malloc(sizeof(Image));
    if (TextureImage == NULL) {
        printf("Error allocating space for image");
        exit(1);
    }

    if (!ImageLoad("checkerboard.bmp", TextureImage)) {
        exit(1);
    }  
      
    /*  2d texture, level of detail 0 (normal), 3 components (red, green, blue),            */
    /*  x size from image, y size from image,                                              */    
    /*  border 0 (normal), rgb color data, unsigned byte data, and finally the data itself. */ 

    glTexImage2D(GL_TEXTURE_2D, 0, 3,
                 TextureImage->sizeX, TextureImage->sizeY,
                 0, GL_RGB, GL_UNSIGNED_BYTE, TextureImage->data);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_NEAREST); /*  cheap scaling when image bigger than texture */    
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_NEAREST); /*  cheap scaling when image smalled than texture*/

    free (TextureImage->data);
    free( TextureImage );
}