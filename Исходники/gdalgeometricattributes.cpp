double GDALGeometricAttributes::aspectRationBB(OGRPolygon * ogr_poly) {
	char* geo;

	ogr_poly->exportToWkt(&geo);
	std::auto_ptr<  SFCGAL::Geometry > g( SFCGAL::io::readWkt(geo));

	SFCGAL::Polygon poly = g->as<SFCGAL::Polygon>();

	if (!poly.toPolygon_2(false).is_simple()) {
		DM::Logger(DM::Warning) << "Polygon is not simple";
		return -1;
	}

	//Transfer to GDAL polygon
	Polygon_with_holes_2 p = poly.toPolygon_with_holes_2(true);


	Polygon_2 p_c;
	CGAL::convex_hull_2(p.outer_boundary().vertices_begin(), p.outer_boundary().vertices_end(), std::back_inserter(p_c));

	//Cacluate Minimal Rect
	Polygon_2 p_m;
	CGAL::min_rectangle_2(p_c.vertices_begin(), p_c.vertices_end(), std::back_inserter(p_m));


	Point_2 p1 = p_m.vertex(0);
	Point_2 p2 = p_m.vertex(1);

	Point_2 p3 = p_m.vertex(2);
	Point_2 p4 = p_m.vertex(3);

	Vector_2 v1 = (p2-p1);
	Vector_2 v2 = (p3-p2);

	double l1 = sqrt(CGAL::to_double(v1.squared_length()));
	double l2 = sqrt(CGAL::to_double(v2.squared_length()));

	double aspect_ration = l1/l2;

	if (aspect_ration < 1.0) {
		aspect_ration = 1.0/aspect_ration;
	}

	return aspect_ration;
}