PNM* HistogramStretching::transform()
{
    int width  = image->width();
    int height = image->height();

    PNM* newImage = new PNM(width, height, image->format());

	QHash<int, int>::const_iterator i;
	int minR = 255;
	int maxR = 0;
	for (i=image->getHistogram()->get(Histogram::RChannel)->constBegin();
			i!=image->getHistogram()->get(Histogram::RChannel)->constEnd();++i) {
		if (i.key()>maxR) {
			maxR=i.key();
		}
		if (i.key()<minR) {
			minR=i.key();
		}

	}
	int minG = 255;
	int maxG = 0;
	for (i=image->getHistogram()->get(Histogram::GChannel)->constBegin();
			i!=image->getHistogram()->get(Histogram::GChannel)->constEnd();++i) {
		if (i.value()!=0 && i.key()>maxG) {
			maxG=i.key();
		}
		if (i.value()!=0 && i.key()<minG) {
			minG=i.key();
		}
	}
	int minB = 255;
	int maxB = 0;
	for (i=image->getHistogram()->get(Histogram::BChannel)->constBegin();
			i!=image->getHistogram()->get(Histogram::BChannel)->constEnd();++i) {
		if (i.value()!=0 && i.key()>maxB) {
			maxB=i.key();
		}
		if (i.value()!=0 && i.key()<minB) {
			minB=i.key();
		}
	}
	int minL = 255;
	int maxL = 0;
	for (i=image->getHistogram()->get(Histogram::LChannel)->constBegin();
			i!=image->getHistogram()->get(Histogram::LChannel)->constEnd();++i) {
		if (i.value()!=0 && i.key()>maxL) {
			maxL=i.key();
		}
		if (i.value()!=0 && i.key()<minL) {
			minL=i.key();
		}
	}

	if (image->format() == QImage::Format_Indexed8)
	{
		for (int x=0; x<width; x++) {
			for (int y=0; y<height; y++)
			{
	            QRgb pixel = image->pixel(x,y); // Getting the pixel(x,y) value
				int l = qGray(pixel);    // Get the 0-255 value of the L channel
				l = (255/(maxL-minL))*(l-minL);

                newImage->setPixel(x,y, l);
			}
		}
	}

	else
	{
		for (int x=0; x<width; x++) {
			for (int y=0; y<height; y++)
			{
				QRgb pixel = image->pixel(x,y); // Getting the pixel(x,y) value

				int r = qRed(pixel);    // Get the 0-255 value of the R channel
				r = (255/(maxR-minR))*(r-minR);
				int g = qGreen(pixel);  // Get the 0-255 value of the G channel
				g = (255/(maxG-minG))*(g-minG);
				int b = qBlue(pixel);   // Get the 0-255 value of the B channel
				b = (255/(maxB-minB))*(b-minB);

				QColor newPixel = QColor(r,g,b);
				newImage->setPixel(x,y, newPixel.rgb());

			}
		}
	}
   

    return newImage;
}