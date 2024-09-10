//uses some trigonometry magic to update the position of the current point based on a limited speed given by SPEED_OF_MOVEMENT
Point speedGovernor(Point current, Point destination, double dist) {
    double x_dist = destination.x - current.x;
    double y_dist = destination.y - current.y;
    double distance = sqrt(pow((x_dist), 2) + pow((y_dist), 2));
    double angle = atan2(y_dist, x_dist);
    if (distance > dist) {
        distance = dist;
        x_dist = distance*(cos(angle));
        y_dist = distance*(sin(angle));
    }
    current.x = current.x + x_dist;
    current.y = current.y + y_dist;
    return current;
}