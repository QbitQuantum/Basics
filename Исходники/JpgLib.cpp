/**
* Converts the RGB Image to GrayScale Image.
*/
void JPGImage::toGrayScale(){

    setGrayScaleAvaliable(true);

   //The news values of Gray Pixel are copied to the Pixel Matrix
   for(int x = 0; x < getWidth(); x++){
      for(int y = 0; y < getHeight(); y++){
          Pixel *p = new Pixel(getPixel(x, y));
          p->toGrayScale();
          setPixel(x, y, p);
          delete(p);
      }
   }
}