FDbool BuildingSystem::searchForHit(PhysicsSystem& physicsSystem,
		Ray r, PxGeometry& pixelFrustum, SearchContext& searchContext) {

	// Cast the ray into the scene. Quit if no intersection at all.
	PxQueryFilterData qFilterData;
	qFilterData.flags |= PxQueryFlag::ePREFILTER | PxQueryFlag::ePOSTFILTER;
	FDbool rayStatus = physicsSystem.scene->raycast(
			r.position, r.direction, 100, searchContext.hitBuffer, 
			PxHitFlag::ePOSITION | PxHitFlag::eDISTANCE | PxHitFlag::eNORMAL,
			qFilterData, &CustomPhysicsQueryFilter());

	/* Demo-ing to a friend showed that it can be confusing to try to connect
	* up an existing point that lies on the guide plane, since part of it will
	* be behind the guide plane, which the ray-cast will see as being closer.
	* To remedy this, I treat the GuidePlane as a "touching" rather than 
	* "blocking hit" and give some priority to points. */
	if (rayStatus && searchContext.hitBuffer.hasBlock) {
		
		// In this case, we know we hit something other than the guide plane.
		searchContext.hitActor = searchContext.hitBuffer.block.actor;
		searchContext.rayHit = &searchContext.hitBuffer.block;
		FDreal blockDistance = searchContext.rayHit->distance;
		searchContext.setHit(&searchContext.hitBuffer.block);

		// If the guide plane was also hit, see if it is closer. 
		if (searchContext.hitBuffer.nbTouches > 0) {
			float guidePlaneDistance = searchContext.hitBuffer.getTouch(0).
					distance;

			// If the point intersects the plane, prefer it.
			if (searchContext.hitActor == pointActor) {

				FDUint i = (FDUint)searchContext.rayHit->shape->userData;
				Vector3 pointPos = *pointAuthor->getAttribute<Vector3>(i, 0);
				float pointRadius = 0.2;

				Vector3 guidePlaneNormal = searchContext.hitBuffer.
						getTouch(0).normal;
				Plane p = Plane(searchContext.hitBuffer.getTouch(0).position,
						guidePlaneNormal);

				// We know the point (modeled as a sphere) intersects the
				// plane if the point is within 1 sphere radius.
				float pointPlaneDistance = p.distance(pointPos);
				if (abs(pointPlaneDistance) <= pointRadius) {
					blockDistance = 0;
				}
			} 
			
			if (guidePlaneDistance < blockDistance) {
				searchContext.hitActor = searchContext.hitBuffer.getTouch(0).
						actor;
				searchContext.setHit(&searchContext.hitBuffer.getTouch(0));
			}

		}

	} else if (rayStatus) {
		
		// Only the guide plane was hit.
		searchContext.hitActor = searchContext.hitBuffer.getTouch(0).actor;
		searchContext.setHit(&searchContext.hitBuffer.getTouch(0));
	}

	// Try overlap test for other geometry.
	Quaternion q = fdmath::getRotationBetween(Vector3(0, 0, 1), r.direction);
	Vector3 obo = q.rotate(Vector3(0, 0, 1));

	PxTransform pose(r.position, q);

	PxQueryFilterData qPixelFilterData;
	qPixelFilterData.flags |= PxQueryFlag::ePREFILTER;
	physicsSystem.scene->overlap(pixelFrustum, pose, 
			searchContext.overlapBuffer, qPixelFilterData, 
			&PixelQueryFilter());

	for (FDUint i = 0; i < searchContext.overlapBuffer.nbTouches; i++) {
		PxRigidStatic* thisActor = (PxRigidStatic*)searchContext.overlapBuffer.
				touches[i].actor;
		PxShape* thisShape = searchContext.overlapBuffer.touches[i].shape;

		// Get the closet point on the line to the ray.

		Transform lineTransform = thisActor->getGlobalPose() *
				thisShape->getLocalPose();
		Vector3 lineAxisPoint = lineTransform.transform(Vector3(1, 0, 0));
		Vector3 centerPos = lineTransform.p;
		Vector3 lineAxis = (lineAxisPoint - centerPos).getNormalized();

		Vector3 uAxis = lineAxis.cross(r.direction);
		uAxis.normalize();

		Plane p(centerPos, lineAxisPoint, centerPos + uAxis);
		Vector3 intersectionPoint;
		FDbool intersects = r.intersect(p, intersectionPoint);
		FD_ASSERT(intersects, "Ray did not intersect line's plane.");

		FDreal y = lineAxis.dot(intersectionPoint) - lineAxis.dot(centerPos);
		Vector3 closestPoint = centerPos + lineAxis * y;

		FDreal dist = (closestPoint - r.position).magnitude(); 
		if (dist < searchContext.hitDist) {
			searchContext.setHit(&searchContext.overlapBuffer.touches[i],
					closestPoint, -r.direction, dist);
			searchContext.hitActor = thisActor;
		}
	} 

	return searchContext.hitHappened;
}