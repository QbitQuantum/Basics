void WsMenu::createMenu(NodePtr curNode, WMenu* menuParent)
{
  std::string path2Icon;
  WsUser*     pUser   = WsApp->wsUser();
  std::string sIcon   = curNode.get()->getProperties().get()->get("global", "icon", "");
  if ( sIcon.size() > 1 ) {
    NodePtr tmpNode = curNode;
    if ( tmpNode.get()->isRegularFile() )
      tmpNode   = curNode.get()->getParent();
    if ( tmpNode.get() ) {
      path2Icon = tmpNode.get()->getFullPath().string() + "/ws.res/icones/" + sIcon;
      if ( !boost::filesystem::exists(path2Icon) )
        path2Icon.clear();
      else {
        boost::algorithm::replace_first(path2Icon, WsApp->docRoot(), "");
      }
    }
  }
  if ( asString(option("useButtons")) == "true" ) {
    if ( curNode.get()->getPath().string() != "/" )
      if ( asString(option("useSeparator")) == "true" ) {
        WText* pText = new WText("|", this);
        pText->addStyleClass("WsMenuSep");
      }
    WPushButton* button = new WPushButton(curNode.get()->getDisplayName(true), this);
    m_vPushButton.push_back(button);
    if ( path2Icon.size() > 1 ) {
      button->setIcon(WLink(WLink::Url, path2Icon));
      if ( curNode.get()->getProperties().get()->get("global", "button_text", "true") == "false" )
        button->setText("");
    }
    // TODO : Ameliorer cette fonction
    if ( (curNode.get()->isDirectory() && asString(option("directorySelectable")) == "true") ||
         pUser->isAdministrator() || pUser->isEditor() ||
         (asString(option("showRoot")) == "true" && curNode.get()->getPath() == "/")
       ) {
      button->setLink(WLink(WLink::InternalPath, curNode.get()->getPath().string()));
    }
    if ( curNode.get()->isRegularFile() ) {
      button->setLink(makeLink(curNode.get()->getPath().string(), false));
      if ( button->link().type() == WLink::Url )
        button->setLinkTarget(TargetNewWindow);
    }
    bool popupAllowed = (curNode.get()->getProperties().get()->get("global", "allow_popup", "true") == "true" ? true : false);
    if ( curNode.get()->isDirectory() && popupAllowed && asString(option("usePopupMenu")) == "true" ) {
      if ( !(asString(option("noRootPopup")) == "true" && curNode.get()->getPath() == "/") ) {
        WPopupMenu* pPopup = new WPopupMenu();
        pPopup->addStyleClass("wt-no-reparent");
        loadPopupMenu(curNode, pPopup);
        button->setMenu(pPopup);
        pPopup->setAutoHide(true);
        button->mouseWentOver().connect(boost::bind(&WsMenu::onMouseWentOver, this, button));
        button->setMouseOverDelay(50);
      }
    }
  } else { // No buttons, standard menu
    if ( curNode.get()->getPath().string() != "/" )
      menuParent->addSeparator();
    WMenuItem* pItem = menuParent->addItem(curNode.get()->getDisplayName(true));
    pItem->setLink(WLink(WLink::InternalPath, curNode.get()->getPath().string()));
    if ( path2Icon.size() > 1 )
      pItem->setIcon(path2Icon);
    if ( curNode.get()->isDirectory() && asString(option("usePopupMenu")) == "true" )
      if ( curNode.get()->getDirectories().size() ) {
        WPopupMenu* pPopup = new WPopupMenu();
        pPopup->addStyleClass("wt-no-reparent");
        loadPopupMenu(curNode, pPopup);
        pItem->setMenu(pPopup);
      }
  }
}