double great_circle_distance::operator() (coord2d const& pt0, 
                                          coord2d const& pt1) const
{
    double lon0 = pt0.x * deg2rad;
    double lat0 = pt0.y * deg2rad;
    double lon1 = pt1.x * deg2rad;
    double lat1 = pt1.y * deg2rad;
      
    double dlat = lat1 - lat0;
    double dlon = lon1 - lon0;
      
    double sin_dlat = sin(0.5 * dlat);
    double sin_dlon = sin(0.5 * dlon);
      
    double a = pow(sin_dlat,2.0) + cos(lat0)*cos(lat1)*pow(sin_dlon,2.0);
    double c = 2 * atan2(sqrt(a),sqrt(1 - a));
    return R * c; 
}