void KJScope::paint(QPainter *p, const QRect &)
{
	// put that thing on screen
	bitBlt ( p->device(), rect().topLeft(), mOsci, QRect(0,0,-1,-1), Qt::CopyROP );
}