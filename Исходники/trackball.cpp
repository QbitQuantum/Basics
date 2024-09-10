void TrackBall::move(const QPointF& p)
{
	if (!m_pressed)
		return;
	QVector3D lastPos3D = QVector3D(m_lastPos.x(), m_lastPos.y(), 0.0f);
	float sqrZ = 1 - QVector3D::dotProduct(lastPos3D, lastPos3D);
	if (sqrZ > 0)
		lastPos3D.setZ(sqrt(sqrZ));
	else
		lastPos3D.normalize();

	QVector3D currentPos3D = QVector3D(p.x(), p.y(), 0.0f);
	sqrZ = 1 - QVector3D::dotProduct(currentPos3D, currentPos3D);
	if (sqrZ > 0)
		currentPos3D.setZ(sqrt(sqrZ));
	else
		currentPos3D.normalize();

	QVector3D axis = QVector3D::crossProduct(lastPos3D, currentPos3D);
	float angle = 360 / PI * asin(sqrt(QVector3D::dotProduct(axis, axis)));

	axis.normalize();
	m_rotation = QQuaternion::fromAxisAndAngle(axis, angle) * m_rotation;

	m_lastPos = p;
}