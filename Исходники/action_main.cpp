void StageDraw()
{
    DrawMap(map, 0);
    DrawEnemy(map);
    DrawItem(map);
    DrawBomb(map);
    DrawEffect(map);
    DrawPlayer(map);
    
#if !MAP_EDIT_MODE
    DrawTextureObject(res.player_right, 0, 0);
    FontPrintf(32, 16, "x %d", life);
    
    DrawTextureObject(res.font_stage, 128, 16);
    FontPrintf(128 + 16 * 5, 16, "%d", stageNum + 1);

    DrawTextureObject(res.font_score, 128 + 16 * 5 + 32, 16);
    FontPrintf(128 + 16 * 5 + 32 + 16 * 5 + 16 , 16, "%d", score);
    PrintWindow("fps: %d", engineFps);
#endif    
}