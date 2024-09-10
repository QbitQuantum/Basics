void NxRobot::handleContactPair(NxContactPair& pair, NxU32 robotIndex)
{
    NxContactStreamIterator i(pair.stream);

    while(i.goNextPair())
    {
        NxShape * s = i.getShape(robotIndex); //umas das partes do robo (o robo eh um unico actor com as MESHs: rodas, driblador, corpo)
        NxShape * s1 = i.getShape(1-robotIndex); //corpo que o robo esta colidindo

        while(i.goNextPatch())
        {
            const NxVec3& contactNormal = i.getPatchNormal();

            while(i.goNextPoint())
            {
                //user can also call getPoint() and getSeparation() here

                const NxVec3& contactPoint = i.getPoint();

                //add forces:

                /*//assuming front wheel drive we need to apply a force at the wheels.
                if (s->is(NX_SHAPE_CAPSULE) && s->userData != NULL) {
                	//assuming only the wheels of the car are capsules, otherwise we need more checks.
                	//this branch can't be pulled out of loops because we have to do a full iteration through the stream

                	NxQuat local2global = s->getActor().getGlobalOrientationQuat();
                	NxWheel* w = (NxWheel*)s->userData;
                	if (!w->getWheelFlag(NX_WF_USE_WHEELSHAPE))
                	{
                		NxWheel1 * wheel = static_cast<NxWheel1*>(w);
                		wheel->contactInfo.otherActor = pair.actors[1-robotIndex];
                		wheel->contactInfo.contactPosition = contactPoint;

                		wheel->contactInfo.contactPositionLocal = contactPoint;
                		wheel->contactInfo.contactPositionLocal -= this->getActor()->getGlobalPosition();
                		local2global.inverseRotate(wheel->contactInfo.contactPositionLocal);

                		wheel->contactInfo.contactNormal = contactNormal;
                		if (wheel->contactInfo.otherActor->isDynamic())
                		{
                			NxVec3 globalV = s->getActor().getLocalPointVelocity(wheel->getWheelPos());
                			globalV -= wheel->contactInfo.otherActor->getLinearVelocity();
                			local2global.inverseRotate(globalV);
                			wheel->contactInfo.relativeVelocity = globalV.x;
                			//printf("%2.3f (%2.3f %2.3f %2.3f)\n", wheel->contactInfo.relativeVelocity,
                			//	globalV.x, globalV.y, globalV.z);
                		}
                		else
                		{
                			NxVec3 vel = s->getActor().getLocalPointVelocity(wheel->getWheelPos());
                			local2global.inverseRotate(vel);
                			wheel->contactInfo.relativeVelocity = vel.x;
                			wheel->contactInfo.relativeVelocitySide = vel.z;
                		}
                		NX_ASSERT(wheel->hasGroundContact());
                		//printf(" Wheel %x is touching\n", wheel);
                	}
                }*/
                const char* name = s->getName();
                if(name) {
                    const char* name1 = s1->getName();
                    if(name1) {
                        char* dribblerName = new char[10]; //"Driblador\0"
                        dribblerName[9] = 0;
                        memcpy(dribblerName, name, strlen(dribblerName));

                        char* ballName = new char[5]; //"Bola\0"
                        ballName[4] = 0;
                        memcpy(ballName, name1, strlen(ballName));

                        if(strcmp(dribblerName, "Driblador")==0 && strcmp(ballName, "Bola")==0) {
                            float angle = this->getAngle2DFromVehicle();
                            angle += NxPi/2.;
                            NxActor& ball = s1->getActor();
                            NxVec3 dribblerGlobalPosition = this->dribbler->getLocalPosition() + this->getPos();
                            NxVec3 r = contactPoint - dribblerGlobalPosition;
                            NxVec3 w = NxVec3(cos(angle), sin(angle), 0);
                            NxVec3 force = w.cross(r);
                            force.setMagnitude(1);
                            NxReal coefKinect = 0.5;
                            NxReal normalMagnitude = contactNormal.magnitude();
                            NxVec3 resultForce = this->dribbler->speedToExecute * 20. * coefKinect * normalMagnitude * force;
                            //NxReal teste =  resultForce.magnitude();
                            //SimulationView::DrawForce(&ball, resultForce, NxVec3(1,1,1));
                            ball.addForceAtPos(/*NxVec3(sin(angle)*this->dribbler->speedToExecute*1000000.,cos(angle)*this->dribbler->speedToExecute*1000000.,0)*/resultForce, contactPoint, NX_IMPULSE);
                            this->dribbler->speedToExecute = 0;
                        }

                        delete dribblerName;
                        delete ballName;
                    }
                }
            }
        }
    }
    //printf("----\n");
}