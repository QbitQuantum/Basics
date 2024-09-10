PNM* MapNormal::transform()
{
    int width  = image->width(),
        height = image->height();

    double strength = getParameter("strength").toDouble();

    PNM* newImage = new PNM(width, height, image->format());

	PNM* heightImage = MapHeight(image).transform();

	math::matrix<double>* G_x = EdgeSobel(heightImage).rawHorizontalDetection();
	math::matrix<double>* G_y = EdgeSobel(heightImage).rawVerticalDetection();

	for (int i=0; i<width;i++) {
		for (int j=0; j<height;j++) {
			double gx = (*G_x)(i,j);
			double gy = (*G_y)(i,j);
			double dX = gx/255;
			double dY = gy/255;
			double dZ = 1/strength;
			double length = sqrt(pow(dX,2)+pow(dY,2)+pow(dZ,2));
			dX/=length;
			dY/=length;
			dZ/=length;
			double r = (dX + 1.0)*(255/strength);
			double g = (dY + 1.0)*(255/strength);
			double b = (dZ + 1.0)*(255/strength);
			
			QColor newPixel = QColor(r,g,b);
			newImage->setPixel(i,j, newPixel.rgb());

		}
	}

    return newImage;
}