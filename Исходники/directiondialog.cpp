double DirectionCanvas::translateMouseCoords(double trans_x, double trans_y)
{
	// We now have 4 squares. One four every corner.
	// With a cross in the middle.
	// For every square we calculate a different tangent
	// therefore we have to add of substract a number of degrees
	double result = 0;
	if (trans_x >= 0 && trans_y >= 0) {
		// Right down
		double arc_tan = trans_y / trans_x;
		result = 90 + (atan(arc_tan)) * (180/M_PI);
	} else if (trans_x <= 0 && trans_y >= 0) {
		// Left down
		trans_x = trans_x * -1;
		double arc_tan = trans_y / trans_x;
		result = 270 - (atan(arc_tan)) * (180/M_PI);
	} else if (trans_x >= 0 && trans_y <= 0) {
		// Right up
		trans_y = trans_y * -1;
		double arc_tan = trans_y / trans_x;
		result = 90 - (atan(arc_tan)) * (180/M_PI);
	} else if (trans_x <= 0 && trans_y <= 0) {
		// Left up
		trans_x = trans_x * -1;
		trans_y = trans_y * -1;
		double arc_tan = trans_y / trans_x;
		result = 270 + (atan(arc_tan)) * (180/M_PI);
	}
	return result;
}