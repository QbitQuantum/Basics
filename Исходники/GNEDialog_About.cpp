// ===========================================================================
// method definitions
// ===========================================================================
GNEDialog_About::GNEDialog_About(FXWindow* parent) :
    FXDialogBox(parent, "About Eclipse SUMO netedit", GUIDesignDialogBox) {
    // set dialog icon
    setIcon(GUIIconSubSys::getIcon(ICON_NETEDIT));

    // create frame for main info
    FXHorizontalFrame* mainInfoFrame = new FXHorizontalFrame(this, GUIDesignAuxiliarHorizontalFrame);

    // Netedit icon
    new FXLabel(mainInfoFrame, "", GUIIconSubSys::getIcon(ICON_NETEDIT), GUIDesignLabelIcon64x64noSpacing);

    // "SUMO <VERSION>"
    FXVerticalFrame* descriptionFrame = new FXVerticalFrame(mainInfoFrame, GUIDesignLabelAboutInfo);
    myHeadlineFont = new FXFont(getApp(), "Arial", 18, FXFont::Bold);
    FXLabel* neteditLabel = new FXLabel(descriptionFrame, "SUMO netedit " VERSION_STRING, 0, GUIDesignLabelAboutInfo);
    neteditLabel->setFont(myHeadlineFont);
    new FXLabel(descriptionFrame, "Network editor for Eclipse SUMO, the Simulation of Urban MObility", 0, GUIDesignLabelAboutInfo);
    new FXLabel(descriptionFrame, HAVE_ENABLED, 0, GUIDesignLabelAboutInfo);

    // write HAVE_ENABLED with the current modules (except Windows)
    if (OptionsCont::getOptions().getBool("gui-testing-debug")) {
        std::string modules(HAVE_ENABLED);
        while((modules.size() > 0) && (modules.front() != ' ')) {
            modules.erase(modules.begin());
        }
        WRITE_WARNING(("Modules: " + modules).c_str());
    }

    // copyright notice
    new FXLabel(this, "Graphical editor for networks of the traffic simulation SUMO.", 0, GUIDesignLabelAboutInfo);
    new FXLabel(this, "Copyright (C) 2001-2018 German Aerospace Center (DLR) and others.", 0, GUIDesignLabelAboutInfo);
    new FXLabel(this, "This application is based on code provided by the Eclipse SUMO project.", 0, GUIDesignLabelAboutInfo);
    new FXLabel(this, "These core components are available under the conditions of the Eclipse Public License v2.", 0, GUIDesignLabelAboutInfo);
    (new FXLinkLabel(this, "SPDX-License-Identifier: EPL-2.0", 0, GUIDesignLabelAboutInfo))->setTipText("http://www.eclipse.org/legal/epl-v20.html");

    // link to homepage
    (new FXLinkLabel(this, "http://sumo.dlr.de", 0, GUIDesignLabelCenter))->setTipText("http://sumo.dlr.de");

    // centered ok-button
    FXHorizontalFrame* buttonFrame = new FXHorizontalFrame(this, GUIDesignHorizontalFrame);
    new FXHorizontalFrame(buttonFrame, GUIDesignAuxiliarHorizontalFrame);
    FXButton* OKButton = new FXButton(buttonFrame, "&OK\t\t", GUIIconSubSys::getIcon(ICON_ACCEPT), this, ID_ACCEPT, GUIDesignButtonOK);
    new FXHorizontalFrame(buttonFrame, GUIDesignAuxiliarHorizontalFrame);

    // focus OK button
    OKButton->setFocus();
}