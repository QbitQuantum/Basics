void PxSetJointGlobalFrame(PxJoint& joint, const PxVec3* wsAnchor, const PxVec3* axisIn)
{
	PxRigidActor* actors[2];
	joint.getActors(actors[0], actors[1]);

	PxTransform localPose[2];
	for(PxU32 i=0; i<2; i++)
		localPose[i] = PxTransform::createIdentity();

	// 1) global anchor
	if(wsAnchor)
	{
		//transform anchorPoint to local space
		for(PxU32 i=0; i<2; i++)
			localPose[i].p = actors[i] ? actors[i]->getGlobalPose().transformInv(*wsAnchor) : *wsAnchor;
	}

	// 2) global axis
	if(axisIn)
	{
		PxVec3 localAxis[2], localNormal[2];

		//find 2 orthogonal vectors.
		//gotta do this in world space, if we choose them
		//separately in local space they won't match up in worldspace.
		PxVec3 axisw = *axisIn;
		axisw.normalize();

		PxVec3 normalw, binormalw;
		::normalToTangents(axisw, binormalw, normalw);
		//because axis is supposed to be the Z axis of a frame with the other two being X and Y, we need to negate
		//Y to make the frame right handed. Note that the above call makes a right handed frame if we pass X --> Y,Z, so 
		//it need not be changed.

		for(PxU32 i=0; i<2; i++)
		{
			if(actors[i])
			{
				const PxTransform& m = actors[i]->getGlobalPose();
				PxMat33Legacy mM(m.q);
				localAxis[i]   = mM % axisw;
				localNormal[i] = mM % normalw;
			}
			else
			{
				localAxis[i] = axisw;
				localNormal[i] = normalw;
			}

			PxMat33Legacy rot;
			rot.setColumn(0, localAxis[i]);
			rot.setColumn(1, localNormal[i]);
			rot.setColumn(2, localAxis[i].cross(localNormal[i]));

			localPose[i].q = rot.toQuat();
			localPose[i].q.normalize();
		}
	}

	for(PxU32 i=0; i<2; i++)
		joint.setLocalPose(static_cast<PxJointActorIndex::Enum>( i ), localPose[i]);
}