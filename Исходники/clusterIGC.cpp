void        CclusterIGC::Update(Time now)
{
    if (now > m_lastUpdate)
    {
        float   dt = now - m_lastUpdate;

        bool    bStarted = m_pMission->GetMissionStage() == STAGE_STARTED;
        if (bStarted)
        {
            {
                //Have any stations launch docked drones
                for (StationLinkIGC*   l = m_stations.first();
                     (l != NULL);
                     l = l->next())
                {
                    IstationIGC*    pstation = l->data();

                    ShipLinkIGC*    pslNext;
                    for (ShipLinkIGC*   psl = pstation->GetShips()->first();
                         (psl != NULL);
                         psl = pslNext)
                    {
                        IshipIGC*   pship = psl->data();
                        pslNext = psl->next();             //Get the next link now since the ship may launch
                        // const MissionParams* pmp = m_pMission->GetMissionParams(); 04/08 commented out as not needed // mmf 10/07 added so we can get at bExperimental game type
                        if (pship->GetAutopilot() && (pship->GetPilotType() < c_ptPlayer))
                        {
                            //Docked non-players on autopilot never are observers/parents
                            assert (pship->GetParentShip() == NULL);
                            assert (pship->GetChildShips()->n() == 0);

							// mmf/yp 10/07 added this so drones launch when ordered to even if OkToLaunch might be false
							// intentionally left c_cidMine out of the list otherwise miners would launch with their AI
							// 'order' to mine
	
							if (pship->OkToLaunch(now) || (pship->GetCommandID(c_cmdAccepted) == c_cidGoto) ||
							   (pship->GetCommandID(c_cmdAccepted) == c_cidBuild) )
                                pship->SetStation(NULL);
							// if (pship->OkToLaunch(now))  // mmf orig code
							//	  pship->SetStation(NULL);
							
                        }
                    }
					
					//Are any ships buzzing around the stations that a side has yet to eye? #121 #120 Imago 8/10
					if (GetShips()->n() > 0 && pstation->GetRoidID() != NA) {
						Vector pos = pstation->GetRoidPos();
						float Sig = pstation->GetRoidSig();
						float Radius = pstation->GetRoidRadius();
						if (Sig != 0.0f && Radius != 0.0f) {
							//check if they have a ship eying where the rock would be
							for (ShipLinkIGC*   psl1 = GetShips()->first(); (psl1 != NULL); psl1 = psl1->next()) {
								IshipIGC*   pship = psl1->data();
								if (pship->GetParentShip() || pship->GetSide()->GetObjectID() == pstation->GetSide()->GetObjectID() || pstation->SeenBySide(pship->GetSide()) || !pstation->GetRoidSide(pship->GetSide()->GetObjectID()))
									continue;
								bool bEye = bSimpleEye(pship->GetHullType()->GetScannerRange(),GetMission()->GetModel(OT_ship,pship->GetObjectID()),Sig,pstation->GetSide()->GetGlobalAttributeSet().GetAttribute(c_gaSignature),Radius,pos);
								if (bEye) {
									//Turkey 3/13 #353: kill asteroids for all sides in that alliance.
									IsideIGC* pside1 = pship->GetSide();
									for (SideLinkIGC* sl = m_pMission->GetSides()->first(); sl != NULL; sl = sl->next())
									{
										IsideIGC* pside2 = sl->data();
										if (pside1->AlliedSides(pside1, pside2))
										{
											pstation->SetRoidSide(pside2->GetObjectID(),false);
											GetMission()->GetIgcSite()->KillAsteroidEvent(pstation->GetRoidID(),GetObjectID(),pside2);
										}
									}
								}
							}
						}
					}
                }
            }
            {
                m_fCost = m_pMission->GetFloatConstant(c_fcidBaseClusterCost);

                float   costLifepod = m_pMission->GetFloatConstant(c_fcidLifepodCost);
                float   costTurret = m_pMission->GetFloatConstant(c_fcidTurretCost);
                float   costPlayer = m_pMission->GetFloatConstant(c_fcidPlayerCost);
                float   costDrone = m_pMission->GetFloatConstant(c_fcidDroneCost);

                //Have miners and builders do any pre-plotted moves. Allow ships to suicide.
                ShipLinkIGC*        lNext;
                for (ShipLinkIGC*   l = m_ships.first();
                     (l != NULL);
                     l = lNext)
                {
                    IshipIGC*   s = l->data();
                    lNext = l->next();

                    if (s->GetPilotType() < c_ptPlayer)
                        m_fCost += costDrone;
                    else if (s->GetParentShip() != NULL)
                        m_fCost += costTurret;
                    else
                    {
                        IhullTypeIGC*   pht = s->GetBaseHullType();
                        assert (pht);
                        m_fCost += pht->HasCapability(c_habmLifepod)
                                  ? costLifepod
                                  : costPlayer;
                    }

                    s->PreplotShipMove(now);
                }

                if (m_fCost > 0.0f)
                {
                    m_fCost *= dt / m_pMission->GetFloatConstant(c_fcidClusterDivisor);
                }

                {
                    //Have all ships on autopilot plot their moves. Allow ships to suicide.
                    ShipLinkIGC*        lNext;
                    for (ShipLinkIGC*   l = m_ships.first();
                         (l != NULL);
                         l = lNext)
                    {
                        IshipIGC*   s = l->data();
                        lNext = l->next();

                        s->PlotShipMove(now);
                    }
                }
            }

            {
                //Have all ships execute their moves
                for (ShipLinkIGC*   l = m_ships.first();
                     (l != NULL);
                     l = l->next())
                {
                    IshipIGC*   s = l->data();

                    if (s->GetParentShip() == NULL)
                    {
                        s->ExecuteShipMove(now);
                    }
                }
            }
        }
        else
            m_fCost = 0.0f;

        {
            //Call the update method on all the contained models
            //models might self-terminate in the update and nuke earlier models in the update loop

            //NYI debugging variables
            //ObjectType  oldObjectType = NA;
            //ObjectType  newObjectType = NA;

            ModelLinkIGC*       lNext;
            for (ModelLinkIGC*     l = m_models.first();
                 (l != NULL);
                 l = lNext)
            {
                //oldObjectType = newObjectType;
                //newObjectType = l->data()->GetObjectType();

                lNext = l->next();

                l->data()->Update(now);
            }
        }

        if (m_data.activeF && bStarted)
        {
            {
                //Update the bounding boxes for all moving objects & projectiles
                for (ModelLinkIGC*     l = m_models.first();
                     (l != NULL);
                     l = l->next())
                {
                    l->data()->SetBB(m_lastUpdate, now, dt);
                }

                m_tMax = dt;
            }

            m_kdrStatic.update();
            m_kdrMoving.update();

            {
                //Cast rays through the KD tree for each object
                for (ModelLinkIGC*     l = m_modelsCastRay.first();
                     (l != NULL);
                     l = l->next())
                {
                    ImodelIGC*  m = l->data();

                    HitTest*    ht = m->GetHitTest();

                    if (!ht->GetDeadF())
                    {
                        m_kdrStatic.test(ht, &m_collisions);
                        m_kdrMoving.test(ht, &m_collisions);
                    }
                }
            }

            //Sort the collisions by the time they occur
            m_collisions.sort(0);

            //Process each collision (in order)
            {
                m_tOffset = 0.0f;
                for (m_collisionID = 0; (m_collisionID < m_collisions.n()); m_collisionID++)
                {
                    const CollisionEntry& entry = m_collisions[m_collisionID];

                    if (!(entry.m_pHitTest1->GetDeadF() || entry.m_pHitTest2->GetDeadF()))
                    {
                        Time    timeCollision = m_lastUpdate + (m_tOffset + entry.m_tCollision);

                        ImodelIGC*  pModelHitTest1 = (ImodelIGC*)(entry.m_pHitTest1->GetData());
                        assert (pModelHitTest1);

                        ImodelIGC*  pModelHitTest2 = (ImodelIGC*)(entry.m_pHitTest2->GetData());
                        assert (pModelHitTest2);

                        //Give each participant in the collision a chance to handle the collision
                        //but give the "1st" model first dibs.
                        if ((pModelHitTest1->GetCluster() == this) &&
                            (pModelHitTest2->GetCluster() == this))
                        {
                            pModelHitTest1->HandleCollision(timeCollision, entry.m_tCollision, entry, pModelHitTest2);
                        }
                    }
                }

                m_collisions.purge();
            }
            {
                //Apply any damage from mines
                //Kids always follow parents in the ship list, so go from back to front
                //so that the killing a parent doesn't mean hitting dead elements in the list
                ShipLinkIGC*        lTxen;
                for (ShipLinkIGC*   l = m_ships.last();
                     (l != NULL);
                     l = lTxen)
                {
                    IshipIGC*   s = l->data();
                    lTxen = l->txen();

                    s->ApplyMineDamage();
                }
            }

            //Move each object & projectile
            {
                for (ModelLinkIGC*  l = m_models.first();
                     (l != NULL);
                     l = l->next())
                {
                    l->data()->Move();
                }
            }

            if ((m_nPass++) % c_nPassesPerUpdate == 0)
            {
                for (ModelLinkIGC*  l = m_models.first();
                     (l != NULL);
                     l = l->next())
                {
                    l->data()->UpdateSeenBySide();
                }

                m_pMission->GetIgcSite()->ClusterUpdateEvent(this);
            }
        }


        //Draw and resolve any explosions
        if (m_nExplosions != 0)
        {
            const int c_maxDmgs = 500;
            IdamageIGC* pdmgs[c_maxDmgs];
            int         nDmgs = 0;

            //Copy the list of models in the sector that can be damaged into
            for (ModelLinkIGC*  l = m_modelsPickable.first();
                 (l != NULL);
                 l = l->next())
            {
                ImodelIGC*  pmodel = l->data();
                ObjectType  type = pmodel->GetObjectType();

                //Not everything that can take damage can be affected by an explosion.
                if ((type == OT_ship) || (type == OT_asteroid) ||
                    (type == OT_station) || (type == OT_missile) || (type == OT_probe))
                {
                    pmodel->AddRef();
                    pdmgs[nDmgs++] = (IdamageIGC*)pmodel;

                    if (nDmgs == c_maxDmgs)
                        break;
                }
            }

            ImineIGC*   pmines[c_maxDmgs];
            int         nMines = 0;
            {
                for (MineLinkIGC*   l = m_mines.first(); (l != NULL); l = l->next())
                {
                    ImineIGC*   pm = l->data();
                    pm->AddRef();
                    pmines[nMines++] = pm;

                    if (nMines == c_maxDmgs)
                        break;
                }
            }

            int i = 0;
            do
            {
                ExplosionData&  e = m_explosions[i];
                m_pClusterSite->AddExplosion(e.position, e.radius, e.explosionType);

                float   dt = (e.time - m_lastUpdate) - m_tOffset;

                //Now, the painful part: applying damage to everything in the sector that could be hit
                {
                    for (int j = 0; (j < nDmgs); j++)
                    {
                        IdamageIGC*  pTarget = pdmgs[j];
                        if (pTarget->GetCluster() == this)      //Make sure it wasn't already destroyed
                        {
                            //The target is still around
                            Vector  p = pTarget->GetPosition() + dt * pTarget->GetVelocity();
                            float   d = (e.position - p).Length() - pTarget->GetRadius();

                            if (d < e.radius)
                            {
                                float   amount = e.amount;
                                if (d > 0.0f)
                                {
                                    float   f = 1.0f - (d / e.radius);
                                    amount *= f * f;
                                }

                                pTarget->ReceiveDamage(e.damageType | c_dmgidNoWarn | c_dmgidNoDebris,
                                                       amount,
                                                       e.time,
                                                       p, e.position,
                                                       e.launcher);
                            }
                        }
                    }
                }
                {
                    for (int j = 0; (j < nMines); j++)
                    {
                        ImineIGC*  pTarget = pmines[j];
                        if (pTarget->GetCluster() == this)      //Make sure it wasn't already destroyed
                        {
                            //The target is still around
                            const Vector&   p = pTarget->GetPosition();
                            float           d = (e.position - p).Length() - pTarget->GetRadius();

                            if (d < e.radius)
                            {
                                float   amount = e.amount;
                                if (d > 0.0f)
                                {
                                    float   f = 1.0f - (d / e.radius);
                                    amount *= f * f;
                                }
                                pTarget->ReduceStrength(amount);
                            }
                        }
                    }
                }

                if (e.launcher)
                    e.launcher->Release();
            }
            while (++i < m_nExplosions);

            //Release all the cached pointers
            {
                while (--nDmgs >= 0)
                    pdmgs[nDmgs]->Release();
            }

            {
                while (--nMines >= 0)
                    pmines[nMines]->Release();
            }

            m_nExplosions = 0;
        }

        m_lastUpdate = now;
    }
}