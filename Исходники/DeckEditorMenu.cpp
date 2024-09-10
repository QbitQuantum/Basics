void DeckEditorMenu::Render()
{
    JRenderer *r = JRenderer::GetInstance();
    r->FillRect(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, ARGB(200,0,0,0));//bg??

    DeckMenu::Render();
    if (deckTitle.size() > 0)
    {
        WFont *mainFont = WResourceManager::Instance()->GetWFont(Fonts::OPTION_FONT);
        DWORD currentColor = mainFont->GetColor();
        mainFont->SetColor(ARGB(255,255,255,255));
        mainFont->DrawString(deckTitle.c_str(), (SCREEN_WIDTH_F / 2)-15, (statsHeight / 2)+4, JGETEXT_CENTER);
        mainFont->SetColor(currentColor);
    }

    if (stw && selectedDeck) drawDeckStatistics();

}