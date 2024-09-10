	void DonationMenu(Player *player, Creature *_Creature, uint32 action, uint32 sender)
	{
		int32 playerid = player->GetGUID();
		int32 accountid = player->GetSession()->GetAccountId();
		if(action == 6000)
		{
			createmenu(accountid,_Creature,player);
		
		}else{
			QueryResult pResult = WorldDatabase.PQuery("SELECT sc.store_cartID,player,date,store_templateID,scg.status,(SELECT type FROM `store`.store_template as temp WHERE temp.store_templateID=sc.store_templateID) FROM `store`.store_cart_give as scg INNER JOIN `store`.store_cart as sc ON scg.store_cartID=sc.store_cartID WHERE scg.accountid='%u' AND scg.store_cart_giveID = '%u';", accountid, action);
			// cart give
				// Status
				//	0 = Not chosen
				//  1 Chosen
				//  2 = confirm
				//  3 = Completed
			if(pResult)
			{
				//do{
				Field* pFields = pResult->Fetch();
				
				//ints
				int32 db_id 			= pFields[0].GetInt32();
				int32 db_player 			= pFields[1].GetInt32();
				int32 db_date 			= pFields[2].GetInt32();
				int32 db_template 			= pFields[3].GetInt32(); 
				int32 db_status 			= pFields[4].GetInt32(); 
				int32 db_type			= pFields[5].GetInt32(); 

				
				//strings
				std::string itemname;
				itemname = pFields[1].GetString();
				
				if(db_player || db_date || db_status == 3)
				{
					//message
					_Creature->MonsterWhisper("This reward is already been recieved!", player->GetGUID());
					player->CLOSE_GOSSIP_MENU();
					return;
				}
				if(db_status == 1) // if we are here with this value means they didn't confirm it
				{
					WorldDatabase.PExecute("UPDATE `store`.store_cart_give SET status = 0,itemset = 0 WHERE store_cart_giveID = '%u'", action); // reset
					db_status = 0;
				}
				//normal reward go striaght to confirm status
				if(db_type < 16)
				{	
					db_status = 2;
				}
				
				// Let the user select itemset they want
				if(db_type >= 16 && db_status == 0 && !sender)
					itemsetgroup(_Creature, player,db_template,action);
				else 				
				{
					//if group itemset update cart
					if(db_type >= 16 && sender && db_status < 2)
					{
						int32 playerid = player->GetGUID();
						WorldDatabase.PExecute("UPDATE `store`.store_cart_give SET status = 2, itemset = '%u' WHERE store_cart_giveID = '%u'", sender,action); 
						db_status = 2;
						sender = 0;
					}
					//confirm choice
					if(db_status == 2 && sender == 0)
					{
						//menu
						player->PlayerTalkClass->ClearMenus();
						player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, "Are you sure?" , 0, 6000);
						player->ADD_GOSSIP_ITEM(1, "Yes" , 1, action);
						player->ADD_GOSSIP_ITEM(1, "No" , 0, 6000);
						player->SEND_GOSSIP_MENU(DEFAULT_GOSSIP_MESSAGE,_Creature->GetGUID());
					}else{
						if(check(db_template,_Creature, player,action))
						{
							giving_proccess(_Creature, player,db_template,action);
							record_donation(_Creature, player, action);
						}else{
							_Creature->MonsterWhisper("Failed!", player->GetGUID());
							player->CLOSE_GOSSIP_MENU();
						}
					}
				}
			}else{
			
				_Creature->MonsterWhisper("Nothing here", player->GetGUID());
				player->CLOSE_GOSSIP_MENU();
			}
		
		}
		
	}