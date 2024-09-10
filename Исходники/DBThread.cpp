bool DBThread::RenderMap(QPainter& painter,
                         const RenderMapRequest& request)
{
  QMutexLocker locker(&mutex);

  if (finishedImage==NULL) {
    painter.fillRect(0,0,request.width,request.height,
                     QColor::fromRgbF(0.0,0.0,0.0,1.0));

    painter.setPen(QColor::fromRgbF(1.0,1.0,1.0,1.0));

    QString text("no map available");

    painter.drawText(QRectF(0,0,request.width,request.height),
                     text,
                     QTextOption(Qt::AlignCenter));

    return false;
  }

  osmscout::MercatorProjection projection;

  projection.Set(finishedLon,finishedLat,
                 finishedMagnification,
                 finishedImage->width(),
                 finishedImage->height());

  double lonMin,lonMax,latMin,latMax;

  projection.GetDimensions(lonMin,latMin,lonMax,latMax);

  double d=(lonMax-lonMin)*2*M_PI/360;
  double scaleSize;
  size_t minScaleWidth=request.width/20;
  size_t maxScaleWidth=request.width/10;
  double scaleValue=d*180*60/M_PI*1852.216/(request.width/minScaleWidth);

  //std::cout << "1/10 screen (" << width/10 << " pixels) are: " << scaleValue << " meters" << std::endl;

  scaleValue=pow(10,floor(log10(scaleValue))+1);
  scaleSize=scaleValue/(d*180*60/M_PI*1852.216/request.width);

  if (scaleSize>minScaleWidth && scaleSize/2>minScaleWidth && scaleSize/2<=maxScaleWidth) {
    scaleValue=scaleValue/2;
    scaleSize=scaleSize/2;
  }
  else if (scaleSize>minScaleWidth && scaleSize/5>minScaleWidth && scaleSize/5<=maxScaleWidth) {
    scaleValue=scaleValue/5;
    scaleSize=scaleSize/5;
  }
  else if (scaleSize>minScaleWidth && scaleSize/10>minScaleWidth && scaleSize/10<=maxScaleWidth) {
    scaleValue=scaleValue/10;
    scaleSize=scaleSize/10;
  }

  //std::cout << "VisualScale: value: " << scaleValue << " pixel: " << scaleSize << std::endl;

  double dx=0;
  double dy=0;
  if (request.lon!=finishedLon || request.lat!=finishedLat) {
    dx-=(request.lon-finishedLon)*request.width/(lonMax-lonMin);
    dy+=(request.lat-finishedLat)*request.height/(latMax-latMin);
  }

  if (dx!=0 ||
      dy!=0) {
    osmscout::FillStyleRef unknownFillStyle;
    osmscout::Color        backgroundColor;

    styleConfig->GetUnknownFillStyle(projection,
                                     settings->GetDPI(),
                                     unknownFillStyle);

    backgroundColor=unknownFillStyle->GetFillColor();

    painter.fillRect(0,
                     0,
                     request.width,
                     request.height,
                     QColor::fromRgbF(backgroundColor.GetR(),
                                      backgroundColor.GetG(),
                                      backgroundColor.GetB(),
                                      backgroundColor.GetA()));
  }

  painter.drawImage(dx,dy,*finishedImage);

  return finishedImage->width()==(int)request.width &&
         finishedImage->height()==(int)request.height &&
         finishedLon==request.lon &&
         finishedLat==request.lat &&
         finishedMagnification==request.magnification;
}