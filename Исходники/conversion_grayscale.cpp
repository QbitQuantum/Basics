PNM* ConversionGrayscale::transform()
{
   // qDebug() << Q_FUNC_INFO << "Not implemented yet!";

    int width = image->width();
    int height = image->height();

    PNM* newImage = new PNM(width, height, QImage::Format_Indexed8);

    if (image->format() == QImage::Format_Mono)
    {
		for (int x = 0; x<width; x++)
			for (int y = 0; y<height; y++)
			{
			QColor color = QColor::fromRgb(image->pixel(x, y)); // Getting the pixel(x,y) value

			newImage->setPixel(x, y, color == Qt::white ? Qt::color1 : Qt::color0);
			}

    }
    else // if (image->format() == QImage::Format_RGB32)
    {
		for (int x = 0; x<width; x++)
			for (int y = 0; y<height; y++)
			{
			QRgb pixel = image->pixel(x, y); // Getting the pixel(x,y) value

			int r = qRed(pixel);    // Get the 0-255 value of the R channel
			int g = qGreen(pixel);  // Get the 0-255 value of the G channel
			int b = qBlue(pixel);   // Get the 0-255 value of the B channel
			r = (int) floor(r*0.3);
			g = (int) floor(g*0.6);
			b = (int) floor(b*0.1);
			//QColor newPixel = QColor(r, g, b);
			newImage->setPixel(x, y, r + g + b);
			}

    }

    return newImage;
}