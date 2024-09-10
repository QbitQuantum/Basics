bool GUITabbedPanel::loadXMLSettings(XMLElement *element)
{
  if(!element || element->getName() != "TabbedPanel")
  {
     LOG_PRINT("Need a TabbedPanel node in the xml file");
	 return false;
  }

  XMLElement *child                = 0,
             *subChild             = 0;
  D3DXFROMWINEVECTOR3     bordersColor         = upperPanel->getBordersColor();
  D3DXFROMWINEVECTOR4     bgColor              = upperPanel->getBGColor();
  int         count                = 0;

  if(child = element->getChildByName("hScale"))
    fontScales.y = child->getValuef();

  if(child = element->getChildByName("wScale"))
    fontScales.x = child->getValuef();

  if(child = element->getChildByName("TabButtonsBordersColor"))
    XMLElement::loadRX_GY_BZf(*child, tabButtonsBordersColor);

  if(child = element->getChildByName("TabButtonsColor"))
    XMLElement::loadRX_GY_BZf(*child, tabButtonsColor);

  if(child = element->getChildByName("BordersColor"))
    XMLElement::loadRX_GY_BZf(*child, bordersColor);

  if(child = element->getChildByName("BGColor"))
    XMLElement::loadRX_GY_BZ_AWf(*child, bgColor);

  if(child = element->getChildByName("fontIndex"))
    fontIndex =  clampNS(child->getValuei(), 0, 50);

  setFontScales(fontScales);

  for(size_t i = 0; i < element->getChildrenCount(); i++)
  {
    if(!(child = element->getChild(i)))
      continue;

    const NSString &childName = child->getName();

    if(childName == "Panel")
    {
      GUIPanel *panel = new GUIPanel();
      if(!panel->loadXMLSettings(child) || !addPanel(panel))
        deleteObject(panel);
      continue;
    }
  }

  mainPanel->setBordersColor(bordersColor);
  mainPanel->setBGColor(bgColor);

  return GUIRectangle::loadXMLSettings(element) && lowerPanel->getWidgets().size();
}