void MotionControl::run() {
    if (!_robot) return;

    const MotionConstraints& constraints = _robot->motionConstraints();

    // update PID parameters
    _positionXController.kp = *_robot->config->translation.p;
    _positionXController.ki = *_robot->config->translation.i;
    _positionXController.setWindup(*_robot->config->translation.i_windup);
    _positionXController.kd = *_robot->config->translation.d;
    _positionYController.kp = *_robot->config->translation.p;
    _positionYController.ki = *_robot->config->translation.i;
    _positionYController.setWindup(*_robot->config->translation.i_windup);
    _positionYController.kd = *_robot->config->translation.d;
    _angleController.kp = *_robot->config->rotation.p;
    _angleController.ki = *_robot->config->rotation.i;
    _angleController.kd = *_robot->config->rotation.d;

    RJ::Seconds timeIntoPath =
        (RJ::now() - _robot->path().startTime()) + RJ::Seconds(1.0 / 60);

    // evaluate path - where should we be right now?
    boost::optional<RobotInstant> optTarget =
        _robot->path().evaluate(timeIntoPath);

    if (!optTarget) {
        optTarget = _robot->path().end();
        _robot->state()->drawCircle(optTarget->motion.pos, .15, Qt::red,
                                    "Planning");
    } else {
        Point start = _robot->pos;
        _robot->state()->drawCircle(optTarget->motion.pos, .15, Qt::green,
                                    "Planning");
    }

    // Angle control //////////////////////////////////////////////////
    ////////////////////////////////////////////////////////////////////

    float targetW = 0;
    auto& rotationCommand = _robot->rotationCommand();
    const auto& rotationConstraints = _robot->rotationConstraints();

    boost::optional<Geometry2d::Point> targetPt;
    const auto& motionCommand = _robot->motionCommand();

    boost::optional<float> targetAngleFinal;
    // if (motionCommand->getCommandType() == MotionCommand::Pivot) {
    //    PivotCommand command =
    //    *static_cast<PivotCommand*>(motionCommand.get());
    //    targetPt = command.pivotTarget;
    //} else {
    if (optTarget) {
        if (optTarget->angle) {
            if (optTarget->angle->angle) {
                targetAngleFinal = *optTarget->angle->angle;
            }
        }
    }
    //}

    if (targetPt) {
        // fixing the angle ensures that we don't go the long way around to get
        // to our final angle
        targetAngleFinal = (*targetPt - _robot->pos).angle();
    }

    if (!targetAngleFinal) {
        _targetAngleVel(0);
    } else {
        float angleError = fixAngleRadians(*targetAngleFinal - _robot->angle);

        targetW = _angleController.run(angleError);

        // limit W
        if (abs(targetW) > (rotationConstraints.maxSpeed)) {
            if (targetW > 0) {
                targetW = (rotationConstraints.maxSpeed);
            } else {
                targetW = -(rotationConstraints.maxSpeed);
            }
        }

        /*
        _robot->addText(QString("targetW: %1").arg(targetW));
        _robot->addText(QString("angleError: %1").arg(angleError));
        _robot->addText(QString("targetGlobalAngle: %1").arg(targetAngleFinal));
        _robot->addText(QString("angle: %1").arg(_robot->angle));
        */
        _targetAngleVel(targetW);
    }

    // handle body velocity for pivot command
    /*
    if (motionCommand->getCommandType() == MotionCommand::Pivot) {
        float r = Robot_Radius;
        const float FudgeFactor = *_robot->config->pivotVelMultiplier;
        float speed = RadiansToDegrees(r * targetW * FudgeFactor);
        Point vel(speed, 0);

        // the robot body coordinate system is wierd...
        vel.rotate(-M_PI_2);

        _targetBodyVel(vel);

        return;  // pivot handles both angle and position
    }
     */

    // Position control ///////////////////////////////////////////////
    ////////////////////////////////////////////////////////////////////
    MotionInstant target = optTarget->motion;

    // tracking error
    Point posError = target.pos - _robot->pos;

    // acceleration factor
    Point acceleration;
    boost::optional<RobotInstant> nextTarget =
        _robot->path().evaluate(timeIntoPath + RJ::Seconds(1) / 60.0);
    if (nextTarget) {
        acceleration = (nextTarget->motion.vel - target.vel) / 60.0f;
    } else {
        acceleration = {0, 0};
    }
    Point accelFactor =
        acceleration * 60.0f * (*_robot->config->accelerationMultiplier);

    target.vel += accelFactor;

    // PID on position
    target.vel.x() += _positionXController.run(posError.x());
    target.vel.y() += _positionYController.run(posError.y());

    // draw target pt
    _robot->state()->drawCircle(target.pos, .04, Qt::red, "MotionControl");
    _robot->state()->drawLine(target.pos, target.pos + target.vel, Qt::blue,
                              "MotionControl");

    // Clamp World Acceleration
    auto dt = RJ::Seconds(RJ::now() - _lastCmdTime);
    Point targetAccel = (target.vel - _lastWorldVelCmd) / dt.count();
    targetAccel.clamp(*_max_acceleration);

    target.vel = _lastWorldVelCmd + targetAccel * dt.count();

    _lastWorldVelCmd = target.vel;
    _lastCmdTime = RJ::now();

    // convert from world to body coordinates
    // the +y axis of the robot points forwards
    target.vel = target.vel.rotated(M_PI_2 - _robot->angle);

    this->_targetBodyVel(target.vel);
}