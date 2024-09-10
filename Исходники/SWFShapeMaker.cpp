void ShapeMaker::arcToR( double rx, double ry, double rotation, bool largeArcFlag, bool sweepFlag, double x, double y ) {
	arcTo(rx, ry, rotation, largeArcFlag, sweepFlag, lastx + x, lasty + y);
}