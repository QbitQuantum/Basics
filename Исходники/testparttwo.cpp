// Utility function which rebuilds an image from a list of pixels
void buildImage(BMP & image, List<RGBApixel> theList, int width, int height) 
{
   if (width * height != theList.length()) {
      cout << "Error: invalid parameters to buildImage.\n";
      return;
   }

   image.SetSize(width, height);
   int x = 0, y = 0;
   theList.front();
   for (int pos = 0; pos < theList.length(); pos++) {
      *image(x,y) = theList.retrieve();

      // move to next pixel position
      x++;
      if (x >= width) {
         x = 0;
         y++;
      }

      // avoid spurious warning message
      if (pos != theList.length() - 1)
         theList.forwardOne();
   }
}