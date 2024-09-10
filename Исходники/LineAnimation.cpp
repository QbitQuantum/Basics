void LineAnimation::initValues()
{

    //IMEDIATELY AFTER KNOWING THE CONTROL POINTS WE CALCULATE THE OVERALL DESTANCE OF THE ANIMATION
    total_delta_x = controlPoints->second->at(X) - controlPoints->first->at(X);
    total_delta_y = controlPoints->second->at(Y) - controlPoints->first->at(Y);
    total_delta_z = controlPoints->second->at(Z) - controlPoints->first->at(Z);
    double dist_x = (double) powl(total_delta_x, 2.0);
    double dist_y = (double) powl(total_delta_y, 2.0);
    double dist_z = (double) powl(total_delta_z, 2.0);

    total_animation_distance = (double) sqrtl(dist_x + dist_y + dist_z);
}