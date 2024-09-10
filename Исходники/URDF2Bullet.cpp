btTransform ConvertURDF2BulletInternal(
	const URDFImporterInterface& u2b, MultiBodyCreationInterface& creation,
	URDF2BulletCachedData& cache, int urdfLinkIndex,
	const btTransform& parentTransformInWorldSpace, btMultiBodyDynamicsWorld* world1,
	bool createMultiBody, const char* pathPrefix,
	int flags, UrdfVisualShapeCache* cachedLinkGraphicsShapesIn, UrdfVisualShapeCache* cachedLinkGraphicsShapesOut, bool recursive)
{
	B3_PROFILE("ConvertURDF2BulletInternal2");
	//b3Printf("start converting/extracting data from URDF interface\n");

	btTransform linkTransformInWorldSpace;
	linkTransformInWorldSpace.setIdentity();

	int mbLinkIndex = cache.getMbIndexFromUrdfIndex(urdfLinkIndex);

	int urdfParentIndex = cache.getParentUrdfIndex(urdfLinkIndex);
	int mbParentIndex = cache.getMbIndexFromUrdfIndex(urdfParentIndex);
	btRigidBody* parentRigidBody = 0;

	//b3Printf("mb link index = %d\n",mbLinkIndex);

	btTransform parentLocalInertialFrame;
	parentLocalInertialFrame.setIdentity();
	btScalar parentMass(1);
	btVector3 parentLocalInertiaDiagonal(1, 1, 1);

	if (urdfParentIndex == -2)
	{
		//b3Printf("root link has no parent\n");
	}
	else
	{
		//b3Printf("urdf parent index = %d\n",urdfParentIndex);
		//b3Printf("mb parent index = %d\n",mbParentIndex);
		parentRigidBody = cache.getRigidBodyFromLink(urdfParentIndex);
		u2b.getMassAndInertia2(urdfParentIndex, parentMass, parentLocalInertiaDiagonal, parentLocalInertialFrame, flags);
	}

	btScalar mass = 0;
	btTransform localInertialFrame;
	localInertialFrame.setIdentity();
	btVector3 localInertiaDiagonal(0, 0, 0);
	u2b.getMassAndInertia2(urdfLinkIndex, mass, localInertiaDiagonal, localInertialFrame, flags);

	btTransform parent2joint;
	parent2joint.setIdentity();

	int jointType;
	btVector3 jointAxisInJointSpace;
	btScalar jointLowerLimit;
	btScalar jointUpperLimit;
	btScalar jointDamping;
	btScalar jointFriction;
	btScalar jointMaxForce;
	btScalar jointMaxVelocity;

	bool hasParentJoint = u2b.getJointInfo2(urdfLinkIndex, parent2joint, linkTransformInWorldSpace, jointAxisInJointSpace, jointType, jointLowerLimit, jointUpperLimit, jointDamping, jointFriction, jointMaxForce, jointMaxVelocity);
	std::string linkName = u2b.getLinkName(urdfLinkIndex);

	if (flags & CUF_USE_SDF)
	{
		parent2joint = parentTransformInWorldSpace.inverse() * linkTransformInWorldSpace;
	}
	else
	{
		if (flags & CUF_USE_MJCF)
		{
			linkTransformInWorldSpace = parentTransformInWorldSpace * linkTransformInWorldSpace;
		}
		else
		{
			linkTransformInWorldSpace = parentTransformInWorldSpace * parent2joint;
		}
	}

	btCompoundShape* tmpShape = u2b.convertLinkCollisionShapes(urdfLinkIndex, pathPrefix, localInertialFrame);
	btCollisionShape* compoundShape = tmpShape;
	if (tmpShape->getNumChildShapes() == 1 && tmpShape->getChildTransform(0) == btTransform::getIdentity())
	{
		compoundShape = tmpShape->getChildShape(0);
	}

	int graphicsIndex;
	{
		B3_PROFILE("convertLinkVisualShapes");
		if (cachedLinkGraphicsShapesIn && cachedLinkGraphicsShapesIn->m_cachedUrdfLinkVisualShapeIndices.size() > (mbLinkIndex + 1))
		{
			graphicsIndex = cachedLinkGraphicsShapesIn->m_cachedUrdfLinkVisualShapeIndices[mbLinkIndex + 1];
			UrdfMaterialColor matColor = cachedLinkGraphicsShapesIn->m_cachedUrdfLinkColors[mbLinkIndex + 1];
			u2b.setLinkColor2(urdfLinkIndex, matColor);
		}
		else
		{
			graphicsIndex = u2b.convertLinkVisualShapes(urdfLinkIndex, pathPrefix, localInertialFrame);
			if (cachedLinkGraphicsShapesOut)
			{
				cachedLinkGraphicsShapesOut->m_cachedUrdfLinkVisualShapeIndices.push_back(graphicsIndex);
				UrdfMaterialColor matColor;
				u2b.getLinkColor2(urdfLinkIndex, matColor);
				cachedLinkGraphicsShapesOut->m_cachedUrdfLinkColors.push_back(matColor);
			}
		}
	}

	if (compoundShape)
	{
		UrdfMaterialColor matColor;
		btVector4 color2 = selectColor2();
		btVector3 specular(0.5, 0.5, 0.5);
		if (u2b.getLinkColor2(urdfLinkIndex, matColor))
		{
			color2 = matColor.m_rgbaColor;
			specular = matColor.m_specularColor;
		}

		/*
         if (visual->material.get())
         {
            color.setValue(visual->material->color.r,visual->material->color.g,visual->material->color.b);//,visual->material->color.a);
         }
         */
		if (mass)
		{
			if (!(flags & CUF_USE_URDF_INERTIA))
			{
				compoundShape->calculateLocalInertia(mass, localInertiaDiagonal);
				btAssert(localInertiaDiagonal[0] < 1e10);
				btAssert(localInertiaDiagonal[1] < 1e10);
				btAssert(localInertiaDiagonal[2] < 1e10);
			}
			URDFLinkContactInfo contactInfo;
			u2b.getLinkContactInfo(urdfLinkIndex, contactInfo);
			//temporary inertia scaling until we load inertia from URDF
			if (contactInfo.m_flags & URDF_CONTACT_HAS_INERTIA_SCALING)
			{
				localInertiaDiagonal *= contactInfo.m_inertiaScaling;
			}
		}

		btRigidBody* linkRigidBody = 0;
		btTransform inertialFrameInWorldSpace = linkTransformInWorldSpace * localInertialFrame;
		bool canSleep = (flags & CUF_ENABLE_SLEEPING) != 0;

		if (!createMultiBody)
		{
			btRigidBody* body = creation.allocateRigidBody(urdfLinkIndex, mass, localInertiaDiagonal, inertialFrameInWorldSpace, compoundShape);

			if (!canSleep)
			{
				body->forceActivationState(DISABLE_DEACTIVATION);
			}

			linkRigidBody = body;

			world1->addRigidBody(body);

			compoundShape->setUserIndex(graphicsIndex);

			URDFLinkContactInfo contactInfo;
			u2b.getLinkContactInfo(urdfLinkIndex, contactInfo);

			processContactParameters(contactInfo, body);
			creation.createRigidBodyGraphicsInstance2(urdfLinkIndex, body, color2, specular, graphicsIndex);
			cache.registerRigidBody(urdfLinkIndex, body, inertialFrameInWorldSpace, mass, localInertiaDiagonal, compoundShape, localInertialFrame);

			//untested: u2b.convertLinkVisualShapes2(linkIndex,urdfLinkIndex,pathPrefix,localInertialFrame,body);
		}
		else
		{
			if (cache.m_bulletMultiBody == 0)
			{
				bool isFixedBase = (mass == 0);  //todo: figure out when base is fixed
				int totalNumJoints = cache.m_totalNumJoints1;
				cache.m_bulletMultiBody = creation.allocateMultiBody(urdfLinkIndex, totalNumJoints, mass, localInertiaDiagonal, isFixedBase, canSleep);
				if (flags & CUF_GLOBAL_VELOCITIES_MB)
				{
					cache.m_bulletMultiBody->useGlobalVelocities(true);
				}
				if (flags & CUF_USE_MJCF)
				{
					cache.m_bulletMultiBody->setBaseWorldTransform(linkTransformInWorldSpace);
				}

				cache.registerMultiBody(urdfLinkIndex, cache.m_bulletMultiBody, inertialFrameInWorldSpace, mass, localInertiaDiagonal, compoundShape, localInertialFrame);
			}
		}

		//create a joint if necessary
		if (hasParentJoint)
		{
			btTransform offsetInA, offsetInB;
			offsetInA = parentLocalInertialFrame.inverse() * parent2joint;
			offsetInB = localInertialFrame.inverse();
			btQuaternion parentRotToThis = offsetInB.getRotation() * offsetInA.inverse().getRotation();

			bool disableParentCollision = true;

			if (createMultiBody && cache.m_bulletMultiBody)
			{
				cache.m_bulletMultiBody->getLink(mbLinkIndex).m_jointDamping = jointDamping;
				cache.m_bulletMultiBody->getLink(mbLinkIndex).m_jointFriction = jointFriction;
				cache.m_bulletMultiBody->getLink(mbLinkIndex).m_jointLowerLimit = jointLowerLimit;
				cache.m_bulletMultiBody->getLink(mbLinkIndex).m_jointUpperLimit = jointUpperLimit;
				cache.m_bulletMultiBody->getLink(mbLinkIndex).m_jointMaxForce = jointMaxForce;
				cache.m_bulletMultiBody->getLink(mbLinkIndex).m_jointMaxVelocity = jointMaxVelocity;
			}

			switch (jointType)
			{
				case URDFSphericalJoint:
				{
					if (createMultiBody)
					{
						creation.addLinkMapping(urdfLinkIndex, mbLinkIndex);
						cache.m_bulletMultiBody->setupSpherical(mbLinkIndex, mass, localInertiaDiagonal, mbParentIndex,
							parentRotToThis, offsetInA.getOrigin(), -offsetInB.getOrigin(),
							disableParentCollision);
					}
					else
					{
						btAssert(0);
					}
					break;
				}
				case URDFPlanarJoint:
				{
					
					if (createMultiBody)
					{
#if 0
						void setupPlanar(int i,  // 0 to num_links-1
							btScalar mass,
							const btVector3 &inertia,
							int parent,
							const btQuaternion &rotParentToThis,  // rotate points in parent frame to this frame, when q = 0
							const btVector3 &rotationAxis,
							const btVector3 &parentComToThisComOffset,  // vector from parent COM to this COM, in PARENT frame
							bool disableParentCollision = false);
#endif
						creation.addLinkMapping(urdfLinkIndex, mbLinkIndex);
						cache.m_bulletMultiBody->setupPlanar(mbLinkIndex, mass, localInertiaDiagonal, mbParentIndex,
							parentRotToThis, quatRotate(offsetInB.getRotation(), jointAxisInJointSpace), offsetInA.getOrigin(),
							disableParentCollision);
					}
					else
					{
#if 0
						//b3Printf("Fixed joint\n");

						btGeneric6DofSpring2Constraint* dof6 = 0;

						//backward compatibility
						if (flags & CUF_RESERVED)
						{
							dof6 = creation.createFixedJoint(urdfLinkIndex, *parentRigidBody, *linkRigidBody, offsetInA, offsetInB);
						}
						else
						{
							dof6 = creation.createFixedJoint(urdfLinkIndex, *linkRigidBody, *parentRigidBody, offsetInB, offsetInA);
						}
						if (enableConstraints)
							world1->addConstraint(dof6, true);
#endif
					}
					break;
				}
				case URDFFloatingJoint:
				
				case URDFFixedJoint:
				{
					if ((jointType == URDFFloatingJoint) || (jointType == URDFPlanarJoint))
					{
						printf("Warning: joint unsupported, creating a fixed joint instead.");
					}
					creation.addLinkMapping(urdfLinkIndex, mbLinkIndex);

					if (createMultiBody)
					{
						//todo: adjust the center of mass transform and pivot axis properly
						cache.m_bulletMultiBody->setupFixed(mbLinkIndex, mass, localInertiaDiagonal, mbParentIndex,
															parentRotToThis, offsetInA.getOrigin(), -offsetInB.getOrigin());
					}
					else
					{
						//b3Printf("Fixed joint\n");

						btGeneric6DofSpring2Constraint* dof6 = 0;

						//backward compatibility
						if (flags & CUF_RESERVED)
						{
							dof6 = creation.createFixedJoint(urdfLinkIndex, *parentRigidBody, *linkRigidBody, offsetInA, offsetInB);
						}
						else
						{
							dof6 = creation.createFixedJoint(urdfLinkIndex, *linkRigidBody, *parentRigidBody, offsetInB, offsetInA);
						}
						if (enableConstraints)
							world1->addConstraint(dof6, true);
					}
					break;
				}
				case URDFContinuousJoint:
				case URDFRevoluteJoint:
				{
					creation.addLinkMapping(urdfLinkIndex, mbLinkIndex);
					if (createMultiBody)
					{
						cache.m_bulletMultiBody->setupRevolute(mbLinkIndex, mass, localInertiaDiagonal, mbParentIndex,
															   parentRotToThis, quatRotate(offsetInB.getRotation(), 
																   jointAxisInJointSpace), 
																offsetInA.getOrigin(),
															   -offsetInB.getOrigin(),
															   disableParentCollision);

						if (jointType == URDFRevoluteJoint && jointLowerLimit <= jointUpperLimit)
						{
							//std::string name = u2b.getLinkName(urdfLinkIndex);
							//printf("create btMultiBodyJointLimitConstraint for revolute link name=%s urdf link index=%d (low=%f, up=%f)\n", name.c_str(), urdfLinkIndex, jointLowerLimit, jointUpperLimit);
							btMultiBodyConstraint* con = new btMultiBodyJointLimitConstraint(cache.m_bulletMultiBody, mbLinkIndex, jointLowerLimit, jointUpperLimit);
							world1->addMultiBodyConstraint(con);
						}
					}
					else
					{
						btGeneric6DofSpring2Constraint* dof6 = 0;
						if (jointType == URDFRevoluteJoint && jointLowerLimit <= jointUpperLimit)
						{
							//backwards compatibility
							if (flags & CUF_RESERVED)
							{
								dof6 = creation.createRevoluteJoint(urdfLinkIndex, *parentRigidBody, *linkRigidBody, offsetInA, offsetInB, jointAxisInJointSpace, jointLowerLimit, jointUpperLimit);
							}
							else
							{
								dof6 = creation.createRevoluteJoint(urdfLinkIndex, *linkRigidBody, *parentRigidBody, offsetInB, offsetInA, jointAxisInJointSpace, jointLowerLimit, jointUpperLimit);
							}
						}
						else
						{
							//disable joint limits
							if (flags & CUF_RESERVED)
							{
								dof6 = creation.createRevoluteJoint(urdfLinkIndex, *parentRigidBody, *linkRigidBody, offsetInA, offsetInB, jointAxisInJointSpace, 1, -1);
							}
							else
							{
								dof6 = creation.createRevoluteJoint(urdfLinkIndex, *linkRigidBody, *parentRigidBody, offsetInB, offsetInA, jointAxisInJointSpace, 1, -1);
							}
						}

						if (enableConstraints)
							world1->addConstraint(dof6, true);
						//b3Printf("Revolute/Continuous joint\n");
					}
					break;
				}
				case URDFPrismaticJoint:
				{
					creation.addLinkMapping(urdfLinkIndex, mbLinkIndex);

					if (createMultiBody)
					{
						cache.m_bulletMultiBody->setupPrismatic(mbLinkIndex, mass, localInertiaDiagonal, mbParentIndex,
																parentRotToThis, quatRotate(offsetInB.getRotation(), jointAxisInJointSpace), offsetInA.getOrigin(),  //parent2joint.getOrigin(),
																-offsetInB.getOrigin(),
																disableParentCollision);

						if (jointLowerLimit <= jointUpperLimit)
						{
							//std::string name = u2b.getLinkName(urdfLinkIndex);
							//printf("create btMultiBodyJointLimitConstraint for prismatic link name=%s urdf link index=%d (low=%f, up=%f)\n", name.c_str(), urdfLinkIndex, jointLowerLimit,jointUpperLimit);

							btMultiBodyConstraint* con = new btMultiBodyJointLimitConstraint(cache.m_bulletMultiBody, mbLinkIndex, jointLowerLimit, jointUpperLimit);
							world1->addMultiBodyConstraint(con);
						}
						//printf("joint lower limit=%d, upper limit = %f\n", jointLowerLimit, jointUpperLimit);
					}
					else
					{
						btGeneric6DofSpring2Constraint* dof6 = creation.createPrismaticJoint(urdfLinkIndex, *parentRigidBody, *linkRigidBody, offsetInA, offsetInB, jointAxisInJointSpace, jointLowerLimit, jointUpperLimit);

						if (enableConstraints)
							world1->addConstraint(dof6, true);

						//b3Printf("Prismatic\n");
					}
					break;
				}
				default:
				{
					//b3Printf("Error: unsupported joint type in URDF (%d)\n", jointType);
					btAssert(0);
				}
			}
		}

		if (createMultiBody)
		{
			//if (compoundShape->getNumChildShapes()>0)
			{
				btMultiBodyLinkCollider* col = creation.allocateMultiBodyLinkCollider(urdfLinkIndex, mbLinkIndex, cache.m_bulletMultiBody);

				compoundShape->setUserIndex(graphicsIndex);

				col->setCollisionShape(compoundShape);

				if (compoundShape->getShapeType() == TRIANGLE_MESH_SHAPE_PROXYTYPE)
				{
					btBvhTriangleMeshShape* trimeshShape = (btBvhTriangleMeshShape*)compoundShape;
					if (trimeshShape->getTriangleInfoMap())
					{
						col->setCollisionFlags(col->getCollisionFlags() | btCollisionObject::CF_CUSTOM_MATERIAL_CALLBACK);
					}
				}

				btTransform tr;
				tr.setIdentity();
				tr = linkTransformInWorldSpace;
				//if we don't set the initial pose of the btCollisionObject, the simulator will do this
				//when syncing the btMultiBody link transforms to the btMultiBodyLinkCollider

				col->setWorldTransform(tr);

				//base and fixed? -> static, otherwise flag as dynamic
				bool isDynamic = (mbLinkIndex < 0 && cache.m_bulletMultiBody->hasFixedBase()) ? false : true;
				int collisionFilterGroup = isDynamic ? int(btBroadphaseProxy::DefaultFilter) : int(btBroadphaseProxy::StaticFilter);
				int collisionFilterMask = isDynamic ? int(btBroadphaseProxy::AllFilter) : int(btBroadphaseProxy::AllFilter ^ btBroadphaseProxy::StaticFilter);

				int colGroup = 0, colMask = 0;
				int collisionFlags = u2b.getCollisionGroupAndMask(urdfLinkIndex, colGroup, colMask);
				if (collisionFlags & URDF_HAS_COLLISION_GROUP)
				{
					collisionFilterGroup = colGroup;
				}
				if (collisionFlags & URDF_HAS_COLLISION_MASK)
				{
					collisionFilterMask = colMask;
				}
				world1->addCollisionObject(col, collisionFilterGroup, collisionFilterMask);

				btVector4 color2 = selectColor2();  //(0.0,0.0,0.5);
				btVector3 specularColor(1, 1, 1);
				UrdfMaterialColor matCol;
				if (u2b.getLinkColor2(urdfLinkIndex, matCol))
				{
					color2 = matCol.m_rgbaColor;
					specularColor = matCol.m_specularColor;
				}
				{
					B3_PROFILE("createCollisionObjectGraphicsInstance2");
					creation.createCollisionObjectGraphicsInstance2(urdfLinkIndex, col, color2, specularColor);
				}
				{
					B3_PROFILE("convertLinkVisualShapes2");
					u2b.convertLinkVisualShapes2(mbLinkIndex, urdfLinkIndex, pathPrefix, localInertialFrame, col, u2b.getBodyUniqueId());
				}
				URDFLinkContactInfo contactInfo;
				u2b.getLinkContactInfo(urdfLinkIndex, contactInfo);

				processContactParameters(contactInfo, col);

				if (mbLinkIndex >= 0)  //???? double-check +/- 1
				{
					cache.m_bulletMultiBody->getLink(mbLinkIndex).m_collider = col;
					if (flags & CUF_USE_SELF_COLLISION_INCLUDE_PARENT)
					{
						cache.m_bulletMultiBody->getLink(mbLinkIndex).m_flags &= ~BT_MULTIBODYLINKFLAGS_DISABLE_PARENT_COLLISION;
					}
					if (flags & CUF_USE_SELF_COLLISION_EXCLUDE_ALL_PARENTS)
					{
						cache.m_bulletMultiBody->getLink(mbLinkIndex).m_flags |= BT_MULTIBODYLINKFLAGS_DISABLE_ALL_PARENT_COLLISION;
					}
				}
				else
				{
					//					if (canSleep)
					{
						if (cache.m_bulletMultiBody->getBaseMass() == 0)
						//&& cache.m_bulletMultiBody->getNumDofs()==0)
						{
							//col->setCollisionFlags(btCollisionObject::CF_KINEMATIC_OBJECT);
							col->setCollisionFlags(btCollisionObject::CF_STATIC_OBJECT);
						}
					}

					cache.m_bulletMultiBody->setBaseCollider(col);
				}
			}
		}
		else
		{
			int mbLinkIndex = cache.getMbIndexFromUrdfIndex(urdfLinkIndex);
			//u2b.convertLinkVisualShapes2(mbLinkIndex, urdfLinkIndex, pathPrefix, localInertialFrame, col, u2b.getBodyUniqueId());
			u2b.convertLinkVisualShapes2(-1, urdfLinkIndex, pathPrefix, localInertialFrame, linkRigidBody, u2b.getBodyUniqueId());
		}
	}

	btAlignedObjectArray<int> urdfChildIndices;
	u2b.getLinkChildIndices(urdfLinkIndex, urdfChildIndices);

	int numChildren = urdfChildIndices.size();

	if (recursive)
	{
		for (int i = 0; i < numChildren; i++)
		{
			int urdfChildLinkIndex = urdfChildIndices[i];

			ConvertURDF2BulletInternal(u2b, creation, cache, urdfChildLinkIndex, linkTransformInWorldSpace, world1, createMultiBody, pathPrefix, flags, cachedLinkGraphicsShapesIn, cachedLinkGraphicsShapesOut, recursive);
		}
	}
	return linkTransformInWorldSpace;
}