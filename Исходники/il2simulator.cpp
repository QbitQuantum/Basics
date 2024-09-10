/**
 * process data string from flight simulator
 */
void IL2Simulator::processUpdate(const QByteArray& inp)
{
    // save old flight data to calculate delta's later
    old=current;
    QString data(inp);
    // Split
    QStringList fields = data.split("/");

    // split up response string
    int t;
    for (t=0; t<fields.length(); t++) {
        QStringList values = fields[t].split("\\");
        // parse values
        if (values.length()>=2) {
            int id = values[0].toInt();
            float value = values[1].toFloat();
            switch (id) {
            case 30:
                current.cas=value * KM_PER_HOUR2METERS_PER_SECOND;
                break;
            case 32:
                current.dZ=value;
                break;
            case 40:
                current.Z=value;
                break;
            case 42:
                current.azimuth=value;
                break;
            case 46:
                current.roll=-value;
                break;
            case 48:
                current.pitch=value;
                break;
            }
        }
    }

    // measure time
    current.dT = ((float)time->restart()) / 1000.0;
    if (current.dT<0.001)  current.dT=0.001;
    current.T = old.T+current.dT;
    current.i = old.i+1;
    if (current.i==1) {
        old.dRoll=0;
        old.dPitch=0;
        old.dAzimuth=0;
        old.ddX=0;
        old.ddX=0;
        old.ddX=0;
    }

    // calculate TAS from alt and CAS
    current.tas = cas2tas(current.cas, current.Z, airParameters, GRAVITY);

    // assume the plane actually flies straight and no wind
    // groundspeed is horizontal vector of TAS
    current.groundspeed = current.tas*cos(current.pitch*DEG2RAD);
    // x and y vector components
    current.dX = current.groundspeed*sin(current.azimuth*DEG2RAD);
    current.dY = current.groundspeed*cos(current.azimuth*DEG2RAD);

    // simple IMS - integration over time the easy way...
    current.X = old.X + (current.dX*current.dT);
    current.Y = old.Y + (current.dY*current.dT);

    // accelerations (filtered)
    if (isnan(old.ddX) || isinf(old.ddX)) old.ddX=0;
    if (isnan(old.ddY) || isinf(old.ddY)) old.ddY=0;
    if (isnan(old.ddZ) || isinf(old.ddZ)) old.ddZ=0;
#define SPEED_FILTER 10
    current.ddX = ((current.dX-old.dX)/current.dT + SPEED_FILTER * (old.ddX)) / (SPEED_FILTER+1);
    current.ddY = ((current.dY-old.dY)/current.dT + SPEED_FILTER * (old.ddY)) / (SPEED_FILTER+1);
    current.ddZ = ((current.dZ-old.dZ)/current.dT + SPEED_FILTER * (old.ddZ)) / (SPEED_FILTER+1);

#define TURN_FILTER 10
    // turn speeds (filtered)
    if (isnan(old.dAzimuth) || isinf(old.dAzimuth)) old.dAzimuth=0;
    if (isnan(old.dPitch) || isinf(old.dPitch)) old.dPitch=0;
    if (isnan(old.dRoll) || isinf(old.dRoll)) old.dRoll=0;
    current.dAzimuth = (angleDifference(current.azimuth,old.azimuth)/current.dT + TURN_FILTER * (old.dAzimuth)) / (TURN_FILTER+1);
    current.dPitch   = (angleDifference(current.pitch,old.pitch)/current.dT     + TURN_FILTER * (old.dPitch))   / (TURN_FILTER+1);
    current.dRoll    = (angleDifference(current.roll,old.roll)/current.dT       + TURN_FILTER * (old.dRoll))    / (TURN_FILTER+1);

    ///////
    // Output formatting
    ///////
    Output2Hardware out;
    memset(&out, 0, sizeof(Output2Hardware));

    // Compute rotation matrix, for later calculations
    float Rbe[3][3];
    float rpy[3];
    float quat[4];
    rpy[0]=current.roll;
    rpy[1]=current.pitch;
    rpy[2]=current.azimuth;
    Utils::CoordinateConversions().RPY2Quaternion(rpy,quat);
    Utils::CoordinateConversions().Quaternion2R(quat,Rbe);

    // Update GPS Position objects, convertin from the current NED position
    // to LLA
    double HomeLLA[3];
    double LLA[3];
    double NED[3];
    HomeLLA[0]=settings.latitude.toFloat();
    HomeLLA[1]=settings.longitude.toFloat();
    HomeLLA[2]=0;
    NED[0] = current.Y;
    NED[1] = current.X;
    NED[2] = -current.Z;
    Utils::CoordinateConversions().NED2LLA_HomeLLA(HomeLLA, NED, LLA);
    out.latitude = LLA[0];
    out.longitude = LLA[1];
    out.groundspeed = current.groundspeed;

    out.calibratedAirspeed = current.cas;
    out.trueAirspeed=cas2tas(current.cas, current.Z, airParameters, GRAVITY);

    out.dstN=current.Y;
    out.dstE=current.X;
    out.dstD=-current.Z;

    // Update BaroAltitude object
    out.altitude = current.Z;
    out.agl = current.Z;
    out.temperature = airParameters.groundTemp + (current.Z * airParameters.tempLapseRate) - 273.0;
    out.pressure = airPressureFromAltitude(current.Z, airParameters, GRAVITY) ; // kpa


    // Update attActual object
    out.roll = current.roll;   //roll;
    out.pitch = current.pitch;  // pitch
    out.heading = current.azimuth; // yaw


    // Update VelocityActual.{North,East,Down}
    out.velNorth = current.dY;
    out.velEast = current.dX;
    out.velDown = -current.dZ;

    // rotate turn rates and accelerations into body frame
    // (note: rotation deltas are NOT in NED frame but in RPY - manual conversion!)
    out.rollRate = current.dRoll;
    out.pitchRate = cos(DEG2RAD * current.roll) * current.dPitch + sin(DEG2RAD * current.roll) * current.dAzimuth;
    out.yawRate = cos(DEG2RAD * current.roll) * current.dAzimuth - sin(DEG2RAD * current.roll) * current.dPitch;

    //Update accelerometer sensor data
    out.accX = current.ddX*Rbe[0][0]
            +current.ddY*Rbe[0][1]
            +(current.ddZ+GRAVITY)*Rbe[0][2];
    out.accY = current.ddX*Rbe[1][0]
            +current.ddY*Rbe[1][1]
            +(current.ddZ+GRAVITY)*Rbe[1][2];
    out.accZ = - (current.ddX*Rbe[2][0]
                     +current.ddY*Rbe[2][1]
                     +(current.ddZ+GRAVITY)*Rbe[2][2]);

    updateUAVOs(out);
}