void HermiteSpline::calculateFrenetFrame(float u, HermiteSplineControlPoint* c0, HermiteSplineControlPoint* c1, Vector3 &tangent, Vector3 &binormal, Vector3 &normal){
	//********************************************************************************
	//hier wird der Frenet-Frame berechnet und in den �bergebenen Funktionsargumenten gespeichert
	//Sie brauchen noch die zweite Ableitung einer Bezier-Kurve...

	vector<Vector3> bez;

	bez.push_back(c0->getPosition());
	bez.push_back(c0->getPosition() + ONE_THIRD * c0->getDirection());
	bez.push_back(c1->getPosition() - ONE_THIRD * c1->getDirection());
	bez.push_back(c1->getPosition());
	
	Vector3 point;

	deCasteljau(u, bez, point, tangent);

	Vector3 secDer =   (6.0f - 6.0f * u) * bez[0] +
					 (18.0f * u - 12.0f) * bez[1] +
					  (6.0f - 18.0f * u) * bez[2] +
								6.0f * u * bez[3];

	binormal = secDer.cross(tangent);
	binormal.normalize();

	normal = binormal.cross(tangent);

}