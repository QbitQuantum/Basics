/// update - update circle controller
void AC_Circle::update()
{
    // calculate dt
    uint32_t now = hal.scheduler->millis();
    float dt = (now - _last_update) / 1000.0f;

    // update circle position at 10hz
    if (dt > 0.095f) {

        // double check dt is reasonable
        if (dt >= 1.0f) {
            dt = 0.0;
        }
        // capture time since last iteration
        _last_update = now;

        // ramp up angular velocity to maximum
        if (_rate >= 0) {
            if (_angular_vel < _angular_vel_max) {
                _angular_vel += _angular_accel * dt;
                _angular_vel = constrain_float(_angular_vel, 0, _angular_vel_max);
            }
        } else {
            if (_angular_vel > _angular_vel_max) {
                _angular_vel += _angular_accel * dt;
                _angular_vel = constrain_float(_angular_vel, _angular_vel_max, 0);
            }
        }

        // update the target angle and total angle traveled
        float angle_change = _angular_vel * dt;
        _angle += angle_change;
        _angle = wrap_PI(_angle);
        _angle_total += angle_change;

        // if the circle_radius is zero we are doing panorama so no need to update loiter target
        if (_radius != 0.0) {
            // calculate target position
            Vector3f target;
            target.x = _center.x + _radius * cosf(-_angle);
            target.y = _center.y - _radius * sinf(-_angle);
            target.z = _pos_control.get_alt_target();

            // update position controller target
            _pos_control.set_pos_target(target);

            // heading is 180 deg from vehicles target position around circle
            _yaw = wrap_PI(_angle-PI) * AC_CIRCLE_DEGX100;
        } else {
            // set target position to center
            Vector3f target;
            target.x = _center.x;
            target.y = _center.y;
            target.z = _pos_control.get_alt_target();

            // update position controller target
            _pos_control.set_pos_target(target);

            // heading is same as _angle but converted to centi-degrees
            _yaw = _angle * AC_CIRCLE_DEGX100;
        }

        // trigger position controller on next update
        _pos_control.trigger_xy();
    }

    // run loiter's position to velocity step
    _pos_control.update_pos_controller(false);
}