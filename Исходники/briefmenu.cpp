BriefMenu::BriefMenu(MenuManager * m)
    : Menu(m, MENU_BRIEF, MENU_MAP, "mbrief.dat", "mbrieout.dat"),
        start_line_(0), p_briefing_(NULL), mm_renderer_() {
    addStatic(85, 35, 545, "#BRIEF_TITLE", FontManager::SIZE_4, false);
    txtTimeId_ = addStatic(500, 9, "", FontManager::SIZE_2, true);       // Time

    // Briefing scroll button
    nextButId_ = addImageOption(461, 316, Sprite::MSPR_RIGHT_ARROW2_D, Sprite::MSPR_RIGHT_ARROW2_L);
    registerHotKey(KFC_RIGHT, nextButId_);
    prevButId_ = addImageOption(427, 316, Sprite::MSPR_LEFT_ARROW2_D, Sprite::MSPR_LEFT_ARROW2_L);
    registerHotKey(KFC_LEFT, prevButId_);

    // Accept button
    addOption(17, 347, 128, 25, "#MENU_ACC_BUT", FontManager::SIZE_2, MENU_SELECT);
    // Map button
    addOption(148, 347, 99, 25, "#BRIEF_MAP", FontManager::SIZE_2, MENU_MAP);
    // Main menu button
    addOption(500, 347,  128, 25, "#MENU_MAIN_BUT", FontManager::SIZE_2, MENU_MAIN);

    // Money
    txtMoneyId_ = addStatic(500, 87, 127, "0", FontManager::SIZE_2, true);     // textfield
    // Info
    infosButId_ = addOption(500, 118, 127, 10, "#BRIEF_INFO", FontManager::SIZE_2); // info button
    txtInfoId_ = addStatic(500, 140, 127, "0", FontManager::SIZE_2, true);
    // Enhancement
    enhButId_ = addOption(500, 169, 127, 10, "#BRIEF_ENH", FontManager::SIZE_2);
    txtEnhId_ = addStatic(500, 195, 127, "0", FontManager::SIZE_2, true);

    a_page_ = new std::string[kMaxLinePerPage];
}