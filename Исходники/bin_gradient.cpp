PNM* BinarizationGradient::transform()
{
    int width = image->width();
    int height = image->height();

    PNM* newImage = new PNM(width, height, QImage::Format_Mono);

	if (image->format() == QImage::Format_Mono) {
	}
	else if (image->format() == QImage::Format_Indexed8) {
		int numerator = 0;
		int denominator = 0;
		for (int x=0; x<width; x++) {
			for (int y=0; y<height; y++) {
				QRgb pixel = image->pixel(x,y); // Getting the pixel(x,y) value
				int l=qGray(pixel);

				QRgb pixel1 = getPixel(x+1,y, RepeatEdge);
				QRgb pixel2 = getPixel(x-1,y, RepeatEdge);
				int l1 = qGray(pixel1);
				int l2 = qGray(pixel2);
				int gx = l1-l2;

				pixel1 = getPixel(x,y+1, RepeatEdge);
				pixel2 = getPixel(x,y-1, RepeatEdge);
				l1 = qGray(pixel1);
				l2 = qGray(pixel2);
				int gy = l1-l2;

				int g=max(gx, gy);

				numerator+=(l*g);
				denominator+=g;
			}
		}
		int threshold=(numerator/denominator);
		for (int x=0; x<width; x++) {
			for (int y=0; y<height; y++) {
				QRgb pixel = image->pixel(x,y); // Getting the pixel(x,y) value
				int l = qGray(pixel);

				newImage->setPixel(x,y, l < threshold ? Qt::color0 : Qt::color1);

			}
		}
    }
	else { //if (image->format() == QImage::Format_RGB32)
		int numerator = 0;
		int denominator = 0;
		for (int x=0; x<width; x++) {
			for (int y=0; y<height; y++) {

				QRgb pixel = image->pixel(x,y); // Getting the pixel(x,y) value
				int ri = qRed(pixel);    // Get the 0-255 value of the R channel
                int gi = qGreen(pixel);  // Get the 0-255 value of the G channel
                int bi = qBlue(pixel);   // Get the 0-255 value of the B channel
				int ti = (ri+gi+bi)/3;

				QRgb pixelx1 = getPixel(x+1,y, RepeatEdge);
				QRgb pixelx2 = getPixel(x-1,y, RepeatEdge);
				int rx1 = qRed(pixelx1);    // Get the 0-255 value of the R channel
                int gx1 = qGreen(pixelx1);  // Get the 0-255 value of the G channel
                int bx1 = qBlue(pixelx1);   // Get the 0-255 value of the B channel
				int tx1 = (rx1+gx1+bx1)/3;

				int rx2 = qRed(pixelx2);    // Get the 0-255 value of the R channel
                int gx2 = qGreen(pixelx2);  // Get the 0-255 value of the G channel
                int bx2 = qBlue(pixelx2);   // Get the 0-255 value of the B channel
				int tx2 = (rx2+gx2+bx2)/3;
				int gx = tx1-tx2;

				int pixely1 = getPixel(x,y+1, RepeatEdge);
				int pixely2 = getPixel(x,y-1, RepeatEdge);
				int ry1 = qRed(pixely1);    // Get the 0-255 value of the R channel
                int gy1 = qGreen(pixely1);  // Get the 0-255 value of the G channel
                int by1 = qBlue(pixely1);   // Get the 0-255 value of the B channel
				int ty1 = (ry1+gy1+by1)/3;

				int ry2 = qRed(pixely2);    // Get the 0-255 value of the R channel
                int gy2 = qGreen(pixely2);  // Get the 0-255 value of the G channel
                int by2 = qBlue(pixely2);   // Get the 0-255 value of the B channel
				int ty2 = (ry2+gy2+by2)/3;
				int gy = ty1-ty2;

				int g=max(gx, gy);

				numerator=numerator+(ti*g);
				denominator+=g;
			}
		}
		int threshold=(numerator/denominator);
		for (int x=0; x<width; x++) {
			for (int y=0; y<height; y++) {
				QRgb pixel = image->pixel(x,y); // Getting the pixel(x,y) value
				int r = qRed(pixel);    // Get the 0-255 value of the R channel
                int g = qGreen(pixel);  // Get the 0-255 value of the G channel
                int b = qBlue(pixel);   // Get the 0-255 value of the B channel

				int t = (r+g+b)/3;

				newImage->setPixel(x,y, t < threshold ? Qt::color0 : Qt::color1);
			}
		}
	}
    return newImage;

}