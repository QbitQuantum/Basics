// check if hero has any artifact that gives an ability
bool artifact_gives_ability( t_hero const& hero, t_creature_ability ability )
{
	t_ability_presence_visitor visitor( ability );

	return hero.accept( visitor );
}