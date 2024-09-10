bool ShootingPrintHitGraphic(COORD location, int timeshit)
{
	COORD consize = getconsize();

	if (location.X < 0 || location.X >= consize.X || location.Y < 0 || location.Y > consize.Y)
		return false;

	if(timeshit >= SHOOTING_SILHOUETTE_HITMARKERSNUM)
	{
		timeshit = SHOOTING_SILHOUETTE_HITMARKERSNUM - 1;
	}
	char toprint = g_Shooting_HitMarkers[timeshit];
	setcursor(location.X, location.Y);
	writechar(toprint);
	return true;
}