void ImageSaver::saveFrame() {

    int w = glutGet(GLUT_WINDOW_WIDTH);
    int h = glutGet(GLUT_WINDOW_HEIGHT);

    _frameCount++;
    std::stringstream filename(stringstream::in | stringstream::out);
    filename << _imgOutDir << _prefix;
    filename << std::setfill('0') << setw(6) << _frameCount << ".bmp";
    //filename << _frameCount << ".bmp";
    cout << "Save frame " << _frameCount << endl;

    Image* img = new Image(w, h);

    /******************************
     * Here we draw!
     ******************************/
    unsigned char *image;

    /* Allocate our buffer for the image */
    try {
        image = new unsigned char[3*w*h];
    } catch (bad_alloc&) {
        cout << "Couldn't allocate memory!" << endl;
        delete img;
        return;
    }
    glPixelStorei(GL_PACK_ALIGNMENT,1);
    glReadBuffer(GL_BACK_LEFT);
    glReadPixels(0,0,w,h,GL_RGB,GL_UNSIGNED_BYTE,image);

    unsigned char r, g, b;
    for (int j=h-1; j>=0; j--) {
        for (int i=0; i<w; i++) {
            r = image[3*j*w+3*i+0];
            g = image[3*j*w+3*i+1];
            b = image[3*j*w+3*i+2];
            img->setPixel(i, j, r, g, b);
        }
    }
    img->saveAsBMP(filename.str());
    delete [] image;
    delete img;

}