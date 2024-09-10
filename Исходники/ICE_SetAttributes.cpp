SICALLBACK MOM_SetAttributes_Evaluate( ICENodeContext& in_ctxt )
{
	// The current output port being evaluated...
   ULONG out_portID = in_ctxt.GetEvaluatedOutputPortID( );

   if(gSimulation == NULL)
      return CStatus::OK;

	switch( out_portID )
	{
		case ID_OUT_base:
		{
         CDataArrayLong baseData( in_ctxt, ID_IN_base );
         CDataArrayLong idData( in_ctxt, ID_IN_id );
         rbdID rbd_ID;
         CIndexSet indexSet( in_ctxt );

			// Get the output port array ...
			CDataArrayLong outData( in_ctxt );

			// get all of the input SET data!
			CDataArrayBool setPosData( in_ctxt, ID_IN_set_position);
			CDataArrayBool setRotData( in_ctxt, ID_IN_set_orientation);
			CDataArrayBool setLinvelData( in_ctxt, ID_IN_set_linvelocity);
			CDataArrayBool setAngvelData( in_ctxt, ID_IN_set_angvelocity);
			CDataArrayBool setStateData( in_ctxt, ID_IN_set_state);
			CDataArrayBool setMassData( in_ctxt, ID_IN_set_mass);
			CDataArrayBool setBounceData( in_ctxt, ID_IN_set_bounce);
			CDataArrayBool setFrictionData( in_ctxt, ID_IN_set_friction);
			CDataArrayBool setLindampData( in_ctxt, ID_IN_set_lindamping);
			CDataArrayBool setAngdampData( in_ctxt, ID_IN_set_angdamping);
			CDataArrayBool setLintreshData( in_ctxt, ID_IN_set_lintreshold);
			CDataArrayBool setAngtreshData( in_ctxt, ID_IN_set_angtreshold);

			// get all of the input data!
			CDataArrayVector3f posData( in_ctxt, ID_IN_position);
			CDataArrayVector3f rotData( in_ctxt, ID_IN_orientation);
			CDataArrayVector3f linvelData( in_ctxt, ID_IN_linvelocity);
			CDataArrayVector3f angvelData( in_ctxt, ID_IN_angvelocity);
			CDataArrayLong stateData( in_ctxt, ID_IN_state);
			CDataArrayFloat massData( in_ctxt, ID_IN_mass);
			CDataArrayFloat bounceData( in_ctxt, ID_IN_bounce);
			CDataArrayFloat frictionData( in_ctxt, ID_IN_friction);
			CDataArrayFloat lindampData( in_ctxt, ID_IN_lindamping);
			CDataArrayFloat angdampData( in_ctxt, ID_IN_angdamping);
			CDataArrayFloat lintreshData( in_ctxt, ID_IN_lintreshold);
			CDataArrayFloat angtreshData( in_ctxt, ID_IN_angtreshold);

         // get the index set iterator
         btTransform bodyTransform;
         CVector3f bodyPos,linvel,angvel;
         btQuaternion bodyRot;
			CRotation rot;
			CQuaternion quat;
			CVector3f anglesf;
			CVector3 angles;

			for(CIndexSet::Iterator it = indexSet.Begin(); it.HasNext(); it.Next())
			{
            rbd_ID.primary = (int)(baseData.IsConstant() ? baseData[0] : baseData[it]);
            rbd_ID.secondary = (int)(idData.IsConstant() ? idData[0] : idData[it]);
            btRigidBodyReference * bodyRef = gSimulation->GetRigidBody(rbd_ID);
            if(bodyRef != NULL)
            {
               // take care of the positions
               if((setPosData.IsConstant() ? setPosData[0] : setPosData[it]) == true)
               {
                  bodyPos = posData.IsConstant() ? posData[0] : posData[it];
                  bodyTransform = bodyRef->GetWorldTransform();
                  bodyTransform.setOrigin(btVector3(bodyPos.GetX(),bodyPos.GetY(),bodyPos.GetZ()));
                  bodyRef->SetWorldTransform(bodyTransform);
               }
               // take care of the orientations
               if((setRotData.IsConstant() ? setRotData[0] : setRotData[it]) == true)
               {
                  anglesf = rotData.IsConstant() ? rotData[0] : rotData[it];
                  rot.SetFromXYZAngles(DegreesToRadians(anglesf.GetX()),DegreesToRadians(anglesf.GetY()),DegreesToRadians(anglesf.GetZ()));
                  quat = rot.GetQuaternion();
                  bodyTransform = bodyRef->GetWorldTransform();
                  bodyTransform.setRotation(btQuaternion(quat.GetX(),quat.GetY(),quat.GetZ(),quat.GetW()));
                  bodyRef->SetWorldTransform(bodyTransform);
               }
               // take care of the linear velocity
               if((setLinvelData.IsConstant() ? setLinvelData[0] : setLinvelData[it]) == true)
               {
                  linvel = linvelData.IsConstant() ? linvelData[0] : linvelData[it];
                  bodyRef->body->setLinearVelocity(btVector3(linvel.GetX(),linvel.GetY(),linvel.GetZ()));
               }
               // take care of the angular velocity
               if((setAngvelData.IsConstant() ? setAngvelData[0] : setAngvelData[it]) == true)
               {
                  angvel = angvelData.IsConstant() ? angvelData[0] : angvelData[it];
                  bodyRef->body->setAngularVelocity(btVector3(angvel.GetX(),angvel.GetY(),angvel.GetZ()));
               }
               // take care of the state
               if((setStateData.IsConstant() ? setStateData[0] : setStateData[it]) == true)
               {
                  int state = stateData.IsConstant() ? stateData[0] : stateData[it];
                  if(state == 0)
                     bodyRef->body->forceActivationState(ACTIVE_TAG);
                  else if(state == 1)
                     bodyRef->body->forceActivationState(ISLAND_SLEEPING);
                  else if(state == 2)
                     bodyRef->body->forceActivationState(DISABLE_SIMULATION);
               }
               // take care of the mass
               if((setMassData.IsConstant() ? setMassData[0] : setMassData[it]) == true)
               {
                  // compute the inertia
                  bodyRef->mass = massData.IsConstant() ? massData[0] : massData[it];
                  btVector3 inertia(0,0,0);
                  if(bodyRef->mass > 0.0f)
                     bodyRef->body->getCollisionShape()->calculateLocalInertia(bodyRef->mass,inertia);
                  bodyRef->body->setMassProps(bodyRef->mass,inertia);
               }
               // take care of the bounce
               if((setBounceData.IsConstant() ? setBounceData[0] : setBounceData[it]) == true)
               {
                  bodyRef->body->setRestitution(bounceData.IsConstant() ? bounceData[0] : bounceData[it]);
               }
               // take care of the friction
               if((setFrictionData.IsConstant() ? setFrictionData[0] : setFrictionData[it]) == true)
               {
                  bodyRef->body->setFriction(frictionData.IsConstant() ? frictionData[0] : frictionData[it]);
               }
               // take care of the linear damping
               if((setLindampData.IsConstant() ? setLindampData[0] : setLindampData[it]) == true)
               {
                  float angdamp = bodyRef->body->getAngularDamping();
                  bodyRef->body->setDamping(lindampData.IsConstant() ? lindampData[0] : lindampData[it],angdamp);
               }
               // take care of the angular damping
               if((setAngdampData.IsConstant() ? setAngdampData[0] : setAngdampData[it]) == true)
               {
                  float lindamp = bodyRef->body->getLinearDamping();
                  bodyRef->body->setDamping(lindamp,angdampData.IsConstant() ? angdampData[0] : angdampData[it]);
               }
               // take care of the linear treshold
               if((setLintreshData.IsConstant() ? setLintreshData[0] : setLintreshData[it]) == true)
               {
                  float angtresh = bodyRef->body->getAngularSleepingThreshold();
                  bodyRef->body->setSleepingThresholds(lintreshData.IsConstant() ? lintreshData[0] : lintreshData[it],angtresh);
               }
               // take care of the angular treshold
               if((setAngtreshData.IsConstant() ? setAngtreshData[0] : setAngtreshData[it]) == true)
               {
                  float lintresh = bodyRef->body->getLinearSleepingThreshold();
                  bodyRef->body->setSleepingThresholds(lintresh,angtreshData.IsConstant() ? angtreshData[0] : angtreshData[it]);
               }
            }
            outData[it] = rbd_ID.primary;
			}
         break;
		}
	};

	return CStatus::OK;
}