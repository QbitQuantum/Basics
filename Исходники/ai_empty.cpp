bool AI::HeroesGetTask(Heroes & hero)
{
    // stop hero
    hero.GetPath().Reset();
    return false;
}