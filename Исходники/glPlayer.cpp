void Player::SpeedUp(Vec3 normal)
{
    Vec3 fwd = ForwardDir(normal);
    fwd.normalize();
    Vec3 lft = normal.cross(fwd);
    Vec3 deltaSpeed = -_velocity;
    deltaSpeed.normalize();
    deltaSpeed /= 2;
    if (_wPressed)
    {
        deltaSpeed += fwd;
    }
    if (_sPressed)
    {
        deltaSpeed -= fwd;
    }
    if (_aPressed)
    {
        deltaSpeed += lft;
    }
    if (_dPressed)
    {
        deltaSpeed -= lft;
    }
    deltaSpeed.normalize();
    deltaSpeed *= 0.1;
    _velocity += deltaSpeed;

    LimitSpeed();
    /*
    printf("%9.3f %9.3f %9.3f %9.3f %9.3f %9.3f %9.3f %9.3f %9.3f\n", _velocity.x, _velocity.y, _velocity.z, _position.x, _position.y, _position.z,
    _lookat.x, _lookat.y, _lookat.z);
    */
}