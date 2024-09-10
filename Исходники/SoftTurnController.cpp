void SoftTurnController::updateHook()
{
    SoftTurnControllerBase::updateHook();
    
    double pointTurnLimit = 0.1;
    double stepLimit = 0.01;

    static double lastSpeed = 0;
    static base::Time changeTime;

    base::actuators::Status status;
    if(_status.readNewest(status, true) == RTT::NoData)
	return;

    // This is the user's command
    base::commands::Motion2D cmd_in;
    if (_motion_command.readNewest(cmd_in, true) == RTT::NoData)
    {
        cmd_in.translation = 0;
        cmd_in.rotation    = 0;
    }
        
    //let's allways turn
    if(true || fabs(cmd_in.rotation) > pointTurnLimit)
    {
        //hack
        cmd_in.rotation = 1.0;
        cmd_in.rotation = turnSpeed * fabs(cmd_in.rotation) / cmd_in.rotation;

	static bool switchState = false;
	for(int i = 0; i < 4; i++)
	{
	    const double diff = fabs(startStatus.states[i].positionExtern - status.states[i].positionExtern);
	    //we assume zero slip
	    if(diff * _wheel_radius.get()  > _turnVariance.get() )
	    {
		//we moved the maximum variance in one direction, reverse
		switchState = true;
		break;
	    }
	}
	
	if(!switchState)
	{
        switch(state)
        {
            case FORWARD:
                cmd_in.translation = translationalSpeed;		
                break;
                
            case BACKWARD:
                cmd_in.translation = -translationalSpeed;		
                break;
        }
	}
	else 
	{
	    if(changeTime.isNull())
		changeTime = base::Time::now();

	    if(base::Time::now() - changeTime > base::Time::fromSeconds(0.5) )
	    {
		startStatus = status;
		if(state == FORWARD)
		    state = BACKWARD;
		else
		    state = FORWARD;

		std::cout << "Switched State" << std::endl;
		changeTime = base::Time();
		switchState = false;
	    }
	}
    }

    double newSpeed = 0;
    if(cmd_in.translation < 0)
    {
	newSpeed = lastSpeed - stepLimit;
	if(newSpeed < cmd_in.translation)
	    newSpeed = cmd_in.translation;
    }
    else
    {
	newSpeed = lastSpeed + stepLimit;
	if(newSpeed > cmd_in.translation)
	    newSpeed = cmd_in.translation;
    }

    lastSpeed = newSpeed;
    cmd_in.translation = newSpeed;

    std::cout << "cmd_in.translation " << cmd_in.translation << "cmd_in.rotation " << cmd_in.rotation << std::endl; 
    double fwd_velocity = cmd_in.translation / _wheel_radius.get();
    double differential = cmd_in.rotation * _track_width.get() / _wheel_radius.get();
    
    double leftSpeed;
    double rightSpeed;
    
    m_cmd.mode[0] = m_cmd.mode[1] =
        m_cmd.mode[2] = m_cmd.mode[3] = base::actuators::DM_SPEED;

    
    m_cmd.target[base::actuators::WHEEL4_FRONT_LEFT]  = fwd_velocity - differential;
    m_cmd.target[base::actuators::WHEEL4_REAR_LEFT]   = fwd_velocity - differential;
    m_cmd.target[base::actuators::WHEEL4_FRONT_RIGHT] = fwd_velocity + differential;
    m_cmd.target[base::actuators::WHEEL4_REAR_RIGHT]  = fwd_velocity + differential;
    m_cmd.time = base::Time::now();

    _simple_command.write(m_cmd);
}