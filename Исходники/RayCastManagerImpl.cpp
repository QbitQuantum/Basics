        int RayCastManagerImpl::CastSweep(const XMFLOAT3& p_origin, XMFLOAT3& p_direction, float p_width, const float& p_range, int& o_flag)
        {
            if(p_range <= 0.0f)
            {
                cout << "Physcs. Raytracer. Sweep. Range of sweep was zero or below" << endl;
                return -1;
            }
            // Cast directx things to physx
            PxVec3 origin = PxVec3(p_origin.x, p_origin.y, p_origin.z);
            PxVec3 direction = PxVec3(p_direction.x, p_direction.y, p_direction.z);
            direction.normalize();
            PxSweepBuffer hit; // Used to save the hit
            /// Paramters for the sweep
            // PxGeometry* geometry
            bool status = m_utils.m_worldScene->sweep(PxSphereGeometry(p_width), PxTransform(origin), direction, p_range, hit, PxHitFlag::eMESH_BOTH_SIDES);
            // hit.block.position;
            if(!status && !hit.hasBlock)
            {
                // No hit detected, return -1 TODOKO Maybee i should return something better?
                return -1;
            }

            // Start with checking static and dynamic rigid bodies
            unordered_map<PxRigidActor*, int> idsByRigidBody = m_utils.m_rigidBodyManager->GetIDsByBodies();
            if(idsByRigidBody.find(hit.block.actor) != idsByRigidBody.end())
            {
                PxRigidActor* actorAsRigic = (PxRigidActor*)hit.block.actor;
                if(actorAsRigic->isRigidDynamic())
                {
                    PxRigidDynamic* actorsAsDynamic = (PxRigidDynamic*)hit.block.actor;
                    if(actorsAsDynamic->getRigidBodyFlags() & PxRigidBodyFlag::eKINEMATIC)
                    {
                        o_flag = 0;
                    }
                }
                else if(actorAsRigic->isRigidStatic())
                {
                    o_flag = 3;
                }
                return idsByRigidBody.find(hit.block.actor)->second;
            }
            else
            {
                // Nothing
            }
            // Now comes the difficult task of checking vs character controllers
            unordered_map<PxController*, int> idsByCharacterController = m_utils.m_characterControlManager->GetIdsByControllers();
            for(auto pairs : idsByCharacterController) // Loop through every pair in the list
            {
                if(pairs.first->getActor() == hit.block.actor) // The first part contains the actor pointer
                {
                    o_flag = 1;
                    return pairs.second; // If this is true we found a hit vs character controller, second contains ID
                }
            }

            return -1;
        }