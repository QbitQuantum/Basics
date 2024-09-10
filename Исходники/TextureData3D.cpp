 void TextureData3D :: Upload ( GLenum target )
 {
     glTexImage3D (
         target               /* the target texture */,
         0                    /* the level-of-detail number */,
         InternalFormat ( )   /* the number of color components */,
         Width ( )            /* the width of the texture with border */,
         Height ( )           /* the height of the texture with border */,
         Depth ( )            /* the depth of the texture with border */,
         0                    /* the width of the border */,
         PixelFormat ( )      /* the format of the pixel data */,
         Type ( )             /* the data type of the pixel data */,
         fPixels              /* a pointer to the image data */ );
 }