// -------------------------------------------------------------------------
void Hermite::getTangentOnSegment(osg::Vec3& tangent, double distance, unsigned int segment)
{
	float fH1 = ( 6.0f * distance - 6.0f) * distance;
	float fH2 = ( 3.0f * distance - 4.0f) * distance + 1.0f;
	float fH3 = ( 3.0f * distance - 2.0f) * distance;
	float fH4 = (-6.0f * distance + 6.0f) * distance;

	const ControlPoint& begin = (*_segments)[segment].getBegin();
	const ControlPoint& end   = (*_segments)[segment].getEnd();

	tangent = begin.position * fH1 + begin.tangent * fH2 + end.tangent * fH3 + end.position * fH4;
	tangent.normalize();
	
	/*
	tangent[0] = begin->position.x * fH1 +
		begin->tangent.x  * fH2 +
		end->tangent.x    * fH3 +
		end->position.x   * fH4;
	tangent[1] = begin->position.y * fH1 +
		begin->tangent.y  * fH2 +
		end->tangent.y    * fH3 +
		end->position.y   * fH4;
	tangent[2] = begin->position.z * fH1 +
		begin->tangent.z  * fH2 +
		end->tangent.z    * fH3 +
		end->position.z   * fH4;

	Math::normalize(tangent);
	*/
	
}