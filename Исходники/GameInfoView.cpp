// doDraw
//---------------------------------------------------------------------------
void GameInfoView::doDraw(const Surface &viewArea, const Surface &clientArea)
{
    char unitsBuf[64];
    char killsBuf[64];
    char lossesBuf[64];
    char fragsBuf[64];
    char timeBuf[64];
    char pingBuf[64];
    char gameBuf[64];
    char fpsBuf[64];

    iXY pos(2, 2);

    // Resize the game info rect to nothing so it can be resized based on the text,
    // to be used in it.
    gameInfoRect = getClientRect();
    //gameInfoRect.max.x = 0;

    sprintf(gameBuf, "game   %s", GameConfig::getGameTypeString() );
    checkGameInfoRect(gameBuf);


    int unitPerPlayer = GameConfig::GetNumberUnits() / GameConfig::GetNumberPlayers();
    sprintf(unitsBuf, "units  %d/%d", int(UnitInterface::getUnitCount(PlayerInterface::getLocalPlayerIndex())), unitPerPlayer);
    checkGameInfoRect(unitsBuf);

    if( GameConfig::GetGameType() == _gametype_fraglimit )
    {
        sprintf(fragsBuf, "frags  %d/%d", getPlayerFrags(), GameConfig::GetFragLimit() );
        checkGameInfoRect(fragsBuf);
    }
    else
    {
        sprintf(fragsBuf, "frags  NA" );
        checkGameInfoRect(fragsBuf);
    }

    /*
    sprintf(killsBuf, "kills  %d", getPlayerKills());
    checkGameInfoRect(killsBuf);

    sprintf(lossesBuf, "losses %d", getPlayerLosses());
    checkGameInfoRect(lossesBuf);
    */

    if( GameConfig::GetGameType() == _gametype_timelimit )
    {
        sprintf(timeBuf, "time   %s/%s", (const char*) getPlayerTime(),
                (const char*) getTimeLimit() );
        checkGameInfoRect(timeBuf);
    }
    else
    {
        sprintf(timeBuf, "time   %s", (const char *) getPlayerTime() );
        checkGameInfoRect(timeBuf);
    }

    sprintf(pingBuf, "ping   %.0f ms", NetworkState::ping_time );
    checkGameInfoRect(pingBuf);

    sprintf(fpsBuf, "FPS    %f", TimerInterface::getFPSAvg() );
    checkGameInfoRect(fpsBuf);

    bltViewBackground(viewArea);

    clientArea.bltStringShadowed(pos, gameBuf, Color::white, Color::black);
    pos.y += 12;
    clientArea.bltStringShadowed(pos, unitsBuf, Color::white, Color::black);
    pos.y += 12;
    clientArea.bltStringShadowed(pos, fragsBuf, Color::white, Color::black);
    pos.y += 12;
    /*
    clientArea.bltStringShadowed(pos, killsBuf, Color::white, Color::black);
    pos.y += 12;
    clientArea.bltStringShadowed(pos, lossesBuf, Color::white, Color::black);
    pos.y += 12;
    */
    clientArea.bltStringShadowed(pos, timeBuf, Color::white, Color::black);
    pos.y += 12;
    clientArea.bltStringShadowed(pos, pingBuf, Color::white, Color::black);
    pos.y += 12;
    clientArea.bltStringShadowed(pos, fpsBuf, Color::white, Color::black);
    pos.y += 12;

    View::doDraw(viewArea, clientArea);

    // Make sure the view stays in the screen when the view is resized.
    //resizeClientArea(gameInfoRect.getSize());
    //moveTo(min);
} // end GameInfoView::doDraw