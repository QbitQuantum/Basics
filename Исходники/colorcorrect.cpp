void luma_stretch(QImage &img, const QRect &rect)
{
  int qmin, qmax;
  makeHistogram(img, rect, getLuma, 256, &qmin, &qmax);

  double ymin = qmin/255.0;
  double k = qmax==qmin? 1.0 : 255.0/(qmax-qmin);

  for (int y=rect.top(); y<=rect.bottom(); y++)
    for (int x=rect.left(); x<=rect.right(); x++)
    {
      RGBV c(img.pixel(x, y));
      double yval = getLuma(img.pixel(x, y)); // Current luminance
      double ytgt = (yval - ymin)*k; // Target luminance
      c.mul(ytgt/yval);
      c.clamp();
      img.setPixel(x, y, c.toQRgb());
    }
}