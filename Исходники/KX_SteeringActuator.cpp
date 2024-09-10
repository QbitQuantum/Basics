void KX_SteeringActuator::HandleActorFace(MT_Vector3& velocity)
{
	if (m_facingMode==0 && (!m_navmesh || !m_normalUp))
		return;
	KX_GameObject* curobj = (KX_GameObject*) GetParent();
	MT_Vector3 dir = m_facingMode==0 ?  curobj->NodeGetLocalOrientation().getColumn(1) : velocity;
	if (dir.fuzzyZero())
		return;
	dir.normalize();
	MT_Vector3 up(0,0,1);
	MT_Vector3 left;
	MT_Matrix3x3 mat;
	
	if (m_navmesh && m_normalUp)
	{
		dtStatNavMesh* navmesh =  m_navmesh->GetNavMesh();
		MT_Vector3 normal;
		MT_Vector3 trpos = m_navmesh->TransformToLocalCoords(curobj->NodeGetWorldPosition());
		if (getNavmeshNormal(navmesh, trpos, normal))
		{

			left = (dir.cross(up)).safe_normalized();
			dir = (-left.cross(normal)).safe_normalized();
			up = normal;
		}
	}

	switch (m_facingMode)
	{
	case 1: // TRACK X
		{
			left  = dir.safe_normalized();
			dir = -(left.cross(up)).safe_normalized();
			break;
		};
	case 2:	// TRACK Y
		{
			left  = (dir.cross(up)).safe_normalized();
			break;
		}

	case 3: // track Z
		{
			left = up.safe_normalized();
			up = dir.safe_normalized();
			dir = left;
			left  = (dir.cross(up)).safe_normalized();
			break;
		}

	case 4: // TRACK -X
		{
			left  = -dir.safe_normalized();
			dir = -(left.cross(up)).safe_normalized();
			break;
		};
	case 5: // TRACK -Y
		{
			left  = (-dir.cross(up)).safe_normalized();
			dir = -dir;
			break;
		}
	case 6: // track -Z
		{
			left = up.safe_normalized();
			up = -dir.safe_normalized();
			dir = left;
			left  = (dir.cross(up)).safe_normalized();
			break;
		}
	}

	mat.setValue (
		left[0], dir[0],up[0], 
		left[1], dir[1],up[1],
		left[2], dir[2],up[2]
	);

	
	
	KX_GameObject* parentObject = curobj->GetParent();
	if (parentObject)
	{ 
		MT_Vector3 localpos;
		localpos = curobj->GetSGNode()->GetLocalPosition();
		MT_Matrix3x3 parentmatinv;
		parentmatinv = parentObject->NodeGetWorldOrientation ().inverse ();
		mat = parentmatinv * mat;
		mat = m_parentlocalmat * mat;
		curobj->NodeSetLocalOrientation(mat);
		curobj->NodeSetLocalPosition(localpos);
	}
	else
	{
		curobj->NodeSetLocalOrientation(mat);
	}

}