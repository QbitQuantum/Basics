POINT sysuVideo::MVDrawer::lpToDp(RECT *refPU, POINT &lorg, POINT& coordinate)
{
	static POINT transResult;
	static int radius;		// Radius of the pu
	static double x, y;		// Round x and y coordinate
	static int tx, ty;

	if (0 == coordinate.x && 0 == coordinate.y)
	{
		transResult.x = lorg.x;
		transResult.y = lorg.y;
	}
	else
	{
		LongToInt(coordinate.x, &tx);
		LongToInt(coordinate.y, &ty);
		x = (double)tx / 4;
		y = (double)ty / 4;

		/*
		radius = min(refPU->bottom - refPU->top, refPU->right - refPU->left) / 2;
		x = 2 * x + .2;
		y = 2 * y + .2;

		transResult.x = (1 - exp(-1.5 * x * x)) * radius;
		transResult.y = (1 - exp(-1.5 * y * y)) * radius;

		if (abs(x) < 1 && abs(y) < 1)
		{
			transResult.x = transResult.y = 1;
		}				*/

		transResult.x = x;
		transResult.y = y;

		if (abs(transResult.x) < 1 && abs(transResult.y) < 1)
		{
			transResult.x = transResult.y = 1;			
		}
		// Adjust 
		/*transResult.x = min(radius, transResult.x);
		transResult.y = min(radius, transResult.y);*/
		transResult.x = coordinate.x > 0 ? transResult.x : -transResult.x;			
		transResult.y = coordinate.y > 0 ? transResult.y : -transResult.y;
		transResult.x += lorg.x;
		transResult.y += lorg.y;
	}

	return transResult;
}