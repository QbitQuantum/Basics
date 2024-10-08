bool collidechecker::check(Eigen::Affine2d center, const double & width, const double & height,
        double & guaranteed_clearance, unsigned int calldepth) {

    if (calldepth > 5) {
        return true;
    }

    double radius_circumcircle = sqrt(width * width + height * height) / 2.0f;

    int map_x = 0;
    int map_y = 0;


    if (!map_ptr_->world2map(center.translation().x(), center.translation().y(), map_x, map_y)) {
        return true; 
    }

    double dist_center = -INFINITY;
    dist_center = map_ptr_->getValue(map_x, map_y) - step_;


    if (dist_center >= radius_circumcircle) {
        guaranteed_clearance = dist_center - radius_circumcircle;
        return false;
    }


    double radius_incircle = (width < height ? width : height) / 2.0f;

    if (dist_center <= radius_incircle) {
        return true;
    }

    double delta_x, delta_y;
    double h_new, w_new;
    if (width <= height) {
        double h_clear = sqrt(dist_center * dist_center - (width * width) / 4.0); // - 0.025;
        h_new = height / 2.0 - h_clear;

        w_new = width;

        delta_x = 0;
        delta_y = h_clear + h_new / 2.0f;
    } else {
        double w_clear = sqrt(dist_center * dist_center - (height * height) / 4.0); // - 0.025;
        w_new = width / 2.0 - w_clear;
        h_new = height;
        delta_x = w_clear + w_new / 2.0f;
        delta_y = 0;

    }
    Eigen::Affine2d delta(Eigen::Translation2d(delta_x, delta_y));
    double guaranteed_clearance_1 = 0;
    double guaranteed_clearance_2 = 0;
    bool result = (check(center * delta, w_new, h_new, guaranteed_clearance_1, calldepth + 1)
            || check(center * delta.inverse(), w_new, h_new, guaranteed_clearance_2, calldepth + 1));
    if (!result) {
        guaranteed_clearance = guaranteed_clearance_1 < guaranteed_clearance_2 ? guaranteed_clearance_1 : guaranteed_clearance_2;
        double guaranteed_clearance_center = dist_center - radius_incircle;
        guaranteed_clearance = guaranteed_clearance < guaranteed_clearance_center ? guaranteed_clearance : guaranteed_clearance_center;
    }
    return result;
}