bool ActionSpellDimensionDoor(Heroes & hero)
{
    const u8 distance = Spell::CalculateDimensionDoorDistance(hero.GetPower(), hero.GetArmy().GetHitPoints());

    Interface::Basic & I = Interface::Basic::Get();
    Cursor & cursor = Cursor::Get();

    // center hero
    cursor.Hide();
    I.gameArea.SetCenter(hero.GetCenter());
    GameFocus::SetRedraw();
    I.Redraw();

    const s32 src = hero.GetIndex();
    // get destination
    const s32 dst = I.GetDimensionDoorDestination(src, distance, hero.isShipMaster());

    if(Maps::isValidAbsIndex(src) && Maps::isValidAbsIndex(dst))
    {
        AGG::PlaySound(M82::KILLFADE);
        hero.GetPath().Reset();
        hero.FadeOut();

        hero.SpellCasted(Spell::DIMENSIONDOOR);

        cursor.Hide();
        hero.Move2Dest(dst, true);

        I.gameArea.SetCenter(hero.GetCenter());
        GameFocus::SetRedraw();
        I.Redraw();

        AGG::PlaySound(M82::KILLFADE);
        hero.FadeIn();

        hero.ActionNewPosition();

        return false; /* SpellCasted apply */
    }

    return false;
}