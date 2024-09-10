void FPhATEdPreviewViewportClient::StartManipulating(EAxisList::Type Axis, const FViewportClick& Click, const FMatrix& WorldToCamera)
{
	check(!SharedData->bManipulating);
	if (SharedData->EditingMode == FPhATSharedData::PEM_BodyEdit && SharedData->SelectedBodies.Num())
	{
		GEditor->BeginTransaction( NSLOCTEXT("UnrealEd", "MoveElement", "Move Element") );
		for(int32 i=0; i<SharedData->SelectedBodies.Num(); ++i)
		{
			SharedData->PhysicsAsset->SkeletalBodySetups[SharedData->SelectedBodies[i].Index]->Modify();
			SharedData->SelectedBodies[i].ManipulateTM = FTransform::Identity;
		}

		SharedData->bManipulating = true;
	}
	else if( SharedData->GetSelectedConstraint())
	{
		GEditor->BeginTransaction( NSLOCTEXT("UnrealEd", "MoveConstraint", "Move Constraint") );
		for(int32 i=0; i<SharedData->SelectedConstraints.Num(); ++i)
		{
			SharedData->PhysicsAsset->ConstraintSetup[SharedData->SelectedConstraints[i].Index]->Modify();
			SharedData->SelectedConstraints[i].ManipulateTM = FTransform::Identity;
		}

		const FTransform WParentFrame = SharedData->GetConstraintWorldTM(SharedData->GetSelectedConstraint(), EConstraintFrame::Frame2);
		const FTransform WChildFrame = SharedData->GetConstraintWorldTM(SharedData->GetSelectedConstraint(), EConstraintFrame::Frame1);
		StartManRelConTM = WChildFrame * WParentFrame.Inverse();

		UPhysicsConstraintTemplate* Setup = SharedData->PhysicsAsset->ConstraintSetup[SharedData->GetSelectedConstraint()->Index];

		StartManParentConTM = Setup->DefaultInstance.GetRefFrame(EConstraintFrame::Frame2);
		StartManChildConTM = Setup->DefaultInstance.GetRefFrame(EConstraintFrame::Frame1);

		SharedData->bManipulating = true;
	}

}