void NpArticulationLink::setCMassLocalPose(const PxTransform& pose)
{
	NP_WRITE_CHECK(NpActor::getOwnerScene(*this));
	PX_CHECK_AND_RETURN(pose.isSane(), "PxArticulationLink::setCMassLocalPose: invalid parameter");

	PxTransform p = pose.getNormalized();
	PxTransform oldpose = getScbBodyFast().getBody2Actor();
	PxTransform comShift = p.transformInv(oldpose);

	NpArticulationLinkT::setCMassLocalPoseInternal(p);

	if(mInboundJoint)
	{
		Scb::ArticulationJoint &j = mInboundJoint->getScbArticulationJoint();
		j.setChildPose(comShift.transform(j.getChildPose()));
	}

	for(PxU32 i=0; i<mChildLinks.size(); i++)
	{
		Scb::ArticulationJoint &j = static_cast<NpArticulationJoint*>(mChildLinks[i]->getInboundJoint())->getScbArticulationJoint();
		j.setParentPose(comShift.transform(j.getParentPose()));
	}
}