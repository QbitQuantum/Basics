bool KX_TrackToActuator::Update(double curtime, bool frame)
{
	bool result = false;	
	bool bNegativeEvent = IsNegativeEvent();
	RemoveAllEvents();

	if (bNegativeEvent)
	{
		// do nothing on negative events
	}
	else if (m_object)
	{
		KX_GameObject* curobj = (KX_GameObject*) GetParent();
		MT_Vector3 dir = ((KX_GameObject*)m_object)->NodeGetWorldPosition() - curobj->NodeGetWorldPosition();
		if (dir.length2())
			dir.normalize();
		MT_Vector3 up(0,0,1);
		
		
#ifdef DSADSA
		switch (m_upflag)
		{
		case 0:
			{
				up.setValue(1.0,0,0);
				break;
			} 
		case 1:
			{
				up.setValue(0,1.0,0);
				break;
			}
		case 2:
		default:
			{
				up.setValue(0,0,1.0);
			}
		}
#endif 
		if (m_allow3D)
		{
			up = (up - up.dot(dir) * dir).safe_normalized();
			
		}
		else
		{
			dir = (dir - up.dot(dir)*up).safe_normalized();
		}
		
		MT_Vector3 left;
		MT_Matrix3x3 mat;
		
		switch (m_trackflag)
		{
		case 0: // TRACK X
			{
				// (1.0 , 0.0 , 0.0 ) x direction is forward, z (0.0 , 0.0 , 1.0 ) up
				left  = dir.safe_normalized();
				dir = (left.cross(up)).safe_normalized();
				mat.setValue (
					left[0], dir[0],up[0], 
					left[1], dir[1],up[1],
					left[2], dir[2],up[2]
					);
				
				break;
			};
		case 1:	// TRACK Y
			{
				// (0.0 , 1.0 , 0.0 ) y direction is forward, z (0.0 , 0.0 , 1.0 ) up
				left  = (dir.cross(up)).safe_normalized();
				mat.setValue (
					left[0], dir[0],up[0], 
					left[1], dir[1],up[1],
					left[2], dir[2],up[2]
					);
				
				break;
			}
			
		case 2: // track Z
			{
				left = up.safe_normalized();
				up = dir.safe_normalized();
				dir = left;
				left  = (dir.cross(up)).safe_normalized();
				mat.setValue (
					left[0], dir[0],up[0], 
					left[1], dir[1],up[1],
					left[2], dir[2],up[2]
					);
				break;
			}
			
		case 3: // TRACK -X
			{
				// (1.0 , 0.0 , 0.0 ) x direction is forward, z (0.0 , 0.0 , 1.0 ) up
				left  = -dir.safe_normalized();
				dir = -(left.cross(up)).safe_normalized();
				mat.setValue (
					left[0], dir[0],up[0], 
					left[1], dir[1],up[1],
					left[2], dir[2],up[2]
					);
				
				break;
			};
		case 4: // TRACK -Y
			{
				// (0.0 , -1.0 , 0.0 ) -y direction is forward, z (0.0 , 0.0 , 1.0 ) up
				left  = (-dir.cross(up)).safe_normalized();
				mat.setValue (
					left[0], -dir[0],up[0], 
					left[1], -dir[1],up[1],
					left[2], -dir[2],up[2]
					);
				break;
			}
		case 5: // track -Z
			{
				left = up.safe_normalized();
				up = -dir.safe_normalized();
				dir = left;
				left  = (dir.cross(up)).safe_normalized();
				mat.setValue (
					left[0], dir[0],up[0], 
					left[1], dir[1],up[1],
					left[2], dir[2],up[2]
					);
				
				break;
			}
			
		default:
			{
				// (1.0 , 0.0 , 0.0 ) -x direction is forward, z (0.0 , 0.0 , 1.0 ) up
				left  = -dir.safe_normalized();
				dir = -(left.cross(up)).safe_normalized();
				mat.setValue (
					left[0], dir[0],up[0], 
					left[1], dir[1],up[1],
					left[2], dir[2],up[2]
					);
			}
		}
		
		MT_Matrix3x3 oldmat;
		oldmat= curobj->NodeGetWorldOrientation();
		
		/* erwin should rewrite this! */
		mat= matrix3x3_interpol(oldmat, mat, m_time);
		

		if(m_parentobj){ // check if the model is parented and calculate the child transform
				
			MT_Point3 localpos;
			localpos = curobj->GetSGNode()->GetLocalPosition();
			// Get the inverse of the parent matrix
			MT_Matrix3x3 parentmatinv;
			parentmatinv = m_parentobj->NodeGetWorldOrientation ().inverse ();				
			// transform the local coordinate system into the parents system
			mat = parentmatinv * mat;
			// append the initial parent local rotation matrix
			mat = m_parentlocalmat * mat;

			// set the models tranformation properties
			curobj->NodeSetLocalOrientation(mat);
			curobj->NodeSetLocalPosition(localpos);
			//curobj->UpdateTransform();
		}
		else
		{
			curobj->NodeSetLocalOrientation(mat);
		}

		result = true;
	}

	return result;
}