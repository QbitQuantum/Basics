// Image conversion
QImage QOpenCvImageBox::convertToQImage(IplImage *cvimage) {
    QImage image;

    int cvIndex, cvLineStart;
    // switch between bit depths
    // TODO other cases
    switch (cvimage->depth) {
    case IPL_DEPTH_8U:
        switch (cvimage->nChannels) {
        case 3:
            if ( (cvimage->width != image.width()) || (cvimage->height != image.height()) ) {
                QImage temp(cvimage->width, cvimage->height, QImage::Format_RGB32);
                image = temp;
            }
            cvIndex = 0; cvLineStart = 0;
            for (int y = 0; y < cvimage->height; y++) {
                unsigned char red,green,blue;
                cvIndex = cvLineStart;
                for (int x = 0; x < cvimage->width; x++) {
                    // DO it
                    red = cvimage->imageData[cvIndex+2];
                    green = cvimage->imageData[cvIndex+1];
                    blue = cvimage->imageData[cvIndex+0];

                    image.setPixel(x,y,qRgb(red, green, blue));
                    cvIndex += 3;
                }
                cvLineStart += cvimage->widthStep;
            }
            break;
                default:
            printf("This number of channels is not supported\n");
            break;
        }
        break;
        default:
        printf("This type of IplImage is not implemented in QOpenCVWidget\n");
        break;
    }

    return image;
}