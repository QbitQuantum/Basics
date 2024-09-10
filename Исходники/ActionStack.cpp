void Interruptible::Render(MTGCardInstance * source, JQuad * targetQuad, string alt1, string alt2, string action,
    bool bigQuad)
{
    WFont * mFont = observer->getResourceManager()->GetWFont(Fonts::MAIN_FONT);
    mFont->SetColor(ARGB(255,255,255,255));
    mFont->SetScale(DEFAULT_MAIN_FONT_SCALE);
    JRenderer * renderer = JRenderer::GetInstance();
    
    if (!targetQuad)
    {
        /*if(source->controller()->isHuman() && source->controller()->opponent()->isAI() && !alt2.size() && _(action).c_str() == source->name)
            mFont->DrawString("You play ", x + 35, y-15 + GetVerticalTextOffset(), JGETEXT_LEFT);
        else if(source->controller()->isAI() && source->controller()->opponent()->isHuman() && !alt2.size() && _(action).c_str() == source->name)
            mFont->DrawString("Opponent plays ", x + 35, y-15 + GetVerticalTextOffset(), JGETEXT_LEFT);*/
        mFont->DrawString(_(action).c_str(), x + 35, y + GetVerticalTextOffset(), JGETEXT_LEFT);
    }
    else
    {
        renderer->FillRect(x-2,y-16 + GetVerticalTextOffset(), 73, 43, ARGB(235,10,10,10));
        /*if(source->controller()->isHuman() && source->controller()->opponent()->isAI())
            renderer->DrawRect(x-2,y-16 + GetVerticalTextOffset(), 73, 43, ARGB(245,0,255,0));
        else
            renderer->DrawRect(x-2,y-16 + GetVerticalTextOffset(), 73, 43, ARGB(245,255,0,0));*/
        mFont->DrawString(">", x + 32, y + GetVerticalTextOffset(), JGETEXT_LEFT);
        mFont->DrawString(_(action).c_str(), x + 75, y + GetVerticalTextOffset(), JGETEXT_LEFT);
    }

    JQuadPtr quad = observer->getResourceManager()->RetrieveCard(source, CACHE_THUMB);
    if (!quad.get())
        quad = CardGui::AlternateThumbQuad(source);
    if (quad.get())
    {
        quad->SetColor(ARGB(255,255,255,255));
        float scale = mHeight / quad->mHeight;
        renderer->RenderQuad(quad.get(), x + (quad->mWidth * scale / 2), y + (quad->mHeight * scale / 2), 0, scale, scale);
    }
    else if (alt1.size())
    {
        mFont->DrawString(_(alt1).c_str(), x, y + GetVerticalTextOffset());
    }

    if (bigQuad)
    {
        /*Pos pos = Pos(CardGui::BigWidth / 2, CardGui::BigHeight / 2 - 10, 1.0, 0.0, 220);
        CardGui::DrawCard(source, pos, observer->getCardSelector()->GetDrawMode());*/
        Pos pos = Pos(CardGui::BigWidth / 2, CardGui::BigHeight / 2 - 10, 0.80f, 0.0, 220);
        pos.actY = 142;//adjust y a little bit
        CardGui::DrawCard(source, pos, observer->getCardSelector()->GetDrawMode());
    }

    if (targetQuad)
    {
        float backupX = targetQuad->mHotSpotX;
        float backupY = targetQuad->mHotSpotY;
        targetQuad->SetColor(ARGB(255,255,255,255));
        targetQuad->SetHotSpot(targetQuad->mWidth / 2, targetQuad->mHeight / 2);
        float scale = mHeight / targetQuad->mHeight;
        renderer->RenderQuad(targetQuad, x + 55, y + ((mHeight - targetQuad->mHeight) / 2) + targetQuad->mHotSpotY, 0, scale, scale);
        targetQuad->SetHotSpot(backupX, backupY);
    }
    else if (alt2.size())
    {
        mFont->DrawString(_(alt2).c_str(), x + 35, y+15 + GetVerticalTextOffset());
    }
}