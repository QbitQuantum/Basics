/**
 * simple linear in time itnerpolation
 */
void Interpolate_sV::simpleinterpolate(const QImage &prev, const QImage &right, float pos, QImage &output)
{

  QColor colOut;

    for (int y = 0; y < prev.height(); y++) {
        for (int x = 0; x < prev.width(); x++) {
                QRgb lt = prev.pixel(x,y);
                QRgb rt = right.pixel(x,y);

                int red = CLAMP((1-pos)*qRed(lt)+(pos)*qRed(rt),0,255);
                int green = CLAMP((1-pos)*qGreen(lt)+(pos)*qGreen(rt),0,255);
                int blue = CLAMP((1-pos)*qBlue(lt)+(pos)*qBlue(rt),0,255);

                QColor out = QColor::fromRgb(red,green,blue);
                                  
                output.setPixel(x,y, out.rgb());
	   } /* for x */
    } /* for y */
}