PNM* NoiseBilateral::transform()
{
    int width  = image->width();
    int height = image->height();

    PNM* newImage = new PNM(width, height, image->format());

    sigma_d = getParameter("sigma_d").toInt();
    sigma_r = getParameter("sigma_r").toInt();
    radius = sigma_d;
    Mode mode = RepeatEdge;
    QRgb pixel;
    int r,g,b;
    if(image->format() == QImage::Format_RGB32){
        for(int x=0;x<width;x++){
            for(int y=0;y<height;y++){
                pixel = getPixel(x,y,mode);

                r=calcVal(x,y,RChannel);
                g=calcVal(x,y,GChannel);
                b=calcVal(x,y,BChannel);
                QColor newPixel = QColor(r,g,b);
                newImage->setPixel(x,y,newPixel.rgb());
            }
        }
    }
    else if(image->format() == QImage::Format_Indexed8){
        for(int x=0;x<width;x++){
            for(int y=0;y<height;y++){
                int temp = calcVal(x,y,LChannel);
                newImage->setPixel(x,y,temp);
            }
        }
    }
    return newImage;
}