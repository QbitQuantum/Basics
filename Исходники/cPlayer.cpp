void CPlayer::onMove( Vector2d dir )
{
	Vector2d v;
	dir=dir.normalize();
	v.x=(getCenter().x+dir.x*size.x);
	v.y=(getCenter().y+dir.y*size.y);
	setGoalPoint(v);
	CMoveObject::onMove(dir);
}