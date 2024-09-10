void Interface::Basic::EventSwitchHeroSleeping(void)
{
    Heroes* hero = GetFocusHeroes();

    if(hero)
    {
	if(hero->Modes(Heroes::SLEEPER))
	    hero->ResetModes(Heroes::SLEEPER);
	else
	{
	    hero->SetModes(Heroes::SLEEPER);
	    hero->GetPath().Reset();
	}

	SetRedraw(REDRAW_HEROES);
    }
}