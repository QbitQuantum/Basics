void TransformManipulator::move(const Vector3F & d)
{
	Matrix44F ps;
	parentSpace(ps);
	Matrix44F invps = ps;
	invps.inverse();
	
	Vector3F od = invps.transformAsNormal(d);
		
	m_subject->translate(od);
	setTranslation(m_subject->translation());
}