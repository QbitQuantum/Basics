Color Sphere::calculateTextureFromMaterial(Point intercept, bool diagnosticEnabled) {
	BMP* texture;
	texture = &this->texture;
	int height = texture->TellHeight();
	int width  = texture->TellWidth();

	Vector vectorToIntercept = intercept - origin;
	vectorToIntercept.normalize();
	double u = 0.5 + atan2(vectorToIntercept.z,vectorToIntercept.x) / 2 / 3.1415;
	double v = 0.5 - asin(vectorToIntercept.y) / 3.1415;

	int pixelX = abs((int)(u * width));
	int pixelY = abs((int)(v * height));
	pixelX %= width;
	pixelY %= height;
	Color matColor;

	if(diagnosticEnabled) {
		matColor = Color(v,0,sin(u * 3.1415));
	}
	else {
		matColor.r = texture->GetPixel(pixelX,pixelY).Red/255.f;
		matColor.g = texture->GetPixel(pixelX,pixelY).Green/255.f;
		matColor.b = texture->GetPixel(pixelX,pixelY).Blue/255.f;
	}

	return matColor;
}