                bool OnGossipSelectCode(Player* pPlayer, Creature* pCreature, uint32 uiSender, uint32 uiAction, const char * code)
                {
                        pPlayer->PlayerTalkClass->ClearMenus();
                        if ( uiSender == GOSSIP_SENDER_MAIN )
                        {
                                if(islower(code[0]))
                                        toupper(code[0]);
 
                                if(passChecks(pPlayer, code))
                                {
                                        Player * pBounty = sObjectAccessor->FindPlayerByName(code);
                                        switch (uiAction)
                                        {
                                                case GOSSIP_ACTION_INFO_DEF+5:
                                                {
                                                        if(hasCurrency(pPlayer, BOUNTY_PRICE_1, SET_CURRENCY))
                                                        {
                                                                #if SET_CURRENCY != 2
                                                                CharacterDatabase.PExecute("INSERT INTO bounties VALUES('%u','20', '1')", pBounty->GetGUID());
                                                                #else
                                                                CharacterDatabase.PExecute("INSERT INTO bounties VALUES('%u','1', '1')", pBounty->GetGUID());
                                                                #endif
                                                                alertServer(code, 1);
                                                                flagPlayer(code);
                                                               pPlayer->CLOSE_GOSSIP_MENU();
                                                        }
                                                        break;
                                                }
                                                       
                                                case GOSSIP_ACTION_INFO_DEF+6:
                                                {
                                                        if(hasCurrency(pPlayer, BOUNTY_PRICE_2, SET_CURRENCY))
                                                        {
                                                                #if SET_CURRENCY != 2
                                                                CharacterDatabase.PExecute("INSERT INTO bounties VALUES('%u', '40', '2')", pBounty->GetGUID());
                                                                #else
                                                                CharacterDatabase.PExecute("INSERT INTO bounties VALUES('%u', '3', '2')", pBounty->GetGUID());
                                                                #endif
                                                                alertServer(code, 1);
                                                                flagPlayer(code);
                                                                pPlayer->CLOSE_GOSSIP_MENU();
                                                        }
                                                        break;
                                                }
                                                case GOSSIP_ACTION_INFO_DEF+7:
                                                {
                                                        if(hasCurrency(pPlayer, BOUNTY_PRICE_3, SET_CURRENCY))
                                                        {
                                                                #if SET_CURRENCY != 2
                                                                CharacterDatabase.PExecute("INSERT INTO bounties VALUES('%u', '100', '3')", pBounty->GetGUID());
                                                                #else
                                                                CharacterDatabase.PExecute("INSERT INTO bounties VALUES('%u', '5', '3')", pBounty->GetGUID());
                                                                #endif
                                                                alertServer(code, 1);
                                                                flagPlayer(code);
                                                                 pPlayer->CLOSE_GOSSIP_MENU();
                                                        }
                                                        break;
                                                }
                                                case GOSSIP_ACTION_INFO_DEF+8:
                                                {
                                                        if(hasCurrency(pPlayer, BOUNTY_PRICE_4, SET_CURRENCY))
                                                        {
                                                                #if SET_CURRENCY != 2
                                                                CharacterDatabase.PExecute("INSERT INTO bounties VALUES('%u', '200', '4')", pBounty->GetGUID());
                                                                #else
                                                                CharacterDatabase.PExecute("INSERT INTO bounties VALUES('%u', '10', '3')", pBounty->GetGUID());
                                                                #endif
                                                                alertServer(code, 1);
                                                                flagPlayer(code);
                                                                pPlayer->CLOSE_GOSSIP_MENU();
                                                        }
                                                        break;
                                                }
 
                                        }
                                }
                                else
                                {
                                         pPlayer->CLOSE_GOSSIP_MENU();
                                }
                        }
                        return true;
                }