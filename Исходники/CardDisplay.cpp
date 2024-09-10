void CardDisplay::Render()
{

    JRenderer * r = JRenderer::GetInstance();
    r->DrawRect(static_cast<float> (x), static_cast<float> (y), static_cast<float> (nb_displayed_items * 30 + 20), 50,
                    ARGB(255,255,255,255));
    if (!mObjects.size()) return;
    for (int i = start_item; i < start_item + nb_displayed_items && i < (int)(mObjects.size()); i++)
    {
        if (mObjects[i])
        {
            mObjects[i]->Render();
            if (tc)
            {
                CardGui * cardg = (CardGui *) mObjects[i];
                if (tc->alreadyHasTarget(cardg->card))
                {
                    r->DrawCircle(cardg->x + 5, cardg->y + 5, 5, ARGB(255,255,0,0));
                }
                else if (!tc->canTarget(cardg->card))
                {
                    r->FillRect(cardg->x, cardg->y, 30, 40, ARGB(200,0,0,0));
                }
            }
        }
    }

    //TODO: CardSelector should handle the graveyard and the library in the future...
    if (mObjects.size() && mObjects[mCurr] != NULL)
    {
        mObjects[mCurr]->Render();
        CardGui * cardg = ((CardGui *) mObjects[mCurr]);
        //Pos pos = Pos(CardGui::BigWidth / 2, CardGui::BigHeight / 2 - 10, 1.0, 0.0, 220);
        Pos pos = Pos((CardGui::BigWidth / 2), CardGui::BigHeight / 2 - 10, 0.80f, 0.0, 220);
        int drawMode = DrawMode::kNormal;
        if (observer)
        {
            //pos.actY = 145;
            pos.actY = 142;//reduce y a little
            if (x < (CardGui::BigWidth / 2)) pos.actX = SCREEN_WIDTH - 10 - CardGui::BigWidth / 2;
            drawMode = observer->getCardSelector()->GetDrawMode();
        }

        cardg->DrawCard(pos, drawMode);
    }
}