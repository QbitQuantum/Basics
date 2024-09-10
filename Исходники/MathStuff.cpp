/* MathStuff::lineSide
 * Returns the side of the line that the point lies on.  Positive is
 * front, negative is back, zero is on the line
 *******************************************************************/
double MathStuff::lineSide(fpoint2_t point, fseg2_t line)
{
	return (point.x - line.x1()) * line.height() - (point.y - line.y1()) * line.width();
}