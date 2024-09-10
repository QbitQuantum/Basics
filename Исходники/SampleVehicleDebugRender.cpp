void SampleVehicle::drawWheels()
{
	const RendererColor colorPurple(255, 0, 255);

	for(PxU32 i=0;i<mVehicleManager.getNbVehicles();i++)
	{
		//Draw a rotating arrow to get an idea of the wheel rotation speed.
		PxVehicleWheels* veh=mVehicleManager.getVehicle(i);
		const PxRigidDynamic* actor=veh->getRigidDynamicActor();
		PxShape* shapeBuffer[PX_MAX_NUM_WHEELS];
		actor->getShapes(shapeBuffer,veh->mWheelsSimData.getNumWheels());
		const PxTransform vehGlobalPose=actor->getGlobalPose();
		const PxU32 numWheels=veh->mWheelsSimData.getNumWheels();
		for(PxU32 j=0;j<numWheels;j++)
		{
			const PxTransform wheelTransform=vehGlobalPose.transform(shapeBuffer[j]->getLocalPose());
			const PxF32 wheelRadius=veh->mWheelsSimData.getWheelData(j).mRadius;
			const PxF32 wheelHalfWidth=veh->mWheelsSimData.getWheelData(j).mWidth*0.5f;
			PxVec3 offset=wheelTransform.q.getBasisVector0()*wheelHalfWidth;
			offset*= (veh->mWheelsSimData.getWheelCentreOffset(j).x > 0) ? 1.0f : -1.0f;
			const PxVec3 arrow=wheelTransform.rotate(PxVec3(0,0,1));
			getDebugRenderer()->addLine(wheelTransform.p+offset, wheelTransform.p+offset+arrow*wheelRadius, colorPurple);
		}
	}
}