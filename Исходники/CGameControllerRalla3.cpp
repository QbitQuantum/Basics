void CGameControllerRalla3::DrawHUD()
{
    if (m_PlayerWin == PLAYER_NULL)
    {
        if (m_ActivePlayer == PLAYER_1)
        {
            circle(mousex(), mousey(), 10);
            outtextxy(g_Game.GetScreenW()/2-textwidth("TURNO: JUGADOR 1")/2, dimTY+60, "TURNO: JUGADOR 1");
        }
        else
        {
            moveto(mousex()-10, mousey()-10);
            lineto(mousex()+10, mousey()+10);
            moveto(mousex()+10, mousey()-10);
            lineto(mousex()-10, mousey()+10);

            if (m_CPU)
                outtextxy(g_Game.GetScreenW()/2-textwidth("TURNO: CPU")/2, dimTY+120, "TURNO: CPU");
            else
                outtextxy(g_Game.GetScreenW()/2-textwidth("TURNO: JUGADOR 2")/2, dimTY+60, "TURNO: JUGADOR 2");
        }
    }
    else
    {
        const char *sBuff;
        if (m_PlayerWin == PLAYER_1)
            sBuff = "Gana el JUGADOR 1";
        else if (m_PlayerWin == PLAYER_2)
            sBuff = "Gana el JUGADOR 2";
        else if (m_PlayerWin == PLAYER_CPU)
            sBuff = "Gana la CPU";
        else
            sBuff = "EMPATE!";

        int xt = g_Game.GetScreenW()/2 - textwidth(sBuff)/2;
        int yt = g_Game.GetScreenH()/2 - textheight(sBuff)/2;

        outtextxy(xt, yt, sBuff);

        xt = g_Game.GetScreenW()/2 - textwidth("pulsa INTRO para reiniciar")/2;
        yt = g_Game.GetScreenH()/2 - textheight("pulsa INTRO para reiniciar")/2;
        yt += textheight(sBuff) + 15;
        outtextxy(xt, yt, "pulsa INTRO para reiniciar");
        rectangle(-1, yt-2, g_Game.GetScreenW()+1, yt-1 + textheight("pulsa INTRO para reiniciar") + 2);
    }
}