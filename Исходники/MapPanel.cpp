bool MapPanel::Click(int x, int y)
{
	// Figure out if a system was clicked on.
	Point click = Point(x, y) - center;
	for(const auto &it : GameData::Systems())
		if(click.Distance(it.second.Position()) < 10.
				&& (player.HasSeen(&it.second) || &it.second == specialSystem))
		{
			Select(&it.second);
			break;
		}
	
	return true;
}