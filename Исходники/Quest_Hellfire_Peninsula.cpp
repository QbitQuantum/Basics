        void OnActivate(Player* pPlayer)
        {
            QuestLogEntry* pQuest = pPlayer->GetQuestLogForEntry(10895);
            if(pQuest != NULL)
            {
                // M4ksiu - WTF IS THIS FOR? :|
                float SSX = pPlayer->GetPositionX();
                float SSY = pPlayer->GetPositionY();
                float SSZ = pPlayer->GetPositionZ();

                GameObject* pBeacon = pPlayer->GetMapMgr()->GetInterface()->GetGameObjectNearestCoords(SSX, SSY, SSZ, 184661);
                if(pBeacon != NULL && pBeacon->GetFlags() > 0)
                {
                    pBeacon->SetFlags((pBeacon->GetFlags() - 1));
                }

                // Northern Zeth'Gor Tower
                if(pQuest->GetMobCount(0) < pQuest->GetQuest()->required_mobcount[0])
                {
                    GameObject* pNorthern = pPlayer->GetMapMgr()->GetInterface()->GetGameObjectNearestCoords(-820.0f, 2029.0f, 55.0f, 300150);
                    if(pNorthern != NULL && pPlayer->CalcDistance(pPlayer, pNorthern) < 40)      // if reduced the server will crash when out of range
                    {
                        pQuest->SetMobCount(0, pQuest->GetMobCount(0) + 1);
                        pQuest->SendUpdateAddKill(0);
                        pQuest->UpdatePlayerFields();

                        GameObject* pGameobject = sEAS.SpawnGameobject(pPlayer, 183816, -819.77f, 2029.09f, 55.6082f, 0, 4, 0, 0, 0, 0);
                        if(pGameobject != NULL)
                        {
                            sEAS.GameobjectDelete(pGameobject, 1 * 60 * 1000);
                        }

                        return;
                    }
                }

                // Southern Zeth'Gor Tower
                if(pQuest->GetMobCount(1) < pQuest->GetQuest()->required_mobcount[1])
                {
                    GameObject* pSouthern = pPlayer->GetMapMgr()->GetInterface()->GetGameObjectNearestCoords(-1150.0f, 2110.0f, 84.0f, 300150);
                    if(pSouthern != NULL && pPlayer->CalcDistance(pPlayer, pSouthern) < 40)
                    {
                        pQuest->SetMobCount(1, pQuest->GetMobCount(1) + 1);
                        pQuest->SendUpdateAddKill(1);
                        pQuest->UpdatePlayerFields();

                        GameObject* pGameobject = sEAS.SpawnGameobject(pPlayer, 183816, -1150.53f, 2109.92f, 84.4204f, 0, 4, 0, 0, 0, 0);
                        if(pGameobject != NULL)
                        {
                            sEAS.GameobjectDelete(pGameobject, 1 * 60 * 1000);
                        }

                        return;
                    }
                }

                // Forge Zeth'Gor Tower
                if(pQuest->GetMobCount(2) < pQuest->GetQuest()->required_mobcount[2])
                {
                    GameObject* pForge = pPlayer->GetMapMgr()->GetInterface()->GetGameObjectNearestCoords(-893.0f, 1919.0f, 82.0f, 300150);
                    if(pForge != NULL && pPlayer->CalcDistance(pPlayer, pForge) < 40)
                    {
                        pQuest->SetMobCount(2, pQuest->GetMobCount(2) + 1);
                        pQuest->SendUpdateAddKill(2);
                        pQuest->UpdatePlayerFields();

                        GameObject* pGameobject = sEAS.SpawnGameobject(pPlayer, 183816, -893.499f, 1919.27f, 81.6449f, 0, 4, 0, 0, 0, 0);
                        if(pGameobject != NULL)
                        {
                            sEAS.GameobjectDelete(pGameobject, 1 * 60 * 1000);
                        }

                        return;
                    }
                }

                // Foothill Zeth'Gor Tower
                if(pQuest->GetMobCount(3) < pQuest->GetQuest()->required_mobcount[3])
                {
                    GameObject* pFoothill = pPlayer->GetMapMgr()->GetInterface()->GetGameObjectNearestCoords(-978.0f, 1879.0f, 111.0f, 300150);
                    if(pFoothill != NULL && pPlayer->CalcDistance(pPlayer, pFoothill) < 40)
                    {
                        pQuest->SetMobCount(3, pQuest->GetMobCount(3) + 1);
                        pQuest->SendUpdateAddKill(3);
                        pQuest->UpdatePlayerFields();

                        GameObject* pGameobject = sEAS.SpawnGameobject(pPlayer, 183816, -977.713f, 1879.500f, 110.892f, 0, 4, 0, 0, 0, 0);
                        if(pGameobject != NULL)
                        {
                            sEAS.GameobjectDelete(pGameobject, 1 * 60 * 1000);
                        }

                        return;
                    }
                }
                else
                {
                    pPlayer->BroadcastMessage("You are to far away!");
                }

            }
            else
            {
                pPlayer->BroadcastMessage("Missing required quest : Zeth'Gor Must Burn");
            }
        }