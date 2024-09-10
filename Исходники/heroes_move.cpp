void Heroes::MoveStep(Heroes & hero, s32 index_from, s32 index_to, bool newpos)
{
    if(newpos)
    {
	hero.Move2Dest(index_to);
	hero.GetPath().PopFront();

	// possible hero is die
	if(!hero.isFreeman() &&
	    index_to == hero.GetPath().GetDestinationIndex())
	{
	    hero.GetPath().Reset();
	    hero.Action(index_to);
	    hero.SetMove(false);
	}
    }
    else
    {
	hero.ApplyPenaltyMovement();
	hero.GetPath().Reset();
	hero.Action(index_to);
	hero.SetMove(false);
    }
}