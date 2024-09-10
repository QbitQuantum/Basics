void entity::detectCollision (struct entity object) {

    long double stepDistance = distance (object.x + object.Vx, object.y + object.Vy) + (Vx + Vy) - (radius + object.radius); //the distance the objects will be at the next move

    if (stepDistance < 0) {
        Vx = object.Vx;
        Vy = object.Vy;

        if (stepDistance < -0.01 ) {
            long double angle = atan2l (object.y - y, object.x - x);
            x -= cos (angle);
            y -= sin (angle);
        }
    }
}