//! Compute the smallest distance from the (infinite) line to the box.
static PxReal distanceLineBoxSquared(const PxVec3& lineOrigin, const PxVec3& lineDirection,
								  const PxVec3& boxOrigin, const PxVec3& boxExtent, const PxMat33& boxBase,
								  PxReal* lineParam,
								  PxVec3* boxParam)
{
	const PxVec3& axis0 = boxBase.column0;
	const PxVec3& axis1 = boxBase.column1;
	const PxVec3& axis2 = boxBase.column2;
	
	// compute coordinates of line in box coordinate system
	const PxVec3 diff = lineOrigin - boxOrigin;
	PxVec3 pnt(diff.dot(axis0), diff.dot(axis1), diff.dot(axis2));
	PxVec3 dir(lineDirection.dot(axis0), lineDirection.dot(axis1), lineDirection.dot(axis2));

	// Apply reflections so that direction vector has nonnegative components.
	bool reflect[3];
	for(unsigned int i=0;i<3;i++)
	{
		if(dir[i]<0.0f)
		{
			pnt[i] = -pnt[i];
			dir[i] = -dir[i];
			reflect[i] = true;
		}
		else
		{
			reflect[i] = false;
		}
	}

	PxReal sqrDistance = 0.0f;

	if(dir.x>0.0f)
	{
		if(dir.y>0.0f)
		{
			if(dir.z>0.0f)	caseNoZeros(pnt, dir, boxExtent, lineParam, sqrDistance);		// (+,+,+)
			else			case0(0, 1, 2, pnt, dir, boxExtent, lineParam, sqrDistance);	// (+,+,0)
		}
		else
		{
			if(dir.z>0.0f)	case0(0, 2, 1, pnt, dir, boxExtent, lineParam, sqrDistance);	// (+,0,+)
			else			case00(0, 1, 2, pnt, dir, boxExtent, lineParam, sqrDistance);	// (+,0,0)
		}
	}
	else
	{
		if(dir.y>0.0f)
		{
			if(dir.z>0.0f)	case0(1, 2, 0, pnt, dir, boxExtent, lineParam, sqrDistance);	// (0,+,+)
			else			case00(1, 0, 2, pnt, dir, boxExtent, lineParam, sqrDistance);	// (0,+,0)
		}
		else
		{
			if(dir.z>0.0f)	case00(2, 0, 1, pnt, dir, boxExtent, lineParam, sqrDistance);	// (0,0,+)
			else
			{
				case000(pnt, boxExtent, sqrDistance);										// (0,0,0)
				if(lineParam)
					*lineParam = 0.0f;
			}
		}
	}

	if(boxParam)
	{
		// undo reflections
		for(unsigned int i=0;i<3;i++)
		{
			if(reflect[i])
				pnt[i] = -pnt[i];
		}

		*boxParam = pnt;
	}

	return sqrDistance;
}