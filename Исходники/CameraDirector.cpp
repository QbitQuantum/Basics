void
CameraDirector::Target(double seconds)
{
    Point target_loc = external_point;

    if (external_ship)
    target_loc = external_ship->Location();

    if (!external_ship || external_ship == ship) {
        if (!external_point) {
            if (ship->Cockpit())
            Virtual(seconds);
            else
            Orbit(seconds);

            return;
        }
    }

    double step  = 1;

    if (requested_mode == MODE_COCKPIT)
    step = transition;

    else if (requested_mode == MODE_TARGET)
    step = 1 - transition;

    if (ship->Cockpit()) {
        // internal padlock:
        Cockpit(seconds);
        camera.Padlock(target_loc, 3*PI/4, PI/8, PI/3);
    }
    else {
        // external padlock:
        Point delta = target_loc - ship->Location();
        delta.Normalize();
        delta *= -5 * ship->Radius() * step;
        delta.y += ship->Radius() * step; 

        camera.MoveTo(ship->Location() + delta);
        camera.LookAt(target_loc);
    }
}