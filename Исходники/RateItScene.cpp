    void setup(AssetAPI*) override {
        //Creating text entities
        textToReadContainer = theEntityManager.CreateEntityFromTemplate("rateit/container");

        textToRead = theEntityManager.CreateEntityFromTemplate("rateit/text");

        TEXT(textToRead)->text = game->gameThreadContext->localizeAPI->text("please_rate_it");
        // ??
        // TRANSFORM(textToRead)->position.x = TRANSFORM(textToReadContainer)->position.x = 0;

        std::stringstream a;
        for (int i = 0; i < 3; i++) {
            a.str("");
            a << "boutonText_" << i;
            boutonText[i] = theEntityManager.CreateEntityFromTemplate("rateit/button_text");

            a.str("");
            a << "boutonContainer_" << i;
            boutonContainer[i] = theEntityManager.CreateEntityFromTemplate("rateit/button");

            TRANSFORM(boutonText[i])->position.y =
                TRANSFORM(boutonContainer[i])->position.y = (float)PlacementHelper::GimpYToScreen(650 + i*183);
        }
        TEXT(boutonText[0])->text = game->gameThreadContext->localizeAPI->text("rate_now");
        TEXT(boutonText[1])->text = game->gameThreadContext->localizeAPI->text("rate_later");
        TEXT(boutonText[2])->text = game->gameThreadContext->localizeAPI->text("rate_never");
    }