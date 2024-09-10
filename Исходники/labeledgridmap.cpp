Image* LabeledGridMap::convertToImage(int w) const{
	Image *img =new Image(this->width, this->height);
	for (int x=0; x < this->width; x++){
		for (int y=0; y < height; y++){
			unsigned char* color = rgb_colors[ getCellValue(x,y) ];
			img->setPixel(x,height-y-1,color);
		}
	}
	if (w>0 && img->getWidth()!=w) img->scale(w);

	return img;
}