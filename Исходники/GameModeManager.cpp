void GameModeManager::Setup() {
    herisson = theEntityManager.CreateEntityFromTemplate("gamemode/herisson");

    branch = theEntityManager.CreateEntityFromTemplate("gamemode/branch");

    decor2nd = theEntityManager.CreateEntityFromTemplate("gamemode/decor2nd");
    // HACK
    TRANSFORM(decor2nd)->size.x = PlacementHelper::ScreenSize.x;

    SCROLLING(decor2nd)->images.push_back(HASH("decor2nd_0", 0x2da4a4da));
    SCROLLING(decor2nd)->images.push_back(HASH("decor2nd_3", 0xb93314de));
    SCROLLING(decor2nd)->images.push_back(HASH("decor2nd_2", 0xc2edcdae));
    SCROLLING(decor2nd)->images.push_back(HASH("decor2nd_1", 0xe8c9a7d4));

    decor1er = theEntityManager.CreateEntityFromTemplate("gamemode/decor1er");
    TRANSFORM(decor1er)->size.x = PlacementHelper::ScreenSize.x;

    SCROLLING(decor1er)->images.push_back(HASH("decor1er_0", 0x3a3efebf));
    SCROLLING(decor1er)->images.push_back(HASH("decor1er_1", 0x5ba415d2));
    SCROLLING(decor1er)->images.push_back(HASH("decor1er_2", 0x68f8263e));
    SCROLLING(decor1er)->images.push_back(HASH("decor1er_3", 0x4d7b9af));

    fillVec();

    uiHelper.build();

    #if SAC_DEBUG
    _debug = false;
    for(int i=0; i<8; i++) {
        debugEntities[2*i] = theEntityManager.CreateEntity(HASH("debug/Entities", 0x15df1b7c));
        ADD_COMPONENT(debugEntities[2*i], Rendering);
        ADD_COMPONENT(debugEntities[2*i], Transformation);
        RENDERING(debugEntities[2*i])->texture = theRenderingSystem.loadTextureFile(HeriswapGame::cellTypeToTextureNameAndRotation(i, 0));
        TRANSFORM(debugEntities[2*i])->z = DL_DebugLayer;
        TRANSFORM(debugEntities[2*i])->size = glm::vec2((float)PlacementHelper::GimpWidthToScreen(80));

        debugEntities[2*i + 1] = theEntityManager.CreateEntity(HASH("debug/Entities", 0x15df1b7c));
        ADD_COMPONENT(debugEntities[2*i + 1], Text);
        TEXT(debugEntities[2*i + 1])->positioning = TextComponent::CENTER;
        ADD_COMPONENT(debugEntities[2*i + 1], Transformation);
        TRANSFORM(debugEntities[2*i + 1])->position = TRANSFORM(debugEntities[2*i])->position;
        TRANSFORM(debugEntities[2*i+1])->z = DL_DebugLayer + 0.01f;
        TEXT(debugEntities[2*i + 1])->fontName = HASH("typo", 0x5a18f4a9);
        TEXT(debugEntities[2*i + 1])->charHeight = PlacementHelper::GimpHeightToScreen(25);
    }
    #endif
}