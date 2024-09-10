QImage CVlib::generateImage(QImage imageBase, Matrix3f h, QVector<Vector3f> *renderArea)
{
    QVector<Vector3f> areaTemp;
    if(renderArea==0){
        areaTemp.push_back(Vector3f(0,0,1));
        areaTemp.push_back(Vector3f(0,imageBase.height(),1));
        areaTemp.push_back(Vector3f(imageBase.width(),imageBase.height(),1));
        areaTemp.push_back(Vector3f(imageBase.width(),0,1));
    }else{
        areaTemp = *renderArea;
    }
    bounds limits = CVlib::getHomographyBounds(areaTemp, h);

   QSize size;
   float ratio;
   float tamanhoBase =500;
//   if(imageBase.width()>imageBase.height()){
//       tamanhoBase = imageBase.width();
//   }else{
//       tamanhoBase = imageBase.height();
//   }
   if(limits.dx < limits.dy){
       qDebug() << "dx";
       ratio = limits.dx/ limits.dy;
       size = QSize(tamanhoBase* ratio, tamanhoBase);
   }else{
       qDebug() << "dy";
      ratio = limits.dy/ limits.dx;
      size = QSize(tamanhoBase , tamanhoBase*ratio);
      //size = QSize(imageBase.width() * ratio, imageBase.width());
   }
    //ratio = limits.dx/ limits.dy;
    //size = QSize(300 * ratio, 300);
    QImage imageResult = QImage(size.width(), size.height(), QImage::Format_ARGB32);

    //TODO testar imagem horizontal e vertical
    //TODO implementar outros trabalhos
    //Todo entrada de paramentro baseado no tamanho de saida da imagem

    float factor = 1;
    float stepX = limits.dx / size.width() / factor;
    float stepY = limits.dy / size.height() /factor;

    Matrix3f hi = h.inverse().eval();
    for(int j = 0; j<imageResult.height(); j++){
        for(int i = 0; i<imageResult.width(); i++){
            MatrixXf p(3,1);
            p << (limits.left + stepX * i) , (limits.top + stepY * j), 1;
            MatrixXf r(3,1);
            r= CVlib::homography(p, hi);
            QPoint p0(r(0),r(1));
            QColor color(0, 0, 0);
            MatrixXf finalColor(3,1);
            finalColor << 0, 0, 0;
            float ratio = 1;
            if((p0.x() >=0 && p0.x() < imageBase.width())&&(p0.y()>=0 && p0.y()<imageBase.height())){
                ratio = 0;
                for(int offSetY = -1; offSetY <= 1; offSetY++){
                    for(int offSetX = -1; offSetX <= 1; offSetX++){
                        QPoint ptemp(p0.x() + offSetX, p0.y() + offSetY);
                        float ratioX =  r(0)-ptemp.x();
                        float ratioY =  r(1)-ptemp.y();
                        float dist   = std::abs(1 - std::sqrt(std::pow(ratioX, 2) + std::pow(ratioY,2)));
                        ratio += dist;
                        if((ptemp.x() >=0 && ptemp.x() < imageBase.width())&&(ptemp.y()>=0 && ptemp.y()<imageBase.height())){
                            QColor ctemp = imageBase.pixel(ptemp.x(), ptemp.y());
                            MatrixXf cmTemp(3,1);
                            cmTemp << ctemp.redF(), ctemp.greenF(), ctemp.blueF();
                            finalColor += cmTemp * dist;
                        }
                    }
                }
            }
            finalColor = finalColor/ratio;
            color.setRgb(finalColor(0) * 255, finalColor(1) * 255, finalColor(2) * 255);
            imageResult.setPixel(QPoint(i, j), color.rgb());
        }
     }
    return imageResult;
}