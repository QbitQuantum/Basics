Point2D VKDrone::futurePosition(const GameObject *obj, double laserSpeed) {
    // Distance to obj.
    double dist = sqrt(pow(obj->posx - myShip->posx, 2) +
                       pow(obj->posy - myShip->posy, 2));

    // Time needed to a laser beam travel all dist.
    double dt = dist / laserSpeed;

    Point2D nextPos;
    nextPos.x = obj->posx + obj->velx * dt;
    nextPos.y = obj->posy + obj->vely * dt;

    return nextPos;
}