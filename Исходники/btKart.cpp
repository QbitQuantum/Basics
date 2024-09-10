void btKart::updateFriction(btScalar timeStep)
{
    //calculate the impulse, so that the wheels don't move sidewards
    for (int i=0;i<getNumWheels();i++)
    {
        m_sideImpulse[i]       = btScalar(0.);
        btWheelInfo& wheelInfo = m_wheelInfo[i];

        btRigidBody* groundObject =
            (btRigidBody*) wheelInfo.m_raycastInfo.m_groundObject;

        if(!groundObject) continue;
        const btTransform& wheelTrans = getWheelTransformWS( i );

        btMatrix3x3 wheelBasis0 = wheelTrans.getBasis();
        m_axle[i] = btVector3(wheelBasis0[0][m_indexRightAxis],
                              wheelBasis0[1][m_indexRightAxis],
                              wheelBasis0[2][m_indexRightAxis]  );

        const btVector3& surfNormalWS =
                        wheelInfo.m_raycastInfo.m_contactNormalWS;
        btScalar proj = m_axle[i].dot(surfNormalWS);
        m_axle[i]    -= surfNormalWS * proj;
        m_axle[i]     = m_axle[i].normalize();

        m_forwardWS[i] = surfNormalWS.cross(m_axle[i]);
        m_forwardWS[i].normalize();

        resolveSingleBilateral(*m_chassisBody,
                               wheelInfo.m_raycastInfo.m_contactPointWS,
                               *groundObject,
                               wheelInfo.m_raycastInfo.m_contactPointWS,
                               btScalar(0.), m_axle[i],m_sideImpulse[i],
                               timeStep);

        btScalar sideFrictionStiffness2 = btScalar(1.0);
        m_sideImpulse[i] *= sideFrictionStiffness2;
    }

    btScalar sideFactor = btScalar(1.);
    btScalar fwdFactor = 0.5;

    bool sliding = false;
    for (int wheel=0; wheel<getNumWheels(); wheel++)
    {
        btWheelInfo& wheelInfo        = m_wheelInfo[wheel];
        m_wheelInfo[wheel].m_skidInfo = btScalar(1.);
        m_forwardImpulse[wheel]       = btScalar(0.);

        btRigidBody* groundObject =
            (btRigidBody*) wheelInfo.m_raycastInfo.m_groundObject;
        if(!groundObject) continue;

        if(m_zipper_active && m_zipper_velocity > 0)
        {
            if (wheel==2 || wheel==3)
            {
                // The zipper velocity is the speed that should be
                // reached. So compute the impulse to accelerate the
                // kart up to that speed:
                m_forwardImpulse[wheel] =
                    0.5f*(m_zipper_velocity -
                          getRigidBody()->getLinearVelocity().length())
                    / m_chassisBody->getInvMass();
            }

        }
        else
        {
            btScalar rollingFriction = 0.f;

            if (wheelInfo.m_engineForce != 0.f)
            {
                rollingFriction = wheelInfo.m_engineForce* timeStep;
            }
            else
            {
                btScalar defaultRollingFrictionImpulse = 0.f;
                btScalar maxImpulse = wheelInfo.m_brake
                                    ? wheelInfo.m_brake
                                    : defaultRollingFrictionImpulse;
                btWheelContactPoint contactPt(m_chassisBody, groundObject,
                                     wheelInfo.m_raycastInfo.m_contactPointWS,
                                     m_forwardWS[wheel],maxImpulse);
                rollingFriction = calcRollingFriction(contactPt);
                // This is a work around for the problem that a kart shakes
                // if it is braking: we get a minor impulse forward, which
                // bullet then tries to offset by applying a backward
                // impulse - which is a bit too big, causing a impulse
                // backwards, ... till the kart is shaking backwards and
                // forwards. By onlyu applying half of the impulse in cae
                // of low friction this goes away.
                if(wheelInfo.m_brake && fabsf(rollingFriction)<10)
                    rollingFriction*=0.5f;
            }

            m_forwardImpulse[wheel] = rollingFriction;
        }
        if(m_time_additional_impulse>0)
        {
            sliding = true;
            m_wheelInfo[wheel].m_skidInfo = 0.0f;
        }
        else
        {
            btScalar maximp         = wheelInfo.m_wheelsSuspensionForce
                                    * timeStep * wheelInfo.m_frictionSlip;
            btScalar maximpSide     = maximp;
            btScalar maximpSquared  = maximp * maximpSide;

            btScalar x = (m_forwardImpulse[wheel] ) * fwdFactor;
            btScalar y = (m_sideImpulse[wheel]    ) * sideFactor;

            btScalar impulseSquared = (x*x + y*y);

            if (impulseSquared > maximpSquared)
            {
                sliding = true;
                btScalar factor = maximp / btSqrt(impulseSquared);
                m_wheelInfo[wheel].m_skidInfo *= factor;
            }   // if impulseSquared > maximpSquared
        }   // else (!m_timed_impulse
    }   // for (int wheel=0; wheel<getNumWheels(); wheel++)


    m_zipper_active   = false;
    m_zipper_velocity = 0;

    // The kart just stopped skidding. Adjust the velocity so that
    // it points in the right direction.
    // FIXME: this is not good enough, we need some smooth interpolation here.
    if(m_is_skidding && m_skid_angular_velocity == 0)
    {
        btVector3 v = m_chassisBody->getLinearVelocity();
        v.setZ(sqrt(v.getX()*v.getX()+v.getZ()*v.getZ()));
        v.setX(0);
        btVector3 v_new = m_chassisBody->getWorldTransform().getBasis()*v;
        m_chassisBody->setLinearVelocity(v_new);
        m_is_skidding = false;
    }

    if(m_skid_angular_velocity!=0)
    {
        m_is_skidding = true;
        // Skidding is implemented by not having any forward impulse,
        // but only add a side impulse
        for(unsigned int i=0; i<4; i++)
        {
            m_forwardImpulse[i] = 0;
            m_sideImpulse[i] = 0;
        }
        btVector3 av = m_chassisBody->getAngularVelocity();
        av.setY(m_skid_angular_velocity);
        m_chassisBody->setAngularVelocity(av);
    }
    else if (sliding && (m_allow_sliding || m_time_additional_impulse>0) )
    {
        for (int wheel = 0; wheel < getNumWheels(); wheel++)
        {
            if (m_sideImpulse[wheel] != btScalar(0.)       &&
                m_wheelInfo[wheel].m_skidInfo< btScalar(1.)   )
            {
                m_forwardImpulse[wheel] *= m_wheelInfo[wheel].m_skidInfo;
                m_sideImpulse[wheel] *= m_wheelInfo[wheel].m_skidInfo;
            }
        }   // for wheel <getNumWheels
    }   // if sliding

    // Apply the impulses
    // ------------------
    for (int wheel = 0;wheel<getNumWheels() ; wheel++)
    {
        btWheelInfo& wheelInfo = m_wheelInfo[wheel];
        btVector3 rel_pos      = wheelInfo.m_raycastInfo.m_contactPointWS
                                 - m_chassisBody->getCenterOfMassPosition();

        if (m_forwardImpulse[wheel] != btScalar(0.))
        {
            m_chassisBody->applyImpulse(
                                  m_forwardWS[wheel]*(m_forwardImpulse[wheel]),
#define COMPATIBLE_0_7_3
#ifdef COMPATIBLE_0_7_3
                                  // This was apparently done to help hexley
                                  btVector3(0,0,0));
#else
                                  rel_pos);
#endif
        }
        if (m_sideImpulse[wheel] != btScalar(0.))
        {
            btRigidBody* groundObject =
                (btRigidBody*) m_wheelInfo[wheel].m_raycastInfo.m_groundObject;
            btVector3 rel_pos2 = wheelInfo.m_raycastInfo.m_contactPointWS
                               - groundObject->getCenterOfMassPosition();
            //adjust relative position above ground so that force only
            // acts sideways
            btVector3 delta_vec = (wheelInfo.m_raycastInfo.m_hardPointWS
                                - wheelInfo.m_raycastInfo.m_contactPointWS);
            if (delta_vec.length() != btScalar (0))
            {
                delta_vec = delta_vec.normalize();
                rel_pos -= delta_vec * rel_pos.dot(delta_vec);
            }

            btVector3 sideImp = m_axle[wheel] * m_sideImpulse[wheel];

#if defined ROLLING_INFLUENCE_FIX && !defined COMPATIBLE_0_7_3
            // fix. It only worked if car's up was along Y - VT.
            btVector3 vChassisWorldUp =
                                    getRigidBody()->getCenterOfMassTransform()
                                   .getBasis().getColumn(m_indexUpAxis);
            rel_pos -= vChassisWorldUp * (vChassisWorldUp.dot(rel_pos) *
                                          (1.f-wheelInfo.m_rollInfluence) );
#else
            rel_pos[m_indexUpAxis] *= wheelInfo.m_rollInfluence;
#endif
            m_chassisBody->applyImpulse(sideImp,rel_pos);

            //apply friction impulse on the ground
            groundObject->applyImpulse(-sideImp,rel_pos2);
        }   // if (m_sideImpulse[wheel] != btScalar(0.))
    }   // for wheel<getNumWheels()