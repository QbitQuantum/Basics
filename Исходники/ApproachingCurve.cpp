void ApproachingCurve::updateSensors(CarState &cs) {
    float speedFactor = 5000;                       //The target speed is obtained through a constant factor

    if (cs.getFocus(2) == -1) {                     //Focus sensors are available only once per second
        // cout << "FOCUS MISS!" << endl;
        rSensor = cs.getTrack(10);                  //Use track sensors
        cSensor = cs.getTrack(9);
        lSensor = cs.getTrack(8);
    }
    else {
        // cout << "FOCUS HIT!" << endl;
        rSensor = cs.getFocus(3);                   //Use focus sensors
        cSensor = cs.getFocus(2);
        lSensor = cs.getFocus(1);
    }
    targetSpeed = BASE_SPEED + speedFactor / fabs(lSensor - rSensor);

    sensorsAreUpdated = true;
}