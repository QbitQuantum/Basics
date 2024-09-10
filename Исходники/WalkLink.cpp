void WalkLink::render() const
{
	Vector3d mid = (m_edge.e1 + m_edge.e2) / 2;
	Vector3d alongEdge = (m_edge.e2 - m_edge.e1);
	Vector3d acrossEdge = alongEdge.cross(Vector3d(0,0,1)).normalize();
	acrossEdge *= 0.2;
	Vector3d s = mid + acrossEdge, d = mid - acrossEdge;
	glBegin(GL_LINES);
		glColor3d(0,1,1);
		glVertex3d(s.x, s.y, s.z);
		glVertex3d(d.x, d.y, d.z);
	glEnd();
}