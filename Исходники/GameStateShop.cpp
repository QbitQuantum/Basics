void GameStateShop::Render()
{
    //Erase
    WFont * mFont = WResourceManager::Instance()->GetWFont(Fonts::MAIN_FONT);
    JRenderer * r = JRenderer::GetInstance();
    r->ClearScreen(ARGB(0,0,0,0));
    if (mStage == STAGE_FADE_IN)
        return;

    JQuadPtr mBg = WResourceManager::Instance()->RetrieveTempQuad("shop.jpg", TEXTURE_SUB_5551);
    if (mBg.get())
        r->RenderQuad(mBg.get(), 0, 0);

    JQuadPtr quad = WResourceManager::Instance()->RetrieveTempQuad("shop_light.jpg", TEXTURE_SUB_5551);
    if (quad.get())
    {
        r->EnableTextureFilter(false);
        r->SetTexBlend(BLEND_SRC_ALPHA, BLEND_ONE);
        quad->SetColor(ARGB(lightAlpha,255,255,255));
        r->RenderQuad(quad.get(), 0, 0);
        r->SetTexBlend(BLEND_SRC_ALPHA, BLEND_ONE_MINUS_SRC_ALPHA);
        r->EnableTextureFilter(true);
    }

    if (shopMenu)
        shopMenu->Render();
    
    if (filterMenu && !filterMenu->isFinished())
        filterMenu->Render();
    else
    {
        if (boosterDisplay)
            boosterDisplay->Render();
        else if (bigDisplay)
        {
            if (bigDisplay->mOffset.getPos() >= 0)
                bigDisplay->setSource(srcCards);
            else
                bigDisplay->setSource(NULL);
            bigDisplay->Render();
            float elp = srcCards->getElapsed();
            //Render the card list overlay.
            if (bListCards || elp > LIST_FADEIN)
            {
                int alpha = 200;
                if (!bListCards && elp < LIST_FADEIN + .25)
                {
                    alpha = static_cast<int> (800 * (elp - LIST_FADEIN));
                }
                r->FillRoundRect(300, 10, 160, SHOP_SLOTS * 20 + 15, 5, ARGB(alpha,0,0,0));
                alpha += 55;
                for (int i = 0; i < SHOP_SLOTS; i++)
                {
                    if (i == shopMenu->getSelected())
                        mFont->SetColor(ARGB(alpha,255,255,0));
                    else
                        mFont->SetColor(ARGB(alpha,255,255,255));
                    char buffer[512];
                    string s = descPurchase(i, true);
                    sprintf(buffer, "%s", s.c_str());
                    float x = 310;
                    float y = static_cast<float> (25 + 20 * i);
                    mFont->DrawString(buffer, x, y);
                }
            }
        }
    }

    //Render the info bar
    r->FillRect(0, SCREEN_HEIGHT - 17, SCREEN_WIDTH, 17, ARGB(128,0,0,0));
    std::ostringstream stream;
    stream << kCreditsString << playerdata->credits;
    mFont->SetColor(ARGB(255,255,255,255));
    mFont->DrawString(stream.str(), 5, SCREEN_HEIGHT - 14);

#ifndef TOUCH_ENABLED
    float len = 4 + mFont->GetStringWidth(kOtherCardsString.c_str());
	r->RenderQuad(pspIcons[6].get(), SCREEN_WIDTH - len - 0.5 - 10, SCREEN_HEIGHT - 8, 0, kPspIconScaleFactor, kPspIconScaleFactor);
    mFont->DrawString(kOtherCardsString, SCREEN_WIDTH - len, SCREEN_HEIGHT - 14);
#else
    enableButtons();
#endif
    
    mFont->SetColor(ARGB(255,255,255,0));
    mFont->DrawString(descPurchase(bigSync.getPos()).c_str(), SCREEN_WIDTH / 2, SCREEN_HEIGHT - 14, JGETEXT_CENTER);
    mFont->SetColor(ARGB(255,255,255,255));

    if (mStage == STAGE_SHOP_TASKS && taskList)
    {
        taskList->Render();
    }
    if (menu)
        menu->Render();
    
    if (!filterMenu || (filterMenu && filterMenu->isFinished()))
        renderButtons();
}