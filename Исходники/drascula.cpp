void DrasculaEngine::reduce_hare_chico(int xx1, int yy1, int xx2, int yy2, int width, int height, int factor, byte *dir_inicio, byte *dir_fin) {
	float totalX, totalY;
	int n, m;
	float pixelX, pixelY;

	newWidth = (width * factor) / 100;
	newHeight = (height * factor) / 100;

	totalX = width / newWidth;
	totalY = height / newHeight;

	pixelX = xx1;
	pixelY = yy1;

	for (n = 0; n < newHeight; n++) {
		for (m = 0; m < newWidth; m++) {
			copyRect((int)pixelX, (int)pixelY, xx2 + m, yy2 + n,
					 1, 1, dir_inicio, dir_fin);

			pixelX += totalX;
		}
		pixelX = xx1;
		pixelY += totalY;
	}
}