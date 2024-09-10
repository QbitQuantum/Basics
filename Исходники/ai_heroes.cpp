void AIHeroesAddedTask(Heroes & hero)
{
    AIHero & ai_hero = AIHeroes::Get(hero);
    AIKingdom & ai_kingdom = AIKingdoms::Get(hero.GetColor());

    Queue & task = ai_hero.sheduled_visit;
    IndexObjectMap & ai_objects = ai_kingdom.scans;

    // load minimal distance tasks
    std::vector<IndexDistance> objs;
    objs.reserve(ai_objects.size());

    for(std::map<s32, int>::const_iterator
	it = ai_objects.begin(); it != ai_objects.end(); ++it)
    {
	const Maps::Tiles & tile = world.GetTiles((*it).first);

	if(hero.isShipMaster())
	{
	    if(MP2::OBJ_COAST != tile.GetObject() &&
		! tile.isWater()) continue;

	    // check previous positions
	    if(MP2::OBJ_COAST == (*it).second &&
		hero.isVisited(world.GetTiles((*it).first))) continue;
	}
	else
	{
	    if(tile.isWater() && MP2::OBJ_BOAT != tile.GetObject()) continue;
	}

	objs.push_back(IndexDistance((*it).first,
			    Maps::GetApproximateDistance(hero.GetIndex(), (*it).first)));
    }

    DEBUG(DBG_AI, DBG_INFO, Color::String(hero.GetColor()) <<
		    ", hero: " << hero.GetName() << ", task prepare: " << objs.size());

    std::sort(objs.begin(), objs.end(), IndexDistance::Shortest);

    for(std::vector<IndexDistance>::const_iterator
	it = objs.begin(); it != objs.end(); ++it)
    {
	if(task.size() >= HERO_MAX_SHEDULED_TASK) break;
	const bool validobj = AI::HeroesValidObject(hero, (*it).first);

	if(validobj &&
	    hero.GetPath().Calculate((*it).first))
	{
	    DEBUG(DBG_AI, DBG_INFO, Color::String(hero.GetColor()) <<
		    ", hero: " << hero.GetName() << ", added tasks: " <<
		    MP2::StringObject(ai_objects[(*it).first]) << ", index: " << (*it).first <<
		    ", distance: " << (*it).second);

	    task.push_back((*it).first);
	    ai_objects.erase((*it).first);
	}
	else
	{
	    DEBUG(DBG_AI, DBG_TRACE, Color::String(hero.GetColor()) <<
		    ", hero: " << hero.GetName() << (!validobj ? ", invalid: " : ", impossible: ") <<
		    MP2::StringObject(ai_objects[(*it).first]) << ", index: " << (*it).first <<
		    ", distance: " << (*it).second);
	}
    }

    if(task.empty())
	AIHeroesAddedRescueTask(hero);
}