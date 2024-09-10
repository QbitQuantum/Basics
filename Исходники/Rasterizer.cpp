void setViewportMatrix() 
{
	double x = window_width;
	double y = window_height;
	double xStart = 0;
	double yStart = 0;

	double matrixInput[4][4] = {
		{ (x - xStart) / 2, 0, 0, (x + xStart) / 2}, 
		{ 0, (y - yStart) / 2, 0, (y + yStart) / 2},
		{ 0, 0, 0.5, 0.5 },
		{ 0, 0, 0, 1 }
	};

	viewportMatrix.identity();
	viewportMatrix = Matrix4(matrixInput);
	viewportMatrix.transpose();
}