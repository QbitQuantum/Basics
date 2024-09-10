Mesh::Mesh(Point points[3])
{
    double trans[3][3] = {
        { 1.0,						1.0,						1.0 },
        { points[1].x - points[0].x, 	points[1].y - points[0].y, 	points[1].z - points[0].z },
        { points[2].x - points[0].x, 	points[2].y - points[0].y, 	points[2].z - points[0].z }
    };
	Matrix<3,3>	calc((const double **) trans);
    Matrix<2,2> adj;
	int idx;
    double mod = 1.0;

	point = Point(points[0]);
	normal = Vector<3>();

	for (idx = 0; idx < 3; idx++) {
		adj = calc.getAdjoint(0, idx);
		normal.setElement(idx, mod * adj.determinant());
        mod *= -1.0;
	}
    normal = normal * (1 / normal.mod());
}