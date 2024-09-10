void SetPixelWithVariance(int r, int g, int b, int x, int y, int variance, sf::Image &Image)
{


        int br, bg, bb;
        br=r*variance;
        bg=g*variance;
        bb=b*variance;


        if(br>255) {
                br=255;
        }
        if(br<0) {
                br=0;
        }
        if(bg>255) {
                bg=255;
        }
        if(br<0) {
                bg=0;
        }
        if(bb>255) {
                bb=255;
        }
        if(br<0) {
                bb=0;
        }

        sf::Color Temp;
        Temp.r=br;
        Temp.g=bg;
        Temp.b=bb;
        Image.SetPixel(x, y, Temp);



}