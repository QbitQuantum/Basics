QImage* setMaskMap(IplImage* ocvImage, IplImage* mask)
{
    int height = ocvImage->height;
    int width = ocvImage->width;
    QImage *retImage = new QImage( width, height, QImage::Format_RGB32 );

    int R, G, B;

    for(int y = 0; y < height; y++)
    {
        for(int x = 0; x < width; x++)
        {
            CvScalar color1 = cvGet2D(ocvImage, y, x);
            CvScalar color2 = cvGet2D(mask, y, x);

            if(ocvImage->nChannels == 3)
            {
                R = 0.6 * color1.val[2] + 0.4 * color2.val[2];
                G = 0.6 * color1.val[1] + 0.4 * color2.val[1];
                B = 0.6 * color1.val[0] + 0.4 * color2.val[0];
            }
            if(x > 0 && x < width-1 && y > 0 && y < height-1 && (color2.val[2] != 0 || color2.val[1] != 0 || color2.val[0] != 0))
            {
                CvScalar color3 = cvGet2D(mask, y, x-1);
                CvScalar color4 = cvGet2D(mask, y, x+1);
                CvScalar color5 = cvGet2D(mask, y-1, x);
                CvScalar color6 = cvGet2D(mask, y+1, x);

                if(isAllZero(color3) || isAllZero(color4) || isAllZero(color5) || isAllZero(color6))
                {
                    R = 255;
                    G = 255;
                    B = 0;
                }
            }
            retImage->setPixel(x, y, qRgb(R, G, B));
        }
    }

    return retImage;
}