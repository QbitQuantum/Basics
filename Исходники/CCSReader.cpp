 void CCSReader::setPropsForTextAreaFromCCDictionary(CocoWidget*widget,cocos2d::CCDictionary* options)
 {
     this->setPropsForWidgetFromCCDictionary(widget, options);
     CocoTextArea* textArea = (CocoTextArea*)widget;
     textArea->setText(DICTOOL->getStringValue(options, "text"));
     CCObject* fs = DICTOOL->checkObjectExist(options, "fontSize");
     if (fs) {
         textArea->setFontSize(DICTOOL->objectToIntValue(fs));
     }
     int cr = DICTOOL->getIntValue(options, "colorR");
     int cg = DICTOOL->getIntValue(options, "colorG");
     int cb = DICTOOL->getIntValue(options, "colorB");
     textArea->setTextColor(cr, cg, cb);
     textArea->setFontName(DICTOOL->getStringValue(options, "fontName"));
     CCObject* aw = DICTOOL->checkObjectExist(options, "areaWidth");
     CCObject* ah = DICTOOL->checkObjectExist(options, "areaHeight");
     if (aw && ah) {
         textArea->setTextAreaSize(DICTOOL->objectToFloatValue(aw),DICTOOL->objectToFloatValue(ah));
     }
     CCObject* ha = DICTOOL->checkObjectExist(options, "hAlignment");
     if (ha) {
         textArea->setTextHorizontalAlignment(DICTOOL->objectToIntValue(ha));
     }
     CCObject* va = DICTOOL->checkObjectExist(options, "vAlignment");
     if (va) {
         textArea->setTextVerticalAlignment(DICTOOL->objectToIntValue(va));
     }
     this->setColorPropsForWidgetFromCCDictionary(widget, options);
 }