void ObjectMgr::LoadExtraItemStuff()
{
	map<uint32, uint32> foodItems;
	QueryResult* result = WorldDatabase.Query("SELECT * FROM itempetfood ORDER BY entry");
	if(result)
	{
		Field* f = result->Fetch();
		do
		{
			foodItems.insert(make_pair(f[0].GetUInt32(), f[1].GetUInt32()));
		}
		while(result->NextRow());
		delete result;
	}

	StorageContainerIterator<ItemPrototype> * itr = ItemPrototypeStorage.MakeIterator();
	ItemPrototype* pItemPrototype;
	while(!itr->AtEnd())
	{
		pItemPrototype = itr->Get();
		if(pItemPrototype->ItemSet > 0)
		{
			ItemSetContentMap::iterator itr2 = mItemSets.find(pItemPrototype->ItemSet);
			std::list<ItemPrototype*>* l;
			if(itr2 == mItemSets.end())
			{
				l = new std::list<ItemPrototype*>;
				mItemSets.insert(ItemSetContentMap::value_type(pItemPrototype->ItemSet, l));
			}
			else
			{
				l = itr2->second;
			}
			l->push_back(pItemPrototype);
		}


		// lowercase name, used for searches
		pItemPrototype->lowercase_name = pItemPrototype->Name1;
		for(uint32 j = 0; j < pItemPrototype->lowercase_name.length(); ++j)
			pItemPrototype->lowercase_name[j] = static_cast<char>(tolower(pItemPrototype->lowercase_name[j]));

		//load item_pet_food_type from extra table
		uint32 ft = 0;
		map<uint32, uint32>::iterator iter = foodItems.find(pItemPrototype->ItemId);
		if(iter != foodItems.end())
			ft = iter->second;
		pItemPrototype->FoodType = ft ;

		// forced pet entries
		switch(pItemPrototype->ItemId)
		{
			case 28071: //Grimoire of Anguish (Rank 1)
			case 28072: //Grimoire of Anguish (Rank 2)
			case 28073: //Grimoire of Anguish (Rank 3)
			case 25469: //Grimoire of Avoidance
			case 23734: //Grimoire of Cleave (Rank 1)
			case 23745: //Grimoire of Cleave (Rank 2)
			case 23755: //Grimoire of Cleave (Rank 3)
			case 25900: //Grimoire of Demonic Frenzy
			case 23711: //Grimoire of Intercept (Rank 1)
			case 23730: //Grimoire of Intercept (Rank 2)
			case 23731: //Grimoire of Intercept (Rank 3)
				// Felguard
				pItemPrototype->ForcedPetId = 17252;
				break;

			case 16321: //Grimoire of Blood Pact (Rank 1)
			case 16322: //Grimoire of Blood Pact (Rank 2)
			case 16323: //Grimoire of Blood Pact (Rank 3)
			case 16324: //Grimoire of Blood Pact (Rank 4)
			case 16325: //Grimoire of Blood Pact (Rank 5)
			case 22180: //Grimoire of Blood Pact (Rank 6)
			case 16326: //Grimoire of Fire Shield (Rank 1)
			case 16327: //Grimoire of Fire Shield (Rank 2)
			case 16328: //Grimoire of Fire Shield (Rank 3)
			case 16329: //Grimoire of Fire Shield (Rank 4)
			case 16330: //Grimoire of Fire Shield (Rank 5)
			case 22181: //Grimoire of Fire Shield (Rank 6)
			case 16302: //Grimoire of Firebolt (Rank 2)
			case 16316: //Grimoire of Firebolt (Rank 3)
			case 16317: //Grimoire of Firebolt (Rank 4)
			case 16318: //Grimoire of Firebolt (Rank 5)
			case 16319: //Grimoire of Firebolt (Rank 6)
			case 16320: //Grimoire of Firebolt (Rank 7)
			case 22179: //Grimoire of Firebolt (Rank 8)
			case 16331: //Grimoire of Phase Shift
				// Imp
				pItemPrototype->ForcedPetId = 416;
				break;

			case 16357: //Grimoire of Consume Shadows (Rank 1)
			case 16358: //Grimoire of Consume Shadows (Rank 2)
			case 16359: //Grimoire of Consume Shadows (Rank 3)
			case 16360: //Grimoire of Consume Shadows (Rank 4)
			case 16361: //Grimoire of Consume Shadows (Rank 5)
			case 16362: //Grimoire of Consume Shadows (Rank 6)
			case 22184: //Grimoire of Consume Shadows (Rank 7)
			case 16351: //Grimoire of Sacrifice (Rank 1)
			case 16352: //Grimoire of Sacrifice (Rank 2)
			case 16353: //Grimoire of Sacrifice (Rank 3)
			case 16354: //Grimoire of Sacrifice (Rank 4)
			case 16355: //Grimoire of Sacrifice (Rank 5)
			case 16356: //Grimoire of Sacrifice (Rank 6)
			case 22185: //Grimoire of Sacrifice (Rank 7)
			case 16363: //Grimoire of Suffering (Rank 1)
			case 16364: //Grimoire of Suffering (Rank 2)
			case 16365: //Grimoire of Suffering (Rank 3)
			case 16366: //Grimoire of Suffering (Rank 4)
			case 22183: //Grimoire of Suffering (Rank 5)
			case 28068: //Grimoire of Suffering (Rank 6)
			case 16346: //Grimoire of Torment (Rank 2)
			case 16347: //Grimoire of Torment (Rank 3)
			case 16348: //Grimoire of Torment (Rank 4)
			case 16349: //Grimoire of Torment (Rank 5)
			case 16350: //Grimoire of Torment (Rank 6)
			case 22182: //Grimoire of Torment (Rank 7)
				// Voidwalker
				pItemPrototype->ForcedPetId = 1860;
				break;

			case 16368: //Grimoire of Lash of Pain (Rank 2)
			case 16371: //Grimoire of Lash of Pain (Rank 3)
			case 16372: //Grimoire of Lash of Pain (Rank 4)
			case 16373: //Grimoire of Lash of Pain (Rank 5)
			case 16374: //Grimoire of Lash of Pain (Rank 6)
			case 22186: //Grimoire of Lash of Pain (Rank 7)
			case 16380: //Grimoire of Lesser Invisibility
			case 16379: //Grimoire of Seduction
			case 16375: //Grimoire of Soothing Kiss (Rank 1)
			case 16376: //Grimoire of Soothing Kiss (Rank 2)
			case 16377: //Grimoire of Soothing Kiss (Rank 3)
			case 16378: //Grimoire of Soothing Kiss (Rank 4)
			case 22187: //Grimoire of Soothing Kiss (Rank 5)
				// Succubus
				pItemPrototype->ForcedPetId = 1863;
				break;

			case 16381: //Grimoire of Devour Magic (Rank 2)
			case 16382: //Grimoire of Devour Magic (Rank 3)
			case 16383: //Grimoire of Devour Magic (Rank 4)
			case 22188: //Grimoire of Devour Magic (Rank 5)
			case 22189: //Grimoire of Devour Magic (Rank 6)
			case 16390: //Grimoire of Paranoia
			case 16388: //Grimoire of Spell Lock (Rank 1)
			case 16389: //Grimoire of Spell Lock (Rank 2)
			case 16384: //Grimoire of Tainted Blood (Rank 1)
			case 16385: //Grimoire of Tainted Blood (Rank 2)
			case 16386: //Grimoire of Tainted Blood (Rank 3)
			case 16387: //Grimoire of Tainted Blood (Rank 4)
			case 22190: //Grimoire of Tainted Blood (Rank 5)
				//Felhunter
				pItemPrototype->ForcedPetId = 417;
				break;

			case 21283:
			case 3144:
			case 21282:
			case 9214:
			case 21281:
			case 22891:
				// Player
				pItemPrototype->ForcedPetId = 0;
				break;

			default:
				pItemPrototype->ForcedPetId = -1;
				break;
		}

		if(!itr->Inc())
			break;
	}

	itr->Destruct();
	foodItems.clear();
}