void ImageOperations::drawMaskOnImage( const QImage& qimgTempl, QImage& qimg,
                                       int pos_x, int pos_y, QRgb color )
{
  int tpl_h = qimgTempl.height();
  int tpl_w = qimgTempl.width();
  int img_h = qimg.height();
  int img_w = qimg.width();

  // draw template on output //
  int minx = max(0, pos_x);
  int miny = max(0, pos_y);
  int maxx = min(pos_x + tpl_w, img_w);
  int maxy = min(pos_y + tpl_h, img_h);
  for (int y = miny; y < maxy; y++)
    for (int x = minx; x < maxx;  x++)
      if (qimgTempl.pixel(x-pos_x, y-pos_y) == qRgb(0,0,0))
        qimg.setPixel(x, y, color);
}