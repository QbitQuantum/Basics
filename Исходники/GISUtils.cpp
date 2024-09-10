void	Quad_1to4(const Point2& ctr, double heading, double len_mtr, double width_mtr, Point2 corners[4])
{
	Vector2		dir;

	NorthHeading2VectorMeters(ctr, ctr, heading,dir);
	dir.normalize();
	Vector2 right(dir.perpendicular_cw());

	Point2	zero(0,0);
	corners[0] = zero - dir * len_mtr * 0.5 - right * width_mtr * 0.5;
	corners[1] = zero + dir * len_mtr * 0.5 - right * width_mtr * 0.5;
	corners[2] = zero + dir * len_mtr * 0.5 + right * width_mtr * 0.5;
	corners[3] = zero - dir * len_mtr * 0.5 + right * width_mtr * 0.5;

	MetersToLLE(ctr, 4, corners);
}