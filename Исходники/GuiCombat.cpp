void GuiCombat::Render()
{
    if (NONE == cursor_pos)
        return;
    JRenderer* renderer = JRenderer::GetInstance();
    renderer->FillRect(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, ARGB(200,0,0,0));

    for (inner_iterator it = attackers.begin(); it != attackers.end(); ++it)
        if ((*it)->show)
            (*it)->Render(step);
    if (activeAtk)
    {
        float setH = 0;
        float setW = 0;
        signed damage = activeAtk->card->stepPower(step);
        for (vector<DefenserDamaged*>::iterator q = activeAtk->blockers.begin(); q != activeAtk->blockers.end(); ++q)
        {
            (*q)->Render(step);
            damage -= (*q)->sumDamages();
            setH = (*q)->Height;
            setW = (*q)->Width;
        }
        if (damage < 0)
            damage = 0;
        if (activeAtk->card->has(Constants::TRAMPLE))
        {
            if(activeAtk->card->isAttacking && activeAtk->card->isAttacking != observer->opponent())
            {
                JQuadPtr enemy = WResourceManager::Instance()->RetrieveCard((MTGCardInstance*)activeAtk->card->isAttacking, CACHE_THUMB);
                float oldH = enemy->mHeight;
                float oldW = enemy->mWidth;
                enemy->mHeight = setH;
                enemy->mWidth = setW;
                enemy->SetHotSpot(18, 25);
                enemy_avatar.Render(enemy.get());
                enemy->mHeight = oldH;
                enemy->mWidth = oldW;
            }
            else
            {
                observer->opponent()->getIcon()->SetHotSpot(18, 25);
                enemy_avatar.Render(observer->opponent()->getIcon().get());
            }
            WFont * mFont = WResourceManager::Instance()->GetWFont(Fonts::MAIN_FONT);
            mFont->SetColor(ARGB(255, 255, 64, 0));
            {
                char buf[10];
                sprintf(buf, "%i", damage);
                mFont->DrawString(buf, enemy_avatar.actX - 25, enemy_avatar.actY - 40);
            }

        }
    }
    if (ok_tex)
    {
        JQuadPtr ok_quad = WResourceManager::Instance()->RetrieveTempQuad("Ok.png");
        ok_quad->SetHotSpot(28, 22);
        ok.Render(ok_quad.get());
    }
    renderer->DrawLine(0, SCREEN_HEIGHT / 2 + 10, SCREEN_WIDTH, SCREEN_HEIGHT / 2 + 10, ARGB(255, 255, 64, 0));
    if (FIRST_STRIKE == step)
    {
        WFont * mFont = WResourceManager::Instance()->GetWFont(Fonts::MAIN_FONT);
        mFont->SetColor(ARGB(255, 64, 255, 64));
        mFont->DrawString("First strike damage", 370, 2);
    }
}