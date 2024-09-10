bool UWorld::ComponentSweepMulti(TArray<struct FHitResult>& OutHits, class UPrimitiveComponent* PrimComp, const FVector& Start, const FVector& End, const FQuat& Quat, const struct FComponentQueryParams& Params) const
{
	if (GetPhysicsScene() == NULL)
	{
		return false;
	}

	if (PrimComp == NULL)
	{
		UE_LOG(LogCollision, Log, TEXT("ComponentSweepMulti : No PrimComp"));
		return false;
	}

	ECollisionChannel TraceChannel = PrimComp->GetCollisionObjectType();

	// if extent is 0, do line trace
	if (PrimComp->IsZeroExtent())
	{
		return RaycastMulti(this, OutHits, Start, End, TraceChannel, Params, FCollisionResponseParams(PrimComp->GetCollisionResponseToChannels()));
	}

	OutHits.Reset();

#if UE_WITH_PHYSICS
	const FBodyInstance* BodyInstance = PrimComp->GetBodyInstance();

	if (!BodyInstance || !BodyInstance->IsValidBodyInstance())
	{
		UE_LOG(LogCollision, Log, TEXT("ComponentSweepMulti : (%s) No physics data"), *PrimComp->GetReadableName());
		return false;
	}

#if !(UE_BUILD_SHIPPING || UE_BUILD_TEST)
	if(PrimComp->IsA(USkeletalMeshComponent::StaticClass()))
	{
		UE_LOG(LogCollision, Warning, TEXT("ComponentSweepMulti : SkeletalMeshComponent support only root body (%s) "), *PrimComp->GetReadableName());
	}
#endif

#endif

	SCOPE_CYCLE_COUNTER(STAT_Collision_GeomSweepMultiple);
	bool bHaveBlockingHit = false;

#if WITH_PHYSX
	ExecuteOnPxRigidActorReadOnly(BodyInstance, [&] (const PxRigidActor* PRigidActor)
	{
		// Get all the shapes from the actor
		FInlinePxShapeArray PShapes;
		const int32 NumShapes = FillInlinePxShapeArray(PShapes, *PRigidActor);

		// calculate the test global pose of the actor
		const PxQuat PGeomRot = U2PQuat(Quat);
		const PxTransform PGlobalStartPose = PxTransform(U2PVector(Start), PGeomRot);
		const PxTransform PGlobalEndPose = PxTransform(U2PVector(End), PGeomRot);

		// Iterate over each shape
		for(int32 ShapeIdx=0; ShapeIdx<NumShapes; ShapeIdx++)
		{
			PxShape* PShape = PShapes[ShapeIdx];
			check(PShape);

			GET_GEOMETRY_FROM_SHAPE(PGeom, PShape);

			if (PGeom != NULL)
			{
				// Calc shape global pose
				const PxTransform PLocalShape = PShape->getLocalPose();
				const PxTransform PShapeGlobalStartPose = PGlobalStartPose.transform(PLocalShape);
				const PxTransform PShapeGlobalEndPose = PGlobalEndPose.transform(PLocalShape);
				// consider localshape rotation for shape rotation
				const PxQuat PShapeRot = PGeomRot * PLocalShape.q;

				if (GeomSweepMulti_PhysX(this, *PGeom, PShapeRot, OutHits, P2UVector(PShapeGlobalStartPose.p), P2UVector(PShapeGlobalEndPose.p), TraceChannel, Params, FCollisionResponseParams(PrimComp->GetCollisionResponseToChannels())))
				{
					bHaveBlockingHit = true;
				}
			}
		}
	});
#endif //WITH_PHYSX

	//@TODO: BOX2D: Implement UWorld::ComponentSweepMulti
#if WITH_BOX2D
// 	if (b2Body* BodyInstance = PrimComp->BodyInstance.BodyInstancePtr)
// 	{
// 		
// 	}
#endif

	return bHaveBlockingHit;
}