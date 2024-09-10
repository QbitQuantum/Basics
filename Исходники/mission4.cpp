//------------------------------------------------------------------------------
void        Mission4::CreateUniverse (void)
{
    LoadUniverse ("training_3", 486, 1030);    // an advanced stealth fighter

    // stuff for setup
    IshipIGC*           pShip = trekClient.GetShip();

    // set a global attribute to increase the overall energy of the ship
    IsideIGC*           pSide = pShip->GetSide ();
    GlobalAttributeSet  gas = pSide->GetGlobalAttributeSet ();
    gas.SetAttribute (c_gaMaxEnergy, 10.0f);
    pSide->SetGlobalAttributeSet (gas);

    // put the commander ship in the station
    ImissionIGC*        pCore = trekClient.GetCore();
    ImodelIGC*          pStation = pCore->GetModel (OT_station, 1030);
    IshipIGC*           pCommander = pCore->GetShip (m_commanderID);
    pCommander->SetStation (static_cast<IstationIGC*> (pStation));
    pCommander->SetCommand (c_cmdAccepted, NULL, c_cidDoNothing);
    pCommander->SetCommand (c_cmdCurrent, NULL, c_cidDoNothing);
    pCommander->SetAutopilot (false);

    // activate all the starting weapons
    trekClient.fGroupFire = true;

    // take the missiles off the ship
    IpartIGC*           pPart = pShip->GetMountedPart (ET_Magazine, 0);
    if (pPart)
        pPart->Terminate ();

}