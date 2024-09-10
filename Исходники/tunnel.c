static void inittextures(void)
{
  IMAGE *img;
  GLenum gluerr;
  
  glGenTextures(1,&t1id);
  glBindTexture(GL_TEXTURE_2D,t1id);

  if(!(img=ImageLoad("tile.rgb"))) {
    fprintf(stderr,"Error reading a texture.\n");
    exit(-1);
  }

  glPixelStorei(GL_UNPACK_ALIGNMENT,4);
  if((gluerr=gluBuild2DMipmaps(GL_TEXTURE_2D, 3, img->sizeX, img->sizeY, GL_RGB,
			       GL_UNSIGNED_BYTE, (GLvoid *)(img->data)))) {
    fprintf(stderr,"GLULib%s\n",gluErrorString(gluerr));
    exit(-1);
  }

  glTexParameterf(GL_TEXTURE_2D,GL_TEXTURE_WRAP_S,GL_REPEAT);
  glTexParameterf(GL_TEXTURE_2D,GL_TEXTURE_WRAP_T,GL_REPEAT);
  
  glTexParameterf(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_NEAREST_MIPMAP_LINEAR);
  glTexParameterf(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);

  glTexEnvf(GL_TEXTURE_ENV,GL_TEXTURE_ENV_MODE,GL_MODULATE);

  glGenTextures(1,&t2id);
  glBindTexture(GL_TEXTURE_2D,t2id);

  if(!(img=ImageLoad("bw.rgb"))) {
    fprintf(stderr,"Error reading a texture.\n");
    exit(-1);
  }

  glPixelStorei(GL_UNPACK_ALIGNMENT,4);
  if((gluerr=gluBuild2DMipmaps(GL_TEXTURE_2D, 3, img->sizeX, img->sizeY, GL_RGB,
			       GL_UNSIGNED_BYTE, (GLvoid *)(img->data)))) {
    fprintf(stderr,"GLULib%s\n",gluErrorString(gluerr));
    exit(-1);
  }

  glTexParameterf(GL_TEXTURE_2D,GL_TEXTURE_WRAP_S,GL_REPEAT);
  glTexParameterf(GL_TEXTURE_2D,GL_TEXTURE_WRAP_T,GL_REPEAT);
  
  glTexParameterf(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_NEAREST_MIPMAP_LINEAR);
  glTexParameterf(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);

  glTexEnvf(GL_TEXTURE_ENV,GL_TEXTURE_ENV_MODE,GL_MODULATE);
}