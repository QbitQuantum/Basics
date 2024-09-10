void DeviceELMOSteeringMotorVel::setProfilePosition(double jointPosition_rad, double jointVelocity_rad_s)
{
    const double Ke = -1.0;
    double command_pos = remainder(jointPosition_rad,M_PI);
    double position_error = remainder(command_pos - getPosition(), 2*M_PI);
    double command_vel = Ke * position_error;
    if (command_vel > jointVelocity_rad_s) {command_vel = jointVelocity_rad_s;}
    if (command_vel <-jointVelocity_rad_s) {command_vel =-jointVelocity_rad_s;}
    printf("%d:Pos control: C %.2f S %.2f O %.2f\n",nodeId_,jointPosition_rad,
	getPosition(), command_vel);
    setProfileVelocity(command_vel);
}