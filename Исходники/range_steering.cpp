void RangeSteering::cycleDock(ros::Duration dt)
{
    ros::Time currentTime = ros::Time::now();
    double w0, w;
    geometry_msgs::Twist vel;
    vel.linear.y = 0.0;
    vel.linear.z = 0.0;
    vel.angular.x = 0.0;
    vel.angular.y = 0.0;

    //~ /* Check if close enough to start local docking */
    //~ double dockStartRange = sqrt(dockStart*dockStart + baseDist*baseDist/4);
    //~
    //~
    //~ if (fabs(leftRange - dockStartRange) < 0.1 && fabs(rightRange - dockStartRange) < 0.1)
    //~ {
    //~ dockStarted = true;
    //~ cout << "Starting Local Docking!" << endl;
    //~ }

    switch (dockState)
    {
    /* Set the turn angle to base, heading is calculated based on the followed radius */
    /* Approximated by 90 degrees (actually dependent on radius and both ranges) */
    case STATE_START_TURN_TO:
    {
        vel.linear.x = 0.0;
        /* Heading dependent on distance */
        double beta = -followDirection * (M_PI / 2 - asin(baseDist / (2 * leftRange)));
        homeHeading = odoHeading - beta;
        dockState = STATE_TURN;
        cout << "Start turning home!, beta: " << beta << ", home: " << homeHeading << ", odoHeading: " << odoHeading
             << endl;
        break;
    }
    case STATE_TURN:
    {

        vel.linear.x = 0.0;
        vel.angular.z = followDirection * turnSpeed;
        double diff = fabs(odoHeading - homeHeading);
        if (diff >= 2 * M_PI)
        {
            diff -= 2 * M_PI;
        }
        else if (diff <= -2 * M_PI)
        {
            diff += 2 * M_PI;
        }

        cout << "----Turning diff: " << diff * 180 / M_PI << "---" << endl;

        /* Stop within +-5 deg of final angle */
        if (diff < 5 * M_PI / 180)
        {
            vel.angular.z = 0;
            dockState = STATE_DOCK_STRAIGHT;
            dockStarted = true;
            cout << "----Turning done, start straight! " << endl;
        }

        cmdPub.publish(vel);
        break;
    }
    case STATE_DOCK_STRAIGHT:
    {
        if (dockStarted)
        {

            w = 0;

            //~ printf("cosA: %f, xL: %f, yL: %f, dx: %f, dy: %f, distToHome: %f, angleToHome: %f\n",  cosAlpha, xL, yL,
            //dx,dy, distToHome, angleToHome);

            /* Check if docking complete */
            if (distToHome < 0.1)
            {
                cout << "Docking Completed!" << endl;
                doDock = false;
                dockStarted = false;
                vel.linear.x = 0.0;
                vel.angular.z = 0.0;
                cmdPub.publish(vel);
            }
            if (doDock)
            {
                vel.linear.x = 0.2; // speed*(distToHome/dockStart);

                errDock = angleToHome;
                if (errOldDock != errDock)
                {
                    dErrDock = errDock - errOldDock;
                }
                errOldDock = errDock;
                w = kpDock * errDock + kdDock * dErrDock;
                vel.angular.z = w;
                cout << "e = " << errDock << ", dErrDock = " << dErrDock << ", w = " << w
                     << ", kpDock*err = " << kpDock* errDock << ",  kdDock*dErrDock = " << kdDock* dErrDock << endl;
                cmdPub.publish(vel);
            }
            break;
        }
    }
    }
}