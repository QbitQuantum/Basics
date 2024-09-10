// reldir*targdist and relvel are pos and vel of ship relative to target in ship's frame
// endspeed is in direction of motion, must be positive
// maxdecel is maximum deceleration thrust
bool Ship::AIMatchPosVel2(const vector3d &reldir, double targdist, const vector3d &relvel, double endspeed, double maxdecel)
{
	matrix4x4d rot; GetRotMatrix(rot);
	double parspeed = relvel.Dot(reldir);
	double ivel = calc_ivel(targdist, endspeed, maxdecel);
	double diffspeed = ivel - parspeed;
	vector3d diffvel = diffspeed * reldir * rot;
	bool rval = false;

	// crunch diffvel by relative thruster power to get acceleration in right direction
	if (diffspeed > 0.0) {
		vector3d maxFA = GetMaxThrust(diffvel) * Pi::game->GetTimeStep() / GetMass();
		if (abs(diffvel.x) > maxFA.x) diffvel *= maxFA.x / abs(diffvel.x);
		if (abs(diffvel.y) > maxFA.y) diffvel *= maxFA.y / abs(diffvel.y);
//		if (abs(diffvel.z) > maxFA.z) diffvel *= maxFA.z / abs(diffvel.z);
		if (maxFA.z < diffspeed) rval = true;
	}

	// add perpendicular velocity
	vector3d perpvel = relvel - parspeed*reldir;
	diffvel -= perpvel * rot;
	AIChangeVelBy(diffvel);
	return rval;			// true if acceleration was capped
}