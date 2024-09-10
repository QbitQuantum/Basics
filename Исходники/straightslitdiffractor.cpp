void StraightSlitDiffractor::run(QImage& image) {

    for(int i=-128;i<127;i++){
         for(int j=-128;j<127;j++){
             double dx = (double)i/zoom;
             double dy = (double)j/zoom;
    double PI = 3.1415709;
             int val =(int)((atan(diffractionMethode(dx,dy)*10e20) * 2 / PI)*254);

            color.setHsv(color.hsvHue(),  255,val);

            color.toRgb();

            image.setPixel(i+128,j+128,color.rgb());
         }

    }

    return;
}