static void ExpectRegistered(
		std::string const & iTemporaryRobotId,
		std::string const & iExpectedRobotId,
		std::string const & iExpectedTeam,
		Sender & ioPusher,
		Receiver & ioSubscriber)
{
	Register aRegisterMessage;
	aRegisterMessage.set_temporary_robot_id(iTemporaryRobotId);
	aRegisterMessage.set_video_url("http://localhost:80");
	aRegisterMessage.set_image("this is a photo of the robot.jpg");
	RawMessage aMessage(
			iTemporaryRobotId,
			"Register",
			aRegisterMessage.SerializeAsString());
	ioPusher.send(aMessage);

	RawMessage aResponse;
	if (not Common::ExpectMessage("Registered", ioSubscriber, aResponse))
	{
		ORWELL_LOG_ERROR("Expected Registered but received " << aResponse._type);
		g_status = -1;
	}
	else
	{
		Registered aRegistered;
		aRegistered.ParsePartialFromString(aResponse._payload);

		if (aRegistered.robot_id() != iExpectedRobotId)
		{
			ORWELL_LOG_ERROR("Expected robot ID '" << iExpectedRobotId
					<< "' but received '" << aRegistered.robot_id() << "'");
			g_status = -2;
		}
		if (iExpectedTeam.length() > 0)
		{
			if (aRegistered.has_team())
			{
				ORWELL_LOG_INFO("The robot will be in team: " << aRegistered.team());
				if (iExpectedTeam != aRegistered.team())
				{
					ORWELL_LOG_ERROR("Expected team '" << iExpectedTeam
							<< "' but received '" << aRegistered.team() << "'");
					g_status = -4;
				}
			}
			else
			{
				ORWELL_LOG_ERROR("Expected a team but none found.");
				g_status = -3;
			}
		}
	}
}