void gra::robaczki()
{
    string outbuf;
    LPWORD buferkoloru;
    buferkoloru = new WORD[outbuf.length()];
    COORD cWhere;
    HANDLE hConsoleOut = GetStdHandle(STD_OUTPUT_HANDLE);
    DWORD dwCharsWritten;
    int opoznienie = 300;
    while(true)
    {
        if (wygrana == true || zgnieciony == true || koniec_czasu == true || escape == true || ukaszony == true)
            break;
        for (int i = 0; i < 22; i++)
        {
            for (int j = 0; j < 40; j++)
            {
                if (MAPA[i][j].zw_typ() == "robak")
                {
                    robak r;
                    r.zmien_wsp(i, j);
                    if (MAPA[i][j].zw_ruch() == true)
                        r.ustaw_ruch(true);
                    ROBAKI.push_back(r);
                }
            }
        }
        for (unsigned i = 0; i < ROBAKI.size(); i++)
        {
            cWhere.X = ROBAKI[i].zw_y();
            cWhere.Y = ROBAKI[i].zw_x();
            outbuf = static_cast<char>(95);
            memset(buferkoloru, (CZARNY << 4) + CZARNY, 1);
            WriteConsoleOutputCharacter(hConsoleOut, outbuf.c_str(), outbuf.length(), cWhere, &dwCharsWritten);
            WriteConsoleOutputAttribute(hConsoleOut, buferkoloru, outbuf.length(), cWhere, &dwCharsWritten);
            ROBAKI[i].ink_wsp_y();
            cWhere.X = ROBAKI[i].zw_y();
            cWhere.Y = ROBAKI[i].zw_x();
            outbuf = static_cast<char>(64);
            memset(buferkoloru, (CIEMNOCZERWONY << 4) + ROZOWY, 1);
            WriteConsoleOutputCharacter(hConsoleOut, outbuf.c_str(), outbuf.length(), cWhere, &dwCharsWritten);
            WriteConsoleOutputAttribute(hConsoleOut, buferkoloru, outbuf.length(), cWhere, &dwCharsWritten);
            MAPA[ROBAKI[i].zw_x()][ROBAKI[i].zw_y()] = ROBAKI[i];
            kurz K;
            MAPA[ROBAKI[i].zw_x()][ROBAKI[i].zw_y() - 1] = K;
            if (MAPA[ROBAKI[i].zw_x() + 1][ROBAKI[i].zw_y()].zw_typ() == "gracz")
            {
                ukaszony = true;
                break;
            }
            if (wygrana == true || zgnieciony == true || koniec_czasu == true || escape == true)
                break;
        }
            Sleep(opoznienie);
        for (unsigned i = 0; i < ROBAKI.size(); i++)
        {
            cWhere.X = ROBAKI[i].zw_y();
            cWhere.Y = ROBAKI[i].zw_x();
            outbuf = static_cast<char>(95);
            memset(buferkoloru, (CZARNY << 4) + CZARNY, 1);
            WriteConsoleOutputCharacter(hConsoleOut, outbuf.c_str(), outbuf.length(), cWhere, &dwCharsWritten);
            WriteConsoleOutputAttribute(hConsoleOut, buferkoloru, outbuf.length(), cWhere, &dwCharsWritten);
            ROBAKI[i].ink_wsp_x();
            cWhere.X = ROBAKI[i].zw_y();
            cWhere.Y = ROBAKI[i].zw_x();
            outbuf = static_cast<char>(64);
            memset(buferkoloru, (CIEMNOCZERWONY << 4) + ROZOWY, 1);
            WriteConsoleOutputCharacter(hConsoleOut, outbuf.c_str(), outbuf.length(), cWhere, &dwCharsWritten);
            WriteConsoleOutputAttribute(hConsoleOut, buferkoloru, outbuf.length(), cWhere, &dwCharsWritten);
            MAPA[ROBAKI[i].zw_x()][ROBAKI[i].zw_y()] = ROBAKI[i];
            kurz K;
            MAPA[ROBAKI[i].zw_x() - 1][ROBAKI[i].zw_y()] = K;
            if (MAPA[ROBAKI[i].zw_x()][ROBAKI[i].zw_y() - 1].zw_typ() == "gracz")
            {
                ukaszony = true;
                break;
            }
            if (wygrana == true || zgnieciony == true || koniec_czasu == true || escape == true)
                break;
        }
            Sleep(opoznienie);
        for (unsigned i = 0; i < ROBAKI.size(); i++)
        {
            cWhere.X = ROBAKI[i].zw_y();
            cWhere.Y = ROBAKI[i].zw_x();
            outbuf = static_cast<char>(95);
            memset(buferkoloru, (CZARNY << 4) + CZARNY, 1);
            WriteConsoleOutputCharacter(hConsoleOut, outbuf.c_str(), outbuf.length(), cWhere, &dwCharsWritten);
            WriteConsoleOutputAttribute(hConsoleOut, buferkoloru, outbuf.length(), cWhere, &dwCharsWritten);
            ROBAKI[i].dek_wsp_y();
            cWhere.X = ROBAKI[i].zw_y();
            cWhere.Y = ROBAKI[i].zw_x();
            outbuf = static_cast<char>(64);
            memset(buferkoloru, (CIEMNOCZERWONY << 4) + ROZOWY, 1);
            WriteConsoleOutputCharacter(hConsoleOut, outbuf.c_str(), outbuf.length(), cWhere, &dwCharsWritten);
            WriteConsoleOutputAttribute(hConsoleOut, buferkoloru, outbuf.length(), cWhere, &dwCharsWritten);
            MAPA[ROBAKI[i].zw_x()][ROBAKI[i].zw_y()] = ROBAKI[i];
            kurz K;
            MAPA[ROBAKI[i].zw_x()][ROBAKI[i].zw_y() + 1] = K;
            if (MAPA[ROBAKI[i].zw_x() - 1][ROBAKI[i].zw_y()].zw_typ() == "gracz")
            {
                ukaszony = true;
                break;
            }
            if (wygrana == true || zgnieciony == true || koniec_czasu == true || escape == true)
                break;
        }
            Sleep(opoznienie);
        for (unsigned i = 0; i < ROBAKI.size(); i++)
        {
            cWhere.X = ROBAKI[i].zw_y();
            cWhere.Y = ROBAKI[i].zw_x();
            outbuf = static_cast<char>(95);
            memset(buferkoloru, (CZARNY << 4) + CZARNY, 1);
            WriteConsoleOutputCharacter(hConsoleOut, outbuf.c_str(), outbuf.length(), cWhere, &dwCharsWritten);
            WriteConsoleOutputAttribute(hConsoleOut, buferkoloru, outbuf.length(), cWhere, &dwCharsWritten);
            ROBAKI[i].dek_wsp_x();
            cWhere.X = ROBAKI[i].zw_y();
            cWhere.Y = ROBAKI[i].zw_x();
            outbuf = static_cast<char>(64);
            memset(buferkoloru, (CIEMNOCZERWONY << 4) + ROZOWY, 1);
            WriteConsoleOutputCharacter(hConsoleOut, outbuf.c_str(), outbuf.length(), cWhere, &dwCharsWritten);
            WriteConsoleOutputAttribute(hConsoleOut, buferkoloru, outbuf.length(), cWhere, &dwCharsWritten);
            MAPA[ROBAKI[i].zw_x()][ROBAKI[i].zw_y()] = ROBAKI[i];
            kurz K;
            MAPA[ROBAKI[i].zw_x() + 1][ROBAKI[i].zw_y()] = K;
            if (MAPA[ROBAKI[i].zw_x()][ROBAKI[i].zw_y() + 1].zw_typ() == "gracz")
            {
                ukaszony = true;
                break;
            }
            if (wygrana == true || zgnieciony == true || koniec_czasu == true || escape == true)
                break;
        }
            Sleep(opoznienie);
    }
    ROBAKI.clear();
}