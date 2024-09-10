double YawStrafeMaxAngle(PlayerData& player, const MovementVars& vars, bool onground, double wishspeed, const StrafeButtons& strafeButtons, bool useGivenButtons, Button& usedButton,
	double vel_yaw, double yaw)
{
	bool safeguard_yaw;
	double theta = MaxAngleTheta(player, vars, onground, wishspeed, safeguard_yaw);
	if (!player.Velocity.AsVector2D().IsZero(0.0f))
		vel_yaw = Atan2(player.Velocity[1], player.Velocity[0]);

	Vector2D newvel;
	double resulting_yaw;
	SideStrafeGeneral(player, vars, onground, wishspeed, strafeButtons, useGivenButtons, usedButton, vel_yaw, theta, (NormalizeRad(yaw - vel_yaw) < 0), newvel, resulting_yaw);

	if (safeguard_yaw) {
		Vector2D test_vel1, test_vel2;
		double test_yaw1, test_yaw2;

		SideStrafeGeneral(player, vars, onground, wishspeed, strafeButtons, useGivenButtons, usedButton, vel_yaw, min(theta - SAFEGUARD_THETA_DIFFERENCE_RAD, 0.0), (NormalizeRad(yaw - vel_yaw) < 0), test_vel1, test_yaw1);
		SideStrafeGeneral(player, vars, onground, wishspeed, strafeButtons, useGivenButtons, usedButton, vel_yaw, std::max(theta + SAFEGUARD_THETA_DIFFERENCE_RAD, 0.0), (NormalizeRad(yaw - vel_yaw) < 0), test_vel2, test_yaw2);

		double cos_test1 = test_vel1.Dot(player.Velocity.AsVector2D()) / (player.Velocity.Length2D() * test_vel1.Length());
		double cos_test2 = test_vel2.Dot(player.Velocity.AsVector2D()) / (player.Velocity.Length2D() * test_vel2.Length());
		double cos_newvel = newvel.Dot(player.Velocity.AsVector2D()) / (player.Velocity.Length2D() * newvel.Length());

		//DevMsg("cos_newvel = %.8f; cos_test1 = %.8f; cos_test2 = %.8f\n", cos_newvel, cos_test1, cos_test2);

		if (cos_test1 < cos_newvel) {
			if (cos_test2 < cos_test1) {
				newvel = test_vel2;
				resulting_yaw = test_yaw2;
				cos_newvel = cos_test2;
			} else {
				newvel = test_vel1;
				resulting_yaw = test_yaw1;
				cos_newvel = cos_test1;
			}
		} else if (cos_test2 < cos_newvel) {
			newvel = test_vel2;
			resulting_yaw = test_yaw2;
			cos_newvel = cos_test2;
		}
	} else {
		//DevMsg("theta = %.08f, yaw = %.08f, vel_yaw = %.08f, speed = %.08f\n", theta, yaw, vel_yaw, player.Velocity.Length2D());
	}

	player.Velocity.AsVector2D() = newvel;
	return resulting_yaw;
}