QImage * pointsDinterets::matrixToQimage(QImage* image, matrix<double> tab){
    int imWidth = image->width();
    int imHeight = image->height();

    QImage *nouvelleImage = new QImage(imWidth, imHeight, image->format() );

    for (int i = 0; i < imWidth-1; ++i) {
        for (int j = 0; j < imHeight-1; ++j) {
            double v = tab(i,j);
            if( v > 255){
                v = 255;
            }
            else if( v < 0 ){
                v = 0;
            }
            nouvelleImage->setPixel(i, j, qRgb(v,v,v) );
        }
    }
    return nouvelleImage;
}