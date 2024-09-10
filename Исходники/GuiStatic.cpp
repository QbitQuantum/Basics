void GuiAvatar::Render()
{
    JRenderer * r = JRenderer::GetInstance();
    int life = player->life;
    int poisonCount = player->poisonCount;
    WFont * mFont = WResourceManager::Instance()->GetWFont(Fonts::MAIN_FONT);
    mFont->SetScale(DEFAULT_MAIN_FONT_SCALE);
    //Avatar
    int lifeDiff = life - currentLife;
    if (lifeDiff < 0 && currentLife > 0)
    {
        avatarRed = 192 + (3 * 255 * lifeDiff) / currentLife / 4;
        if (avatarRed < 0)
            avatarRed = 0;
    }
    int poisonDiff = poisonCount - currentpoisonCount;
    if (poisonDiff < 0 && currentpoisonCount > 0)
    {
        avatarRed = 192 + (3 * 255 * poisonDiff) / currentpoisonCount / 4;
        if (avatarRed < 0)
            avatarRed = 0;
    }
    currentpoisonCount = poisonCount;
    currentLife = life;

    r->FillRect(actX + 2, actY + 2, Width * actZ, Height * actZ, ARGB((int)(actA / 2), 0, 0, 0));

    float x0 = actX;
    float y0 = actY;

    if (player->getIcon().get())
    {
        if (corner == BOTTOM_RIGHT)
        {
            x0 -= Width * actZ;
            y0 -= Height * actZ;
        }
        switch (corner)
        {
        case TOP_LEFT:
            player->getIcon()->SetHotSpot(0, 0);
            break;
        case BOTTOM_RIGHT:
            player->getIcon()->SetHotSpot(player->getIcon()->mWidth, player->getIcon()->mHeight);
            break;
        }
        player->getIcon()->SetColor(ARGB((int)actA, 255, avatarRed, avatarRed));
        r->RenderQuad(player->getIcon().get(), actX, actY, actT, Width/player->getIcon()->mWidth*actZ, Height/player->getIcon()->mHeight*actZ);
        if (mHasFocus)
        {
            r->FillRect(x0, x0, Width/player->getIcon()->mWidth * actZ, Height/player->getIcon()->mHeight * actZ, ARGB(abs(128 - wave),255,255,255));
        }
    }

    if (avatarRed < 255)
    {
        avatarRed += 3;
        if (avatarRed > 255)
            avatarRed = 255;
    }

    if (player->getObserver()->currentPlayer == player)
        r->DrawRect(x0 - 1, y0 - 1, 36 * actZ, 51 * actZ, ARGB((int)actA, 0, 255, 0));
    else if (player->getObserver()->currentActionPlayer == player)
        r->DrawRect(x0, y0, 34 * actZ, 49 * actZ, ARGB((int)actA, 0, 0, 255));
    if (player->getObserver()->isInterrupting == player)
        r->DrawRect(x0, y0, 34 * actZ, 49 * actZ, ARGB((int)actA, 255, 0, 0));

    //Life
    char buffer[10];
    int lx = 255, ly = 255, lz = 255;
    if(life > 24) { lx = 127; ly = 255; lz = 212; }
    if(life > 16 && life < 24) { lx = 255; ly = 255; lz = 255; }
    if(life > 12 && life < 17) { lx = 255; ly = 255; lz = 105; }
    if(life > 8 && life < 13) { lx = 255; ly = 255; lz = 13; }
    if(life > 4 && life < 9) { lx = 255; ly = 166; lz = 0; }
    if(life < 5) { lx = 255; ly = 40; lz = 0; }
    sprintf(buffer, "%i", life);
    switch (corner)
    {
    case TOP_LEFT:
        mFont->SetColor(ARGB((int)actA / 4, 0, 0, 0));
        mFont->DrawString(buffer, actX + 2, actY + 2);
        mFont->SetScale(1.3f);
        mFont->SetColor(ARGB((int)actA, lx, ly, lz));
        mFont->DrawString(buffer, actX + 1, actY + 1);
        mFont->SetScale(1);
        break;
    case BOTTOM_RIGHT:
        mFont->SetScale(1.3f);
        mFont->SetColor(ARGB((int)actA, lx, ly, lz));
        mFont->DrawString(buffer, actX, actY - 14, JGETEXT_RIGHT);
        mFont->SetScale(1);
        break;
    }
    //poison
    char poison[5];
    if (poisonCount > 0)
    {
        sprintf(poison, "%i", poisonCount);
        switch (corner)
        {
        case TOP_LEFT:
            mFont->SetColor(ARGB((int)actA / 1, 0, 255, 0));
            mFont->DrawString(poison, actX + 2, actY + 10);
            break;
        case BOTTOM_RIGHT:
            mFont->SetColor(ARGB((int)actA / 1 ,0, 255, 0));
            mFont->DrawString(poison, actX, actY - 20, JGETEXT_RIGHT);
            break;
        }
    }
    PlayGuiObject::Render();
}