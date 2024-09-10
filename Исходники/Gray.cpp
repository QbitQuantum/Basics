void Gray::gamma(double c,double _y)
{
    for(int y=0;y<this->mat->getHeight();y++){
        for (int x = 0; x < this->mat->getWidth(); x++) {
            Pixel * pixel = this->mat->getPixel(x,y);
            uint32_t R = pixel->getR();
            uint32_t G = pixel->getG();
            uint32_t B = pixel->getB();

            uint32_t gray = (R*19595 + G*38469 + B*7472) >> 16;

            gray = c * (pow(gray,_y));

            pixel->setPixel(gray,gray,gray);
            delete (pixel);
        }
    }
}