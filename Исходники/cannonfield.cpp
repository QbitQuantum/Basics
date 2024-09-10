void CannonField::moveShot()
{
	QRegion region = shotRect();
	++timerCount;
	
	QRect shotR = shotRect();

	if (shotR.intersects(targetRect()))
	{
		autoShootTimer->stop();
		emit hit();
		emit canShoot(true);
	}	
	else if (shotR.x() > width() || shotR.y() > height() || shotR.intersects(barrierRect()))
	{
		autoShootTimer->stop();	
		emit missed();
		emit canShoot(true);
	}
	else
	{
		region = region.unite(shotR);
	}

	update(region);
}