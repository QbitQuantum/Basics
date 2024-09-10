void ribi::ImageRotaterMainDialog::Rotate(
  const QImage& pixmapOriginal,
  QImage& pixmapResult,
  const double angle)
{
  QImage imageOriginal = pixmapOriginal; //pixmapOriginal.toImage();
  QImage imageResult = pixmapResult;     //pixmapResult.toImage();
  const int maxx = imageResult.width();
  const int maxy = imageResult.height();
  const double midx = static_cast<double>(maxx) / 2.0;
  const double midy = static_cast<double>(maxy) / 2.0;

  for (int y=0; y!=maxy; ++y)
  {
    for(int x=0; x!=maxx; ++x)
    {
      const double dx1 = static_cast<double>(x) - midx;
      const double dy1 = static_cast<double>(y) - midy;
      double dx2, dy2; //Coordinats in original
      Translate(dx1,dy1,angle,dx2,dy2);
      const double x2 =
      (static_cast<double>(imageOriginal.width() ) / 2.0) + dx2;
      const double y2 =
      (static_cast<double>(imageOriginal.height()) / 2.0) + dy2;
      if ( x2 < 1.0
        || y2 < 1.0
        || x2 >= imageOriginal.width() - 1.0
        || y2 >= imageOriginal.height() - 1.0
        )
      { //Out of range
        //SetPixel(imageResult,x,y,qRgb(0,0,0));
        imageResult.setPixel(x,y,qRgb(0,0,0));
        continue;
      }
      const QRgb rgb {
        GetPixel(imageOriginal,x2,y2)
      };
      imageResult.setPixel(x,y,rgb);
      //SetPixel(imageResult,x,y,rgb);
    }
  }
  pixmapResult = imageResult;
  //pixmapResult = QPixmap::fromImage(imageResult);
}