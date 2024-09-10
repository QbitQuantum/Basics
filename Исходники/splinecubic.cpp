double SplineCubic::getCurvature(float distance) const
{
	if(distance < 0.0) distance = getCursor();	// No parameter distance given, use cursor position
	double t = distanceToT(distance);

	// http://de.wikipedia.org/wiki/Krümmung
	// http://upload.wikimedia.org/math/a/6/3/a63b7d087733b448c4f798d16d65b421.png
	double val1X = evaluate1t(t).x();
	double val1Y = evaluate1t(t).y();
	double val2X = evaluate2t(t).x();
	double val2Y = evaluate2t(t).y();

// 	qDebug() << "SplineCubic::getCurvature(): val1X" << val1X << "val1Y" << val1Y << "val2X" << val2X << "val2Y" << val2Y;

	double curvature =
		(val1X * val2Y - val2X * val1Y)
		/
		pow(val1X*val1X + val1Y*val1Y, 3.0/2.0);

// 	qDebug("SplineCubic::getCurvature(): distance %.3F, t is %.6F, curvature is %.6F", distance, t, curvature);

	return curvature;
}