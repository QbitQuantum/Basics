//This should only be called from the ChangeCluster() callback.
void CFSPlayer::SetCluster(IclusterIGC* pcluster, bool bViewOnly)
{
  CFSShip::SetCluster(pcluster, bViewOnly);

  if (pcluster)
  {
    SetDPGroup((CFSCluster*)(pcluster->GetPrivateData()), true);

    IshipIGC*   pshipParent = GetIGCShip()->GetParentShip();
    if ((pshipParent == NULL) || bViewOnly)
    {
        ShipID      shipID = GetIGCShip()->GetObjectID();
        assert(0 == g.fm.CbUsedSpaceInOutbox());
        if (!bViewOnly)
        {
            //Move the player to his destination
            BEGIN_PFM_CREATE(g.fm, pfmSetCluster, S, SET_CLUSTER)
            END_PFM_CREATE
            pfmSetCluster->sectorID = pcluster->GetObjectID();

            //Send the position of the parent ship if we are a child, otherwise our position
            IshipIGC*   pshipSource = pshipParent ? pshipParent : GetIGCShip();
            pshipSource->ExportShipUpdate(&(pfmSetCluster->shipupdate));
            pfmSetCluster->cookie = NewCookie();
        }

        {
            for (ShipLinkIGC*   pshiplink = pcluster->GetShips()->first(); pshiplink; pshiplink = pshiplink->next())
            {
                IshipIGC * pshipExist = pshiplink->data();
                if ((pshipExist != GetIGCShip()) && (pshipExist != pshipParent))
                {
                  IshipIGC*   pshipExistParent = pshipExist->GetParentShip();

                  //Tell the new player where the existing ship is/was
                  //provided the existing ship is not the child of some other ship
                  //and is not the parent of the new ship
                  if (pshipExistParent == NULL) 
                  {
                    CFSShip * pfsShipExist = (CFSShip *) pshipExist->GetPrivateData();

                    pfsShipExist->QueueLoadoutChange();

                    BEGIN_PFM_CREATE(g.fm, pfmSSU, S, SINGLE_SHIP_UPDATE)
                    END_PFM_CREATE

                    //Always use the ship update based on the server's current view of the universe
                    //(this shouldn't be a lot worse than anything the player sent and it is easier)
                    pshipExist->ExportShipUpdate(&(pfmSSU->shipupdate));

                    {
                        ImodelIGC*  pmodelTarget = pshipExist->GetCommandTarget(c_cmdCurrent);
                        if (pmodelTarget)
                        {
                            pfmSSU->otTarget = pmodelTarget->GetObjectType();
                            pfmSSU->oidTarget = pmodelTarget->GetObjectID();
                        }
                        else
                        {
                            pfmSSU->otTarget = NA;
                            pfmSSU->oidTarget = NA;
                        }                    
                    }
                    pfmSSU->bIsRipcording = pshipExist->fRipcordActive();
                  }
                }
            }
        }

        {
            // Let's build up a list of station updates so we can batch 'em down
            IsideIGC* pside = GetIGCShip()->GetSide();

            {
                const StationListIGC * pstnlist = pcluster->GetStations();
                int nStations = 0;
                {
                    //Count the number of visible stations
                    for (StationLinkIGC* pstnlink = pstnlist->first(); pstnlink; pstnlink = pstnlink->next())
                    {
                        IstationIGC*  pstation = pstnlink->data();
                        if (pstation->SeenBySide(pside))
                            nStations++;
                    }
                }

                if (nStations != 0)
                {
                    // tell the client what happened
                    BEGIN_PFM_CREATE(g.fm, pfmStationsUpdate, S, STATIONS_UPDATE)
                      FM_VAR_PARM(NULL, nStations * sizeof(StationState))
                    END_PFM_CREATE

                    StationState* pss = (StationState*)(FM_VAR_REF(pfmStationsUpdate, rgStationStates));
                    for (StationLinkIGC* pstnlink = pstnlist->first(); pstnlink; pstnlink = pstnlink->next())
                    {
                        IstationIGC * pstation = pstnlink->data();
                        if (pstation->SeenBySide(pside))
                        {
                            pss->stationID            = pstation->GetObjectID();
                            pss->bpHullFraction       = pstation->GetFraction();
                            (pss++)->bpShieldFraction = pstation->GetShieldFraction();
                        }
                    }
                }
            }

            {
                //Let's build up a list of probe updates and batch them on down (only damage & visible probes)
                const ProbeListIGC * pprblist = pcluster->GetProbes();
                int nProbes = 0;
                {
                    for (ProbeLinkIGC* pprblink = pprblist->first(); pprblink; pprblink = pprblink->next())
                    {
                        if (pprblink->data()->SeenBySide(pside))
                            nProbes++;
                    }
                }

                if (nProbes != 0)
                {
                    BEGIN_PFM_CREATE(g.fm, pfmProbesUpdate, S, PROBES_UPDATE)
                      FM_VAR_PARM(NULL, nProbes * sizeof(ProbeState))
                    END_PFM_CREATE

                    ProbeState* pps = (ProbeState*)(FM_VAR_REF(pfmProbesUpdate, rgProbeStates));
                    for (ProbeLinkIGC* pprblink = pprblist->first(); pprblink; pprblink = pprblink->next())
                    {
                        IprobeIGC * pprobe = pprblink->data();

                        if (pprobe->SeenBySide(pside))
                        {
                            pps->probeID        = pprobe->GetObjectID();
                            (pps++)->bpFraction = pprobe->GetFraction();
                        }
                    }
                }
            }

            {
                //Let's build up a list of asteroid updates and batch them on down
                const AsteroidListIGC * pastlist = pcluster->GetAsteroids();
                int nAsteroids = 0;
                {
                    for (AsteroidLinkIGC* pastlink = pastlist->first(); pastlink; pastlink = pastlink->next())
                    {
                        if (pastlink->data()->SeenBySide(pside))
                            nAsteroids++;
                    }
                }

                if (nAsteroids != 0)
                {
                    BEGIN_PFM_CREATE(g.fm, pfmAsteroidsUpdate, S, ASTEROIDS_UPDATE)
                      FM_VAR_PARM(NULL, nAsteroids * sizeof(AsteroidState))
                    END_PFM_CREATE

                    AsteroidState* pas = (AsteroidState*)(FM_VAR_REF(pfmAsteroidsUpdate, rgAsteroidStates));
                    for (AsteroidLinkIGC* pastlink = pastlist->first(); pastlink; pastlink = pastlink->next())
                    {
                        IasteroidIGC * pasteroid = pastlink->data();

                        if (pasteroid->SeenBySide(pside))
                        {
                            pas->asteroidID         = pasteroid->GetObjectID();
                            pas->ore                = short(pasteroid->GetOre());
                            pas->co.Set(pasteroid->GetOrientation());
                            (pas++)->bpFraction     = pasteroid->GetFraction();
                        }
                    }
                }
            }
        }
    
        //Also send the identical message to all of the ship's children]
		if (!bViewOnly) //TheRock 4-1-2010 fixed ships overlaying in f3 while on a turret
        {
            for (ShipLinkIGC*   psl = GetIGCShip()->GetChildShips()->first(); (psl != NULL); psl = psl->next())
            {
                CFSShip*    pfsShip = (CFSShip*)(psl->data()->GetPrivateData());
                assert (pfsShip->IsPlayer());
                pfsShip->GetPlayer()->ResetLastUpdate();
                g.fm.SendMessages(pfsShip->GetPlayer()->GetConnection(), FM_GUARANTEED, FM_DONT_FLUSH);
            }
        }
        g.fm.SendMessages(GetConnection(), FM_GUARANTEED, FM_FLUSH);
    }
  }
  else if (bViewOnly)
  {
    IstationIGC*    pstation = GetIGCShip()->GetStation();
    assert (pstation);

    CFSCluster*     pfsCluster = (CFSCluster*)(pstation->GetCluster()->GetPrivateData());
    SetDPGroup(pfsCluster, false);
  }
  else
    SetDPGroup(NULL, false);
}