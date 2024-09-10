		RaytraceTriangle::RaytraceTriangle(Vector3f p1, Vector3f p2, Vector3f p3, Vector3f n1, Vector3f n2, Vector3f n3) 
			:  p1(p1),p2(p2),p3(p3),n1(n1),n2(n2),n3(n3) 
		{

				// We will use barycentric coordiantes.
				Vector3f p12 = p2-p1;
				Vector3f p13 = p3-p1;
				Vector3f p312 = (p12/p12.sqrLength())*Vector3f::dot(p12,p13);
				Vector3f pn3 = p13-p312;
				npn3 = pn3/pn3.sqrLength();

				Vector3f p32 = p2-p3;
				Vector3f p31 = p1-p3;
				Vector3f p132 = (p32/p32.sqrLength())*Vector3f::dot(p32,p31);
				Vector3f pn1 = p31-p132;
				npn1 = pn1/pn1.sqrLength();
	
				Vector3f p213 = (p13/p13.sqrLength())*Vector3f::dot(p13,p12);
				Vector3f pn2 = p12-p213;
				npn2 = pn2/pn2.sqrLength();

				if (npn1.sqrLength() * 0 != 0 || npn2.sqrLength() * 0 != 0 || npn3.sqrLength() * 0 != 0 ||
					p13.sqrLength() < 1E-8 || p12.sqrLength() < 1E-8 || p32.sqrLength() < 1E-8) {
					//INFO(QString("Bad Triangle (%0): %1, %2, %3").arg((p3-p2).sqrLength()).arg(p1.toString()).arg(p2.toString()).arg(p3.toString()));
					bad = true;
				} else {
					bad = false;
				}

				n1.normalize();
				n2.normalize();
				n3.normalize();

				n = Vector3f::cross(p13,p12);
			}