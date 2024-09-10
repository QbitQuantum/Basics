void LootMgr::PushLoot(StoreLootList *list,Loot * loot, uint8 difficulty, uint8 team, bool disenchant)
{
	uint32 i;
	uint32 count;
	float nrand = 0;
	float ncount = 0;
	assert(difficulty < 4);

	if (disenchant)
	{
		nrand = RandomUInt(10000) / 100.0f;
		ncount = 0;
	}

	for( uint32 x = 0; x < list->count; x++ )
	{
		if( list->items[x].item.itemproto )// this check is needed until loot DB is fixed
		{
			float chance = list->items[x].chance[difficulty];
			if(chance == 0.0f)
				continue;

			ItemPrototype *itemproto = list->items[x].item.itemproto;
			if(!CheckItemFaction(itemproto->Faction, team))
				continue;

			int lucky;
			if (disenchant)
			{
				lucky = nrand >= ncount && nrand <= (ncount+chance);
				ncount+= chance;
			}
			else
				lucky = Rand( chance * sWorld.getRate( RATE_DROP0 + itemproto->Quality ) );

			if( lucky )
			{
				if( list->items[x].mincount == list->items[x].maxcount )
					count = list->items[x].maxcount;
				else
					count = RandomUInt(list->items[x].maxcount - list->items[x].mincount) + list->items[x].mincount;

				for( i = 0; i < loot->items.size(); i++ )
				{
					//itemid rand match a already placed item, if item is stackable and unique(stack), increment it, otherwise skips
					if((loot->items[i].item.itemproto == list->items[x].item.itemproto) && itemproto->MaxCount && ((loot->items[i].StackSize + count) < itemproto->MaxCount))
					{
						if(itemproto->Unique && ((loot->items[i].StackSize+count) < itemproto->Unique))
						{
							loot->items[i].StackSize += count;
							break;
						}
						else if (!itemproto->Unique)
						{
							loot->items[i].StackSize += count;
							break;
						}
					}
				}

				if( i != loot->items.size() )
					continue;

				__LootItem itm;
				itm.item =list->items[x].item;
				itm.StackSize = count;
				itm.roll = NULLROLL;
				itm.passed = false;
				itm.ffa_loot = list->items[x].ffa_loot;
				itm.has_looted.clear();

				if( itemproto->Quality > 1 && itemproto->ContainerSlots == 0 )
				{
					itm.iRandomProperty=GetRandomProperties( itemproto );
					itm.iRandomSuffix=GetRandomSuffix( itemproto );
				}
				else
				{
					// save some calls :P
					itm.iRandomProperty = NULL;
					itm.iRandomSuffix = NULL;
				}

				loot->items.push_back(itm);
			}
		}
	}

	if( loot->items.size() > 16 )
	{
		std::vector<__LootItem>::iterator item_to_remove;
		std::vector<__LootItem>::iterator itr;
		uint32 item_quality;
		bool quest_item;
		while( loot->items.size() > 16 )
		{
			item_to_remove = loot->items.begin();
			item_quality = 0;
			quest_item = false;
			for( itr = loot->items.begin(); itr != loot->items.end(); itr++ )
			{
				item_quality = (*itr).item.itemproto->Quality;
				quest_item = (*itr).item.itemproto->Class == ITEM_CLASS_QUEST;
				if( (*item_to_remove).item.itemproto->Quality > item_quality && !quest_item )
				{
					item_to_remove = itr;
				}
			}
			loot->items.erase( item_to_remove );
		}
	}

}