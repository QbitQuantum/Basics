bool MissionPanel::Click(int x, int y)
{
	dragSide = 0;
	
	// Handle clicks on the interface buttons.
	{
		const Interface *interface = GameData::Interfaces().Get("mission");
		char key = interface->OnClick(Point(x, y));
		if(key)
			return DoKey(key);
	}
	{
		const Interface *interface = GameData::Interfaces().Get("map buttons");
		char key = interface->OnClick(Point(x, y));
		if(key)
			return DoKey(key);
	}
	
	if(x > Screen::Right() - 80 && y > Screen::Bottom() - 50)
		return DoKey('p');
	
	if(x < Screen::Left() + SIDE_WIDTH)
	{
		unsigned index = max(0, (y + static_cast<int>(availableScroll) - 36 - Screen::Top()) / 20);
		if(index < available.size())
		{
			availableIt = available.begin();
			while(index--)
				++availableIt;
			acceptedIt = accepted.end();
			dragSide = -1;
			selectedSystem = availableIt->Destination()->GetSystem();
			center = Point(0., -80.) - selectedSystem->Position();
			return true;
		}
	}
	else if(x >= Screen::Right() - SIDE_WIDTH)
	{
		int index = max(0, (y + static_cast<int>(acceptedScroll) - 36 - Screen::Top()) / 20);
		if(index < AcceptedVisible())
		{
			acceptedIt = accepted.begin();
			while(index || !acceptedIt->IsVisible())
			{
				index -= acceptedIt->IsVisible();
				++acceptedIt;
			}
			availableIt = available.end();
			dragSide = 1;
			selectedSystem = acceptedIt->Destination()->GetSystem();
			center = Point(0., -80.) - selectedSystem->Position();
			return true;
		}
	}
	
	// Figure out if a system was clicked on.
	Point click = Point(x, y) / Zoom() - center;
	const System *system = nullptr;
	for(const auto &it : GameData::Systems())
		if(click.Distance(it.second.Position()) < 10.
				&& (player.HasSeen(&it.second) || &it.second == specialSystem))
		{
			system = &it.second;
			break;
		}
	if(system)
	{
		Select(system);
		int options = available.size() + accepted.size();
		// If you just aborted your last mission, it is possible that neither
		// iterator is valid. In that case, start over from the beginning.
		if(availableIt == available.end() && acceptedIt == accepted.end())
		{
			if(!available.empty())
				availableIt = available.begin();
			else
				acceptedIt = accepted.begin();
		}
		while(options--)
		{
			if(availableIt != available.end())
			{
				++availableIt;
				if(availableIt == available.end())
				{
					if(!accepted.empty())
						acceptedIt = accepted.begin();
					else
						availableIt = available.begin();
				}
			}
			else if(acceptedIt != accepted.end())
			{
				++acceptedIt;
				if(acceptedIt == accepted.end())
				{
					if(!available.empty())
						availableIt = available.begin();
					else
						acceptedIt = accepted.begin();
				}
			}
			if(acceptedIt != accepted.end() && !acceptedIt->IsVisible())
				continue;
			
			if(availableIt != available.end() && availableIt->Destination()->GetSystem() == system)
				break;
			if(acceptedIt != accepted.end() && acceptedIt->Destination()->GetSystem() == system)
				break;
		}
	}
	
	return true;
}