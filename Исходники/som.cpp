// subsquare [low,high)
double
SOMap::BMU_range( const SOM_element &s, int &xval, int &yval, subsquare_type &r) {
    double min_distance_squared = DBL_MAX;
    task &my_task = task::self();
    int min_x = -1;
    int min_y = -1;
    for(int x = r.rows().begin(); x != r.rows().end(); ++x) {
        for( int y = r.cols().begin(); y != r.cols().end(); ++y) {
            double dist = distance_squared(s,my_map[x][y]);
            if(dist < min_distance_squared) {
                min_distance_squared = dist;
                min_x = x;
                min_y = y;
            }
            if(cancel_test && my_task.is_cancelled()) {
                xval = r.rows().begin();
                yval = r.cols().begin();
                return DBL_MAX;
            }
        }
    }
    xval = min_x;
    yval = min_y;
    return sqrt(min_distance_squared);
}