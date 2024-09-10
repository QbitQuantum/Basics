void RenderState::buildGUI()
{

        OgreBites::SdkTrayManager* trayMgr = OgreFramework::getSingletonPtr()->_trayMgr;


        trayMgr->showFrameStats(OgreBites::TL_BOTTOMLEFT);
        // trayMgr->showLogo(OgreBites::TL_BOTTOMRIGHT);
        // trayMgr->createLabel(OgreBites::TL_TOP, "GameLbl", "Game mode", 250);
        trayMgr->showCursor();

        Ogre::StringVector items;
        items.push_back("cam.pX");
        items.push_back("cam.pY");
        items.push_back("cam.pZ");
        items.push_back("cam.oW");
        items.push_back("cam.oX");
        items.push_back("cam.oY");
        items.push_back("cam.oZ");
        items.push_back("Mode");

        _detailsPanel = trayMgr->createParamsPanel(OgreBites::TL_NONE, 
                                                     "DetailsPanel", 200, items);
        _detailsPanel->hide();

        Ogre::StringVector displayModes;
        displayModes.push_back("Solid mode");
        displayModes.push_back("Wireframe mode");
        displayModes.push_back("Point mode");
        trayMgr->createLongSelectMenu(OgreBites::TL_TOPRIGHT, 
                                      "DisplayModeSelMenu", 
                                      "Display Mode", 200, 3, displayModes);

        lightCheckBox = trayMgr->createCheckBox(OgreBites::TL_TOPLEFT, "light", 
                                                "Moving light", 200);

        tmkSlider = trayMgr->createLongSlider(OgreBites::TL_TOPLEFT, "tmk", 
                                              "tmk", 200,80,44,0,25,101);

        tmk2Slider = trayMgr->createLongSlider(OgreBites::TL_TOPLEFT, "tmk2", 
                                               "tmk2", 200,80,44,0,70,101);

        mintmSlider = trayMgr->createLongSlider(OgreBites::TL_TOPLEFT, "minTm", 
                                                "minTm", 200,80,44,0,1,101);

        shininessSlider = trayMgr->createLongSlider(OgreBites::TL_TOPLEFT, "shininess", 
                                                    "shininess",  200,80,44,0,10,101);

        stepsSlider = trayMgr->createLongSlider(OgreBites::TL_TOPLEFT, "steps", 
                                                "steps",  200,80,44,16,1024,241);

        ambientSlider = trayMgr->createLongSlider(OgreBites::TL_TOPLEFT, "ambient", 
                                                  "ambient",  200,80,44,-1,3,61);

        backIllumSlider = trayMgr->createLongSlider(OgreBites::TL_TOPLEFT, "backIllum", 
                                          "back illumination", 200,80,44,0,3,31);

        shadeCoeffSlider = trayMgr->createLongSlider(OgreBites::TL_TOPLEFT, "shadeCoeff", 
                                                     "shadeCoeff", 200,80,44,0.1,5,50);

        specCoeffSlider = trayMgr->createLongSlider(OgreBites::TL_TOPLEFT, "specCoeff", 
                                                     "specCoeff", 200,80,44,0.1,5,50);

        specMultSlider = trayMgr->createLongSlider(OgreBites::TL_TOPLEFT, "specMult", 
                                                     "specMult", 200,80,44,0.1,8,80);

        glowCoeffSlider = trayMgr->createLongSlider(OgreBites::TL_TOPLEFT, "glowCoeff", 
                                               "glowCoeff", 200,80,44,0,5,101);

        miscSlider = trayMgr->createLongSlider(OgreBites::TL_TOPLEFT, "misc", 
                                               "misc", 200,80,44,0,10,101);

        // OgreBites::Button* reloadMaterialButton = 
        //         trayMgr->createButton(OgreBites::TL_RIGHT, 
        //                               "ReloadMaterial", 
        //                               "Reload material", 60);

        updateWidgets();
}