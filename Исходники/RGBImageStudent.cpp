RGBImageStudent::RGBImageStudent(const RGBImageStudent &other) : RGBImage{ other.getWidth(), other.getHeight() } {
	pixelmap = new RGB[this->getWidth() * this->getHeight()];
   for (int i = 0; i < this->getHeight()*this->getWidth(); i++) {
       pixelmap[i] = other.getPixel(i);
   }
}