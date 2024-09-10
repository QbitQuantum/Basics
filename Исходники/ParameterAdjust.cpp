std::vector<float> CalBarycentric(const std::vector<Point2f> &points, Point2f tf)
{
	Point3f p1 = Point3f(points[0].x, points[0].y, 0.0f);
	Point3f p2 = Point3f(points[1].x, points[1].y, 0.0f);
	Point3f p3 = Point3f(points[2].x, points[2].y, 0.0f);

	Point3f f(tf.x, tf.y, 0.0f);
	Point3f f1 = p1 - f;
	Point3f f2 = p2 - f;
	Point3f f3 = p3 - f;

	Point3f va = (p1 - p2).cross(p1 - p3);
	Point3f va1 = f2.cross(f3);
	Point3f va2 = f3.cross(f1);
	Point3f va3 = f1.cross(f2);

	float a = CalLength(va);
	float a1 = CalLength(va1) / a * sign(va.dot(va1));
	float a2 = CalLength(va2) / a * sign(va.dot(va2));
	float a3 = CalLength(va3) / a * sign(va.dot(va3));

	std::vector<float> w;
	w.push_back(a1);
	w.push_back(a2);
	w.push_back(a3);
	return w;
}