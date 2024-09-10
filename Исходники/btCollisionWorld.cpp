void	btCollisionWorld::rayTestSingle(const btTransform& rayFromTrans,const btTransform& rayToTrans,
										btCollisionObject* collisionObject,
										const btCollisionShape* collisionShape,
										const btTransform& colObjWorldTransform,
										RayResultCallback& resultCallback)
{
	btSphereShape pointShape(btScalar(0.0));
	pointShape.setMargin(0.f);
	const btConvexShape* castShape = &pointShape;

	if (collisionShape->isConvex())
	{
		//		BT_PROFILE("rayTestConvex");
		btConvexCast::CastResult castResult;
		castResult.m_fraction = resultCallback.m_closestHitFraction;

		btConvexShape* convexShape = (btConvexShape*) collisionShape;
		btVoronoiSimplexSolver	simplexSolver;
#define USE_SUBSIMPLEX_CONVEX_CAST 1
#ifdef USE_SUBSIMPLEX_CONVEX_CAST
		btSubsimplexConvexCast convexCaster(castShape,convexShape,&simplexSolver);
#else
		//btGjkConvexCast	convexCaster(castShape,convexShape,&simplexSolver);
		//btContinuousConvexCollision convexCaster(castShape,convexShape,&simplexSolver,0);
#endif //#USE_SUBSIMPLEX_CONVEX_CAST

		if (convexCaster.calcTimeOfImpact(rayFromTrans,rayToTrans,colObjWorldTransform,colObjWorldTransform,castResult))
		{
			//add hit
			if (castResult.m_normal.length2() > btScalar(0.0001))
			{
				if (castResult.m_fraction < resultCallback.m_closestHitFraction)
				{
#ifdef USE_SUBSIMPLEX_CONVEX_CAST
					//rotate normal into worldspace
					castResult.m_normal = rayFromTrans.getBasis() * castResult.m_normal;
#endif //USE_SUBSIMPLEX_CONVEX_CAST

					castResult.m_normal.normalize();
					btCollisionWorld::LocalRayResult localRayResult
						(
						collisionObject,
						0,
						castResult.m_normal,
						castResult.m_fraction
						);

					bool normalInWorldSpace = true;
					resultCallback.addSingleResult(localRayResult, normalInWorldSpace);

				}
			}
		}
	} else {
		if (collisionShape->isConcave())
		{
			//			BT_PROFILE("rayTestConcave");
			if (collisionShape->getShapeType()==TRIANGLE_MESH_SHAPE_PROXYTYPE)
			{
				///optimized version for btBvhTriangleMeshShape
				btBvhTriangleMeshShape* triangleMesh = (btBvhTriangleMeshShape*)collisionShape;
				btTransform worldTocollisionObject = colObjWorldTransform.inverse();
				btVector3 rayFromLocal = worldTocollisionObject * rayFromTrans.getOrigin();
				btVector3 rayToLocal = worldTocollisionObject * rayToTrans.getOrigin();

				//ConvexCast::CastResult
				struct BridgeTriangleRaycastCallback : public btTriangleRaycastCallback
				{
					btCollisionWorld::RayResultCallback* m_resultCallback;
					btCollisionObject*	m_collisionObject;
					btTriangleMeshShape*	m_triangleMesh;

					btTransform m_colObjWorldTransform;

					BridgeTriangleRaycastCallback( const btVector3& from,const btVector3& to,
						btCollisionWorld::RayResultCallback* resultCallback, btCollisionObject* collisionObject,btTriangleMeshShape*	triangleMesh,const btTransform& colObjWorldTransform):
					//@BP Mod
					btTriangleRaycastCallback(from,to, resultCallback->m_flags),
						m_resultCallback(resultCallback),
						m_collisionObject(collisionObject),
						m_triangleMesh(triangleMesh),
						m_colObjWorldTransform(colObjWorldTransform)
					{
					}


					virtual btScalar reportHit(const btVector3& hitNormalLocal, btScalar hitFraction, int partId, int triangleIndex )
					{
						btCollisionWorld::LocalShapeInfo	shapeInfo;
						shapeInfo.m_shapePart = partId;
						shapeInfo.m_triangleIndex = triangleIndex;

						btVector3 hitNormalWorld = m_colObjWorldTransform.getBasis() * hitNormalLocal;

						btCollisionWorld::LocalRayResult rayResult
							(m_collisionObject,
							&shapeInfo,
							hitNormalWorld,
							hitFraction);

						bool	normalInWorldSpace = true;
						return m_resultCallback->addSingleResult(rayResult,normalInWorldSpace);
					}

				};

				BridgeTriangleRaycastCallback rcb(rayFromLocal,rayToLocal,&resultCallback,collisionObject,triangleMesh,colObjWorldTransform);
				rcb.m_hitFraction = resultCallback.m_closestHitFraction;
				triangleMesh->performRaycast(&rcb,rayFromLocal,rayToLocal);
			} else
			{
				//generic (slower) case
				btConcaveShape* concaveShape = (btConcaveShape*)collisionShape;

				btTransform worldTocollisionObject = colObjWorldTransform.inverse();

				btVector3 rayFromLocal = worldTocollisionObject * rayFromTrans.getOrigin();
				btVector3 rayToLocal = worldTocollisionObject * rayToTrans.getOrigin();

				//ConvexCast::CastResult

				struct BridgeTriangleRaycastCallback : public btTriangleRaycastCallback
				{
					btCollisionWorld::RayResultCallback* m_resultCallback;
					btCollisionObject*	m_collisionObject;
					btConcaveShape*	m_triangleMesh;

					btTransform m_colObjWorldTransform;

					BridgeTriangleRaycastCallback( const btVector3& from,const btVector3& to,
						btCollisionWorld::RayResultCallback* resultCallback, btCollisionObject* collisionObject,btConcaveShape*	triangleMesh, const btTransform& colObjWorldTransform):
					//@BP Mod
					btTriangleRaycastCallback(from,to, resultCallback->m_flags),
						m_resultCallback(resultCallback),
						m_collisionObject(collisionObject),
						m_triangleMesh(triangleMesh),
						m_colObjWorldTransform(colObjWorldTransform)
					{
					}


					virtual btScalar reportHit(const btVector3& hitNormalLocal, btScalar hitFraction, int partId, int triangleIndex )
					{
						btCollisionWorld::LocalShapeInfo	shapeInfo;
						shapeInfo.m_shapePart = partId;
						shapeInfo.m_triangleIndex = triangleIndex;

						btVector3 hitNormalWorld = m_colObjWorldTransform.getBasis() * hitNormalLocal;

						btCollisionWorld::LocalRayResult rayResult
							(m_collisionObject,
							&shapeInfo,
							hitNormalWorld,
							hitFraction);

						bool	normalInWorldSpace = true;
						return m_resultCallback->addSingleResult(rayResult,normalInWorldSpace);
					}

				};


				BridgeTriangleRaycastCallback	rcb(rayFromLocal,rayToLocal,&resultCallback,collisionObject,concaveShape, colObjWorldTransform);
				rcb.m_hitFraction = resultCallback.m_closestHitFraction;

				btVector3 rayAabbMinLocal = rayFromLocal;
				rayAabbMinLocal.setMin(rayToLocal);
				btVector3 rayAabbMaxLocal = rayFromLocal;
				rayAabbMaxLocal.setMax(rayToLocal);

				concaveShape->processAllTriangles(&rcb,rayAabbMinLocal,rayAabbMaxLocal);
			}
		} else {
			//			BT_PROFILE("rayTestCompound");
			if (collisionShape->isCompound())
			{
				struct LocalInfoAdder2 : public RayResultCallback
				{
					RayResultCallback* m_userCallback;
					int m_i;
					
					LocalInfoAdder2 (int i, RayResultCallback *user)
						: m_userCallback(user), m_i(i)
					{ 
						m_closestHitFraction = m_userCallback->m_closestHitFraction;
					}
					virtual bool needsCollision(btBroadphaseProxy* p) const
					{
						return m_userCallback->needsCollision(p);
					}

					virtual btScalar addSingleResult (btCollisionWorld::LocalRayResult &r, bool b)
					{
						btCollisionWorld::LocalShapeInfo shapeInfo;
						shapeInfo.m_shapePart = -1;
						shapeInfo.m_triangleIndex = m_i;
						if (r.m_localShapeInfo == NULL)
							r.m_localShapeInfo = &shapeInfo;

						const btScalar result = m_userCallback->addSingleResult(r, b);
						m_closestHitFraction = m_userCallback->m_closestHitFraction;
						return result;
					}
				};
				
				struct RayTester : btDbvt::ICollide
				{
					btCollisionObject* m_collisionObject;
					const btCompoundShape* m_compoundShape;
					const btTransform& m_colObjWorldTransform;
					const btTransform& m_rayFromTrans;
					const btTransform& m_rayToTrans;
					RayResultCallback& m_resultCallback;
					
					RayTester(btCollisionObject* collisionObject,
							const btCompoundShape* compoundShape,
							const btTransform& colObjWorldTransform,
							const btTransform& rayFromTrans,
							const btTransform& rayToTrans,
							RayResultCallback& resultCallback):
						m_collisionObject(collisionObject),
						m_compoundShape(compoundShape),
						m_colObjWorldTransform(colObjWorldTransform),
						m_rayFromTrans(rayFromTrans),
						m_rayToTrans(rayToTrans),
						m_resultCallback(resultCallback)
					{
						
					}
					
					void Process(int i)
					{
						const btCollisionShape* childCollisionShape = m_compoundShape->getChildShape(i);
						const btTransform& childTrans = m_compoundShape->getChildTransform(i);
						btTransform childWorldTrans = m_colObjWorldTransform * childTrans;
						
						// replace collision shape so that callback can determine the triangle
						btCollisionShape* saveCollisionShape = m_collisionObject->getCollisionShape();
						m_collisionObject->internalSetTemporaryCollisionShape((btCollisionShape*)childCollisionShape);

						LocalInfoAdder2 my_cb(i, &m_resultCallback);

						rayTestSingle(
							m_rayFromTrans,
							m_rayToTrans,
							m_collisionObject,
							childCollisionShape,
							childWorldTrans,
							my_cb);
						
						// restore
						m_collisionObject->internalSetTemporaryCollisionShape(saveCollisionShape);
					}
					
					void Process(const btDbvtNode* leaf)
					{
						Process(leaf->dataAsInt);
					}
				};
				
				const btCompoundShape* compoundShape = static_cast<const btCompoundShape*>(collisionShape);
				const btDbvt* dbvt = compoundShape->getDynamicAabbTree();


				RayTester rayCB(
					collisionObject,
					compoundShape,
					colObjWorldTransform,
					rayFromTrans,
					rayToTrans,
					resultCallback);
#ifndef	DISABLE_DBVT_COMPOUNDSHAPE_RAYCAST_ACCELERATION
				if (dbvt)
				{
					btVector3 localRayFrom = colObjWorldTransform.inverseTimes(rayFromTrans).getOrigin();
					btVector3 localRayTo = colObjWorldTransform.inverseTimes(rayToTrans).getOrigin();
					btDbvt::rayTest(dbvt->m_root, localRayFrom , localRayTo, rayCB);
				}
				else
#endif //DISABLE_DBVT_COMPOUNDSHAPE_RAYCAST_ACCELERATION
				{
					for (int i = 0, n = compoundShape->getNumChildShapes(); i < n; ++i)
					{
						rayCB.Process(i);
					}	
				}
			}
		}
	}
}