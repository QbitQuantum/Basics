void HavokExport::makeHavokRigidBody(NiNodeRef parent, INode *ragdollParent, float scale) {

	this->scale = scale;

	Object *Obj = ragdollParent->GetObjectRef();

	Modifier* rbMod = nullptr;
	Modifier* shapeMod = nullptr;
	Modifier* constraintMod = nullptr;

	SimpleObject* havokTaperCapsule = nullptr;

	//get modifiers
	

	while (Obj->SuperClassID() == GEN_DERIVOB_CLASS_ID) {
		IDerivedObject *DerObj = static_cast<IDerivedObject *> (Obj);
		const int nMods = DerObj->NumModifiers(); //it is really the last modifier on the stack, and not the total number of modifiers

		for (int i = 0; i < nMods; i++)
		{
			Modifier *Mod = DerObj->GetModifier(i);
			if (Mod->ClassID() == HK_RIGIDBODY_MODIFIER_CLASS_ID) {
				rbMod = Mod;
			}
			if (Mod->ClassID() == HK_SHAPE_MODIFIER_CLASS_ID) {
				shapeMod = Mod;
			}
			if (Mod->ClassID() == HK_CONSTRAINT_RAGDOLL_CLASS_ID || Mod->ClassID() == HK_CONSTRAINT_HINGE_CLASS_ID) {
				constraintMod = Mod;
			}
		}
		if (Obj->SuperClassID() == GEOMOBJECT_CLASS_ID) {
			havokTaperCapsule = (SimpleObject*)Obj;
		}
		Obj = DerObj->GetObjRef();
	}

	
	if (!rbMod) {
		throw exception(FormatText("No havok rigid body modifier found on %s", ragdollParent->GetName()));
	}
	if (!shapeMod) {
		throw exception(FormatText("No havok shape modifier found on %s", ragdollParent->GetName()));
	}

//	Object* taper = ragdollParent->GetObjectRef();
	IParamBlock2* taperParameters = Obj->GetParamBlockByID(PB_TAPEREDCAPSULE_OBJ_PBLOCK);
	float radius;
	enum
	{
		// GENERAL PROPERTIES ROLLOUT
		PA_TAPEREDCAPSULE_OBJ_RADIUS = 0,
		PA_TAPEREDCAPSULE_OBJ_TAPER,
		PA_TAPEREDCAPSULE_OBJ_HEIGHT,
		PA_TAPEREDCAPSULE_OBJ_VERSION_INTERNAL,
	};
	taperParameters->GetValue(PA_TAPEREDCAPSULE_OBJ_RADIUS, 0, radius, FOREVER);
	

	int shapeType;
	if (IParamBlock2* shapeParameters = shapeMod->GetParamBlockByID(PB_SHAPE_MOD_PBLOCK)) {
		shapeParameters->GetValue(PA_SHAPE_MOD_SHAPE_TYPE,0,shapeType,FOREVER);
	}

	//Havok Shape
	bhkShapeRef shape;

	if (shapeType == 2) {

		// Capsule
		bhkCapsuleShapeRef capsule = new bhkCapsuleShape();
		capsule->SetRadius(radius/scale);
		capsule->SetRadius1(radius/scale);
		capsule->SetRadius2(radius/scale);
		float length; 
		taperParameters->GetValue(PA_TAPEREDCAPSULE_OBJ_HEIGHT, 0, length, FOREVER);
		//get the normal
		Matrix3 axis(true);
		ragdollParent->GetObjOffsetRot().MakeMatrix(axis);
		Point3 normalAx = axis.GetRow(2);
		//capsule center
		Point3 center = ragdollParent->GetObjOffsetPos();
		//min and max points
		Point3 pt1 = center - normalAx*(length/2);
		Point3 pt2 = center + normalAx*(length/2);

		capsule->SetFirstPoint(TOVECTOR3(pt1)/scale);
		capsule->SetSecondPoint(TOVECTOR3(pt2)/scale);
		capsule->SetMaterial(HAV_MAT_SKIN);

		shape = StaticCast<bhkShape>(capsule);
		
	}
	else {
		// Sphere
		//CalcBoundingSphere(node, tm.GetTrans(), radius, 0);

		bhkSphereShapeRef sphere = new bhkSphereShape();
		sphere->SetRadius(radius/scale);
		sphere->SetMaterial(HAV_MAT_SKIN);
		shape = StaticCast<bhkShape>(sphere);
	}

	bhkRigidBodyRef body;

	if (shape)
	{
		bhkBlendCollisionObjectRef blendObj = new bhkBlendCollisionObject();
		body = new bhkRigidBody();

		Matrix3 tm = ragdollParent->GetObjTMAfterWSM(0);
		
		//Calculate Object Offset Matrix
		Matrix3 otm(1);
		Point3 pos = ragdollParent->GetObjOffsetPos();
		otm.PreTranslate(pos);
		Quat quat = ragdollParent->GetObjOffsetRot();
		PreRotateMatrix(otm, quat);
		Matrix3 otmInvert = otm;
		otmInvert.Invert();

		//correct object tm
		Matrix3 tmbhk = otmInvert * tm;

		//set geometric parameters
		body->SetRotation(TOQUATXYZW(Quat(tmbhk).Invert()));
		body->SetTranslation(TOVECTOR4(tmbhk.GetTrans() / scale));
		body->SetCenter(TOVECTOR4(ragdollParent->GetObjOffsetPos())/scale);

		//set physics
		if (IParamBlock2* rbParameters = rbMod->GetParamBlockByID(PB_RB_MOD_PBLOCK)) {
			//These are fundamental parameters

			int lyr = NP_DEFAULT_HVK_LAYER;
			int mtl = NP_DEFAULT_HVK_MATERIAL;
			int msys = NP_DEFAULT_HVK_MOTION_SYSTEM;
			int qtype = NP_DEFAULT_HVK_QUALITY_TYPE;
			float mass = NP_DEFAULT_HVK_MASS;
			float lindamp = NP_DEFAULT_HVK_LINEAR_DAMPING;
			float angdamp = NP_DEFAULT_HVK_ANGULAR_DAMPING;
			float frict = NP_DEFAULT_HVK_FRICTION;
			float maxlinvel = NP_DEFAULT_HVK_MAX_LINEAR_VELOCITY;
			float maxangvel = NP_DEFAULT_HVK_MAX_ANGULAR_VELOCITY;
			float resti = NP_DEFAULT_HVK_RESTITUTION;
			float pendepth = NP_DEFAULT_HVK_PENETRATION_DEPTH;
			Point3 InertiaTensor;


			rbParameters->GetValue(PA_RB_MOD_MASS, 0, mass, FOREVER);
			rbParameters->GetValue(PA_RB_MOD_RESTITUTION, 0, resti, FOREVER);
			rbParameters->GetValue(PA_RB_MOD_FRICTION, 0, frict, FOREVER);
			rbParameters->GetValue(PA_RB_MOD_INERTIA_TENSOR, 0, InertiaTensor, FOREVER);


			rbParameters->GetValue(PA_RB_MOD_LINEAR_DAMPING, 0, lindamp, FOREVER);
			rbParameters->GetValue(PA_RB_MOD_CHANGE_ANGULAR_DAMPING, 0, angdamp, FOREVER);

			rbParameters->GetValue(PA_RB_MOD_MAX_LINEAR_VELOCITY, 0, maxlinvel, FOREVER);
			rbParameters->GetValue(PA_RB_MOD_MAX_ANGULAR_VELOCITY, 0, maxangvel, FOREVER);

			rbParameters->GetValue(PA_RB_MOD_ALLOWED_PENETRATION_DEPTH, 0, pendepth, FOREVER);
			rbParameters->GetValue(PA_RB_MOD_QUALITY_TYPE, 0, qtype, FOREVER);

			body->SetMass(mass);
			body->SetRestitution(resti);
			body->SetFriction(frict);
			body->SetLinearDamping(lindamp);
			body->SetMaxLinearVelocity(maxlinvel);
			body->SetMaxAngularVelocity(maxangvel);
			body->SetPenetrationDepth(pendepth);
			InertiaMatrix im;
			im[0][0] = InertiaTensor[0];
			im[1][1] = InertiaTensor[1];
			im[2][2] = InertiaTensor[2];

			body->SetInertia(im);

			/*switch (qtype) {
			case QT_FIXED:
				body->SetQualityType(MO_QUAL_FIXED);
				break;
			case QT_KEYFRAMED:
				body->SetQualityType(MO_QUAL_KEYFRAMED);
				break;
			case QT_DEBRIS:
				body->SetQualityType(MO_QUAL_DEBRIS);
				break;
			case QT_MOVING:
				body->SetQualityType(MO_QUAL_MOVING);
				break;
			case QT_CRITICAL:
				body->SetQualityType(MO_QUAL_CRITICAL);
				break;
			case QT_BULLET:
				body->SetQualityType(MO_QUAL_BULLET);
				break;
			case QT_KEYFRAMED_REPORTING:
				body->SetQualityType(MO_QUAL_KEYFRAMED_REPORT);
				break;
			}*/

			body->SetSkyrimLayer(SkyrimLayer::SKYL_BIPED);
			body->SetSkyrimLayerCopy(SkyrimLayer::SKYL_BIPED);

			body->SetMotionSystem(MotionSystem::MO_SYS_BOX);
			body->SetDeactivatorType(DeactivatorType::DEACTIVATOR_NEVER);
			body->SetSolverDeactivation(SolverDeactivation::SOLVER_DEACTIVATION_LOW);
			body->SetQualityType(MO_QUAL_FIXED);

		}
		
		if (constraintMod && ragdollParent->GetParentNode() && parent->GetParent()) {
			if (constraintMod->ClassID() == HK_CONSTRAINT_RAGDOLL_CLASS_ID) {
				bhkRagdollConstraintRef ragdollConstraint = new bhkRagdollConstraint();
				
				//entities
				ragdollConstraint->AddEntity(body);
				NiNodeRef parentRef = parent->GetParent();
				bhkRigidBodyRef nifParentRigidBody;
				while (parentRef) {
					if (parentRef->GetCollisionObject()) {
						nifParentRigidBody = StaticCast<bhkRigidBody>(StaticCast<bhkBlendCollisionObject>(parentRef->GetCollisionObject())->GetBody());
						break;
					}
					parentRef = parentRef->GetParent();
				}
				if (!nifParentRigidBody)
					throw exception(FormatText("Unable to find NIF constraint parent for ragdoll node %s", ragdollParent->GetName()));
				ragdollConstraint->AddEntity(nifParentRigidBody);

				RagdollDescriptor desc;
				//parameters
				if (IParamBlock2* constraintParameters = constraintMod->GetParamBlockByID(PB_CONSTRAINT_MOD_COMMON_SPACES_PARAMS)) {
					Point3 pivotA;
					Matrix3 parentRotation;
					Point3 pivotB;
					Matrix3 childRotation;
					constraintParameters->GetValue(PA_CONSTRAINT_MOD_CHILD_SPACE_TRANSLATION, 0, pivotB, FOREVER);
					constraintParameters->GetValue(PA_CONSTRAINT_MOD_CHILD_SPACE_ROTATION, 0, childRotation, FOREVER);
					constraintParameters->GetValue(PA_CONSTRAINT_MOD_PARENT_SPACE_TRANSLATION, 0, pivotA, FOREVER);
					constraintParameters->GetValue(PA_CONSTRAINT_MOD_PARENT_SPACE_ROTATION, 0, parentRotation, FOREVER);
					
					desc.pivotA = TOVECTOR4(pivotA);
					desc.pivotB = TOVECTOR4(pivotB);
					desc.planeA = TOVECTOR4(parentRotation.GetRow(0));
					desc.motorA = TOVECTOR4(parentRotation.GetRow(1));
					desc.twistA = TOVECTOR4(parentRotation.GetRow(2));
					desc.planeB = TOVECTOR4(childRotation.GetRow(0));
					desc.motorB = TOVECTOR4(childRotation.GetRow(1));
					desc.twistB = TOVECTOR4(childRotation.GetRow(2));
					
				}
				if (IParamBlock2* constraintParameters = constraintMod->GetParamBlockByID(PB_RAGDOLL_MOD_PBLOCK)) {
					float coneMaxAngle;
					float planeMinAngle;
					float planeMaxAngle;
					float coneMinAngle;
					float twistMinAngle;
					float maxFriction;

					constraintParameters->GetValue(PA_RAGDOLL_MOD_CONE_ANGLE, 0, coneMaxAngle, FOREVER);
					constraintParameters->GetValue(PA_RAGDOLL_MOD_PLANE_MIN, 0, planeMinAngle, FOREVER);
					constraintParameters->GetValue(PA_RAGDOLL_MOD_PLANE_MAX, 0, planeMaxAngle, FOREVER);
					constraintParameters->GetValue(PA_RAGDOLL_MOD_TWIST_MIN, 0, coneMinAngle, FOREVER);
					constraintParameters->GetValue(PA_RAGDOLL_MOD_TWIST_MAX, 0, twistMinAngle, FOREVER);
					constraintParameters->GetValue(PA_RAGDOLL_MOD_MAX_FRICTION_TORQUE, 0, maxFriction, FOREVER);

					desc.coneMaxAngle = TORAD(coneMaxAngle);
					desc.planeMinAngle = TORAD(planeMinAngle);
					desc.planeMaxAngle = TORAD(planeMaxAngle);
					desc.coneMaxAngle = TORAD(coneMinAngle);
					desc.twistMinAngle = TORAD(twistMinAngle);
					desc.maxFriction = maxFriction;


				}
				ragdollConstraint->SetRagdoll(desc);
				body->AddConstraint(ragdollConstraint);
			}
			else if (constraintMod->ClassID() == HK_CONSTRAINT_HINGE_CLASS_ID) {
				bhkLimitedHingeConstraintRef limitedHingeConstraint = new bhkLimitedHingeConstraint();

				//entities
				limitedHingeConstraint->AddEntity(body);
				NiNodeRef parentRef = parent->GetParent();
				bhkRigidBodyRef nifParentRigidBody;
				while (parentRef) {
					if (parentRef->GetCollisionObject()) {
						nifParentRigidBody = StaticCast<bhkRigidBody>(StaticCast<bhkBlendCollisionObject>(parentRef->GetCollisionObject())->GetBody());
						break;
					}
					parentRef = parentRef->GetParent();
				}
				if (!nifParentRigidBody)
					throw exception(FormatText("Unable to find NIF constraint parent for limited hinge node %s", ragdollParent->GetName()));
				limitedHingeConstraint->AddEntity(nifParentRigidBody);

				LimitedHingeDescriptor lh;

				if (IParamBlock2* constraintParameters = constraintMod->GetParamBlockByID(PB_CONSTRAINT_MOD_COMMON_SPACES_PARAMS)) {
					Matrix3 parentRotation;
					Matrix3 childRotation;
					constraintParameters->GetValue(PA_CONSTRAINT_MOD_CHILD_SPACE_ROTATION, 0, childRotation, FOREVER);
					constraintParameters->GetValue(PA_CONSTRAINT_MOD_PARENT_SPACE_ROTATION, 0, parentRotation, FOREVER);

					lh.perp2AxleInA1 = TOVECTOR4(parentRotation.GetRow(0));
					lh.perp2AxleInA2 = TOVECTOR4(parentRotation.GetRow(1));
					lh.axleA = TOVECTOR4(parentRotation.GetRow(2));
					lh.perp2AxleInB1 = TOVECTOR4(childRotation.GetRow(0));
					lh.perp2AxleInB2 = TOVECTOR4(childRotation.GetRow(1));
					lh.axleB = TOVECTOR4(childRotation.GetRow(2));
					
				}
				if (IParamBlock2* constraintParameters = constraintMod->GetParamBlockByID(PB_HINGE_MOD_PBLOCK)) {
					float minAngle;
					float maxAngle;
					float maxFriction;

					constraintParameters->GetValue(PA_HINGE_MOD_LIMIT_MIN, 0, minAngle, FOREVER);
					constraintParameters->GetValue(PA_HINGE_MOD_LIMIT_MAX, 0, maxAngle, FOREVER);
					constraintParameters->GetValue(PA_HINGE_MOD_MAX_FRICTION_TORQUE, 0, maxFriction, FOREVER);
					//	constraintParameters->SetValue(PA_HINGE_MOD_MOTOR_TYPE, 0, lh.motor., 0);

					lh.minAngle = TORAD(minAngle);
					lh.maxAngle = TORAD(maxAngle);
					lh.maxAngle = maxFriction;

				}
				limitedHingeConstraint->SetLimitedHinge(lh);
				body->AddConstraint(limitedHingeConstraint);
			}
		}


		//InitializeRigidBody(body, node);
		body->SetShape(shape);
		blendObj->SetBody(StaticCast<NiObject>(body));
		parent->SetCollisionObject(StaticCast<NiCollisionObject>(blendObj));
	}

	////rigid body parameters
	//	// get data from node
	//int lyr = NP_DEFAULT_HVK_LAYER;
	//int mtl = NP_DEFAULT_HVK_MATERIAL;
	//int msys = NP_DEFAULT_HVK_MOTION_SYSTEM;
	//int qtype = NP_DEFAULT_HVK_QUALITY_TYPE;
	//float mass = NP_DEFAULT_HVK_MASS;
	//float lindamp = NP_DEFAULT_HVK_LINEAR_DAMPING;
	//float angdamp = NP_DEFAULT_HVK_ANGULAR_DAMPING;
	//float frict = NP_DEFAULT_HVK_FRICTION;
	//float maxlinvel = NP_DEFAULT_HVK_MAX_LINEAR_VELOCITY;
	//float maxangvel = NP_DEFAULT_HVK_MAX_ANGULAR_VELOCITY;
	//float resti = NP_DEFAULT_HVK_RESTITUTION;
	//float pendepth = NP_DEFAULT_HVK_PENETRATION_DEPTH;
	//BOOL transenable = TRUE;

	//if (IParamBlock2* rbParameters = rbMod->GetParamBlockByID(PB_SHAPE_MOD_PBLOCK))
	//{
	//	//These are fundamental parameters
	//	rbParameters->GetValue(PA_RB_MOD_MASS, 0, mass, FOREVER);
	//	rbParameters->GetValue(PA_RB_MOD_RESTITUTION, 0, resti, FOREVER);
	//	rbParameters->GetValue(PA_RB_MOD_FRICTION, 0, frict, FOREVER);

	//	rbParameters->GetValue(PA_RB_MOD_LINEAR_DAMPING, 0, lindamp, FOREVER);
	//	rbParameters->GetValue(PA_RB_MOD_CHANGE_ANGULAR_DAMPING, 0, angdamp, FOREVER);

	//	rbParameters->GetValue(PA_RB_MOD_MAX_LINEAR_VELOCITY, 0, maxlinvel, FOREVER);
	//	rbParameters->GetValue(PA_RB_MOD_MAX_ANGULAR_VELOCITY, 0, maxangvel, FOREVER);

	//	rbParameters->GetValue(PA_RB_MOD_ALLOWED_PENETRATION_DEPTH, 0, pendepth, FOREVER);

	//	rbParameters->GetValue(PA_RB_MOD_QUALITY_TYPE, 0, qtype, FOREVER);


	//	switch (qtype) {
	//	case MO_QUAL_INVALID:
	//		break;
	//	case QT_FIXED:
	//		rbParameters->SetValue(PA_RB_MOD_QUALITY_TYPE, 0, MO_QUAL_FIXED, 0);
	//		break;
	//	case MO_QUAL_KEYFRAMED:
	//		rbParameters->SetValue(PA_RB_MOD_QUALITY_TYPE, 0, QT_KEYFRAMED, 0);
	//		break;
	//	case MO_QUAL_DEBRIS:
	//		rbParameters->SetValue(PA_RB_MOD_QUALITY_TYPE, 0, QT_DEBRIS, 0);
	//		break;
	//	case MO_QUAL_MOVING:
	//		rbParameters->SetValue(PA_RB_MOD_QUALITY_TYPE, 0, QT_MOVING, 0);
	//		break;
	//	case MO_QUAL_CRITICAL:
	//		rbParameters->SetValue(PA_RB_MOD_QUALITY_TYPE, 0, QT_CRITICAL, 0);
	//		break;
	//	case MO_QUAL_BULLET:
	//		rbParameters->SetValue(PA_RB_MOD_QUALITY_TYPE, 0, QT_BULLET, 0);
	//		break;
	//	case MO_QUAL_USER:
	//		break;
	//	case MO_QUAL_CHARACTER:
	//		break;
	//	case MO_QUAL_KEYFRAMED_REPORT:
	//		rbParameters->SetValue(PA_RB_MOD_QUALITY_TYPE, 0, QT_KEYFRAMED_REPORTING, 0);
	//		break;
	//	}

	//	// setup body
	//	bhkRigidBodyRef body = transenable ? new bhkRigidBodyT() : new bhkRigidBody();

	//	OblivionLayer obv_layer; SkyrimLayer sky_layer;
	//	GetHavokLayersFromIndex(lyr, (int*)&obv_layer, (int*)&sky_layer);
	//	body->SetLayer(obv_layer);
	//	body->SetLayerCopy(obv_layer);
	//	body->SetSkyrimLayer(sky_layer);

	//	body->SetMotionSystem(MotionSystem(msys));
	//	body->SetQualityType(MotionQuality(qtype));
	//	body->SetMass(mass);
	//	body->SetLinearDamping(lindamp);
	//	body->SetAngularDamping(angdamp);
	//	body->SetFriction(frict);
	//	body->SetRestitution(resti);
	//	body->SetMaxLinearVelocity(maxlinvel);
	//	body->SetMaxAngularVelocity(maxangvel);
	//	body->SetPenetrationDepth(pendepth);
	//	body->SetCenter(center);
	//	QuaternionXYZW q; q.x = q.y = q.z = 0; q.w = 1.0f;
	//	body->SetRotation(q);
	//}
}