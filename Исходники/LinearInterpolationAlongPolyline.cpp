MathLib::PiecewiseLinearInterpolation LinearInterpolationAlongPolyline::createInterpolation(
		const GeoLib::Polyline& ply,
		const std::vector<std::size_t>& vec_interpolate_point_ids,
		const std::vector<double>& vec_interpolate_point_values)
{
	std::vector<double> vec_known_dist;
	std::vector<double> vec_known_values;
	vec_known_dist.reserve(vec_interpolate_point_ids.size());
	vec_known_values.reserve(vec_interpolate_point_ids.size());
	for (std::size_t i=0; i<vec_interpolate_point_ids.size(); i++)
	{
		const std::size_t pnt_id = vec_interpolate_point_ids[i];
		if (!ply.isPointIDInPolyline(pnt_id))
			continue;

		for (std::size_t j=0; j<ply.getNumberOfPoints(); j++)
		{
			if (pnt_id == ply.getPointID(j))
			{
				vec_known_dist.push_back(ply.getLength(j));
				vec_known_values.push_back(vec_interpolate_point_values[i]);
				break;
			}
		}
	}

	return MathLib::PiecewiseLinearInterpolation(vec_known_dist, vec_known_values);
}