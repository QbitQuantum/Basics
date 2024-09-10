 void drawPopupMenuItem (Graphics& g, const Rectangle<int>& area,
                                         const bool isSeparator, const bool isActive,
                                         const bool isHighlighted, const bool isTicked,
                                         const bool hasSubMenu, const String& text,
                                         const String& shortcutKeyText,
                                         const Drawable* icon, const Colour* const textColourToUse)
 {
     Rectangle<int> r(area.reduced(1));
     if(isHighlighted)
     {
         g.setColour(Env::getColorTxt());
         g.fillRect(r);
         g.setColour(Env::getColorBg());
     }
     else
     {
         g.setColour(Env::getColorTxt());
     }
     g.setFont(Env::getFont());
     Rectangle<float> iconArea(r.removeFromRight((r.getHeight() * 5) / 4).reduced(3).toFloat());
 
     if(isTicked)
     {
         const Path tick (getTickShape (1.0f));
         g.fillPath(tick, tick.getTransformToScaleToFit (iconArea, true));
     }
     g.drawFittedText(text, 4, 1, area.getWidth() - 4, area.getHeight() - 1, Justification::centredLeft, 1);
 }