// check for inability to reach target waypoint without overshooting
static bool CheckOvershoot(Ship *ship, const vector3d &reldir, double targdist, const vector3d &relvel, double endvel)
{
	if (targdist < 100.0) return false;		// spazzes out occasionally otherwise
	// only slightly fake minimum time to target
	// based on s = (sv+ev)*t/2 + a*t*t/4
	double fwdacc = ship->GetAccelFwd();
	double u = 0.5 * (relvel.Dot(reldir) + endvel);	if (u<0) u = 0;
	double t = (-u + sqrt(u*u + fwdacc*targdist)) / (fwdacc * 0.5);
	if (t < Pi::game->GetTimeStep()) t = Pi::game->GetTimeStep();
//	double t2 = ship->AITravelTime(reldir, targdist, relvel, endvel, true);

	// check for uncorrectable side velocity
	vector3d perpvel = relvel - reldir * relvel.Dot(reldir);
	if (perpvel.Length() > 0.5*ship->GetAccelMin()*t)
		return true;
	return false;
}