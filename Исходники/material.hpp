 Color getTextureColor(float u, float v, float lod) const{
     Color c;
     mTexture->getPixel(u, v, lod, c);
     return c;
 }