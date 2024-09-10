int L2Window::check(){
    QImage image;
    image = capture();
    if(image.isNull()) {
        qDebug("image.isNull()");
        findBars();
        return status;
    }
    if(status == L2_OFF || image_width != image.width() || image_height != image.height()){
        findBars();
        status = L2_OFF;
        image_width = image.width();
        image_height = image.height();
        for(int i = idCP; i < BARNUM; i++ ){
            status |= findXP(i, image);
        }


        for(int j = idCP; j < BARNUM; j++ ){
            for(int i=bar[j].getBegin();i<bar[j].getEnd();i++){
                 image.setPixel(i, bar[j].getY(), qRgb(128, 128, 128));
            }
        }


        image.save("image.png");
        QImage icotmp=image.copy(bar[idCP].getBegin()+18, bar[idCP].getY()-29, 18, 18);
    //    icotmp.save("icotmp.png");
        QPixmap pixmap(20,20);
        pixmap.convertFromImage(icotmp);
    //    pixmap.save("pixmap.png");
        if(L2icon) delete L2icon;
        L2icon = new QIcon(pixmap);

    }

    //QImage barimg=image.copy(bar[idCP].getBegin(), bar[idCP].getY(), bar[idCP].getEnd()-bar[idCP].getBegin(), 1);
    //barimg.save("CP.png");
    for(int i = idCP; i < BARNUM; i++ ){
        bar[i].checkXPBar(image);
    }
    return status;
}