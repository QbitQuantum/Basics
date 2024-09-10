// Only override the ones you need; the default action is to return false.
bool MapDetailPanel::KeyDown(SDL_Keycode key, Uint16 mod, const Command &command)
{
	if(command.Has(Command::MAP) || key == 'd' || key == SDLK_ESCAPE || (key == 'w' && (mod & (KMOD_CTRL | KMOD_GUI))))
		GetUI()->Pop(this);
	else if(key == SDLK_PAGEUP || key == SDLK_PAGEDOWN || key == 'i')
	{
		GetUI()->Pop(this);
		GetUI()->Push(new MissionPanel(*this));
	}
	else if(key == 'o')
	{
		GetUI()->Pop(this);
		GetUI()->Push(new MapOutfitterPanel(*this));
	}
	else if(key == 's')
	{
		GetUI()->Pop(this);
		GetUI()->Push(new MapShipyardPanel(*this));
	}
	else if((key == SDLK_TAB || command.Has(Command::JUMP)) && player.Flagship())
	{
		// Toggle to the next link connected to the "source" system. If the
		// shift key is down, the source is the end of the travel plan; otherwise
		// it is one step before the end.
		vector<const System *> &plan = player.TravelPlan();
		const System *source = plan.empty() ? player.GetSystem() : plan.front();
		const System *next = nullptr;
		Point previousUnit = Point(0., -1.);
		if(!plan.empty() && !(mod & KMOD_SHIFT))
		{
			previousUnit = plan.front()->Position();
			plan.erase(plan.begin());
			next = source;
			source = plan.empty() ? player.GetSystem() : plan.front();
			previousUnit = (previousUnit - source->Position()).Unit();
		}
		Point here = source->Position();
		
		// Depending on whether the flagship has a jump drive, the possible links
		// we can travel along are different:
		bool hasJumpDrive = player.Flagship()->Attributes().Get("jump drive");
		const vector<const System *> &links = hasJumpDrive ? source->Neighbors() : source->Links();
		
		double bestAngle = 2. * PI;
		for(const System *it : links)
		{
			if(!player.HasSeen(it))
				continue;
			if(!(hasJumpDrive || player.HasVisited(it) || player.HasVisited(source)))
				continue;
			
			Point unit = (it->Position() - here).Unit();
			double angle = acos(unit.Dot(previousUnit));
			if(unit.Cross(previousUnit) >= 0.)
				angle = 2. * PI - angle;
			
			if(angle <= bestAngle)
			{
				next = it;
				bestAngle = angle;
			}
		}
		if(next)
		{
			plan.insert(plan.begin(), next);
			Select(next);
		}
	}
	else if((key == SDLK_DELETE || key == SDLK_BACKSPACE) && player.HasTravelPlan())
	{
		vector<const System *> &plan = player.TravelPlan();
		plan.erase(plan.begin());
		Select(plan.empty() ? player.GetSystem() : plan.front());
	}
	else if(key == SDLK_DOWN)
	{
		if(commodity < 0 || commodity == 9)
			commodity = 0;
		else
			++commodity;
	}
	else if(key == SDLK_UP)
	{
		if(commodity <= 0)
			commodity = 9;
		else
			--commodity;
	}
	else if(key == 'f')
		GetUI()->Push(new Dialog(
			this, &MapDetailPanel::DoFind, "Search for:"));
	else if(key == '+' || key == '=')
		ZoomMap();
	else if(key == '-')
		UnzoomMap();
	else
		return false;
	
	return true;
}