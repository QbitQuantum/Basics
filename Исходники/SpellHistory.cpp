void SpellHistory::ModifyCooldown(uint32 spellId, Clock::duration offset)
{
    auto itr = _spellCooldowns.find(spellId);
    if (!offset.count() || itr == _spellCooldowns.end())
        return;

    Clock::time_point now = Clock::now();

    if (itr->second.CooldownEnd + offset > now)
        itr->second.CooldownEnd += offset;
    else
        EraseCooldown(itr);

    if (Player* playerOwner = GetPlayerOwner())
    {
        WorldPackets::Spells::ModifyCooldown modifyCooldown;
        modifyCooldown.IsPet = _owner != playerOwner;
        modifyCooldown.SpellID = spellId;
        modifyCooldown.DeltaTime = std::chrono::duration_cast<std::chrono::milliseconds>(offset).count();
        playerOwner->SendDirectMessage(modifyCooldown.Write());
    }
}