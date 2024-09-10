std::list<Blob> BlobDetection::Invoke(Image &img) {
	
	std::list<Blob> blobList;

	Point firstPoint(0, -1);
	Point secondPoint(-1, -1);
	Point thirdPoint(-1, 0);
	Point fourthPoint(-1, 1);

	Point _checkPoints[4];

	_checkPoints[0] = firstPoint;
	_checkPoints[1] = secondPoint;
	_checkPoints[2] = thirdPoint;
	_checkPoints[3] = fourthPoint;

	int height = img.GetHeight();
	int width = img.GetWidth();

	int **ary = new int*[height];
	for(int i = 0; i < height; ++i) {
		ary[i] = new int[width];
		for(int z = 0; z < width; z++) {
			ary[i][z] = 0;
		}
	}


	int labelIndex = 0;


	bool neighbourFound = false;
	int smallestNeighbourLabel = 0;

	for(int y = 0; y< height; y++) {
		for(int x = 0; x < width; x++) {
			if(img.GetPixelBlue(x,y) == 255 && img.GetPixelGreen(x,y) == 255 && img.GetPixelRed(x,y) == 255) {
				ary[y][x] = 1;
				//For every pixel check pixels around it.
				for(int listIndex = 0; listIndex < 4; listIndex++) {

					int _x = x + _checkPoints[listIndex].getX();
					int _y = y + _checkPoints[listIndex].getY();

					if(_x > 0 && _y > 0 && ary[_y][_x] > 0) {
						neighbourFound = true;
						if(smallestNeighbourLabel == 0 || ary[_y][_x] < smallestNeighbourLabel) {
							smallestNeighbourLabel = ary[_y][_x];
						}
					}
				}
				if(neighbourFound == false) {
					ary[y][x] = labelIndex++;
				} else {
					ary[y][x] = smallestNeighbourLabel;
				}
				neighbourFound = false;
				smallestNeighbourLabel = 0;
			}
		}
	}

	int *labelColors = new int[labelIndex];

	for(int a = 0; a <labelIndex; a++) {
		labelColors[a] = rand() % 200 + 50;
	}



	for(int yy = 0; yy < height; yy++){
		for(int xx =0; xx < width; xx++) {
			if(ary[yy][xx] > 0) {
				img.SetPixel(xx,yy, labelColors[ary[yy][xx]] << 24 | 0 << 16 | labelColors[ary[yy][xx]] << 8);
			}
		}
	}





	//newImg.SaveImageToFile("ppp_");
	img.SaveImageToFile("changed");
	return blobList;

}