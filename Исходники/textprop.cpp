void TextProp::setTextStyle(const TextStyle& s)
      {
      fontBold->setChecked(s.bold());
      fontItalic->setChecked(s.italic());
      fontUnderline->setChecked(s.underline());
      fontSize->setValue(s.size());
      color->setColor(s.foregroundColor());

      systemFlag->setChecked(s.systemFlag());
      int a = s.align();
      if (a & ALIGN_HCENTER)
            alignHCenter->setChecked(true);
      else if (a & ALIGN_RIGHT)
            alignRight->setChecked(true);
      else
            alignLeft->setChecked(true);

      if (a & ALIGN_VCENTER)
            alignVCenter->setChecked(true);
      else if (a & ALIGN_BOTTOM)
            alignBottom->setChecked(true);
      else if (a & ALIGN_BASELINE)
            alignBaseline->setChecked(true);
      else
            alignTop->setChecked(true);

      QString str;
      if (s.offsetType() == OFFSET_ABS) {
            xOffset->setValue(s.offset().x() * INCH);
            yOffset->setValue(s.offset().y() * INCH);
            mmUnit->setChecked(true);
            curUnit = 0;
            }
      else if (s.offsetType() == OFFSET_SPATIUM) {
            xOffset->setValue(s.offset().x());
            yOffset->setValue(s.offset().y());
            spatiumUnit->setChecked(true);
            curUnit = 1;
            }
      rxOffset->setValue(s.reloff().x());
      ryOffset->setValue(s.reloff().y());

      QFont f(s.family());
      f.setPixelSize(lrint(s.size()));
      f.setItalic(s.italic());
      f.setUnderline(s.underline());
      f.setBold(s.bold());
      fontSelect->setCurrentFont(f);
      sizeIsSpatiumDependent->setChecked(s.sizeIsSpatiumDependent());

      frameColor->setColor(s.frameColor());
      bgColor->setColor(s.backgroundColor());
      frameWidth->setValue(s.frameWidth());
      frame->setChecked(s.hasFrame());
      paddingWidth->setValue(s.paddingWidth());
      frameRound->setValue(s.frameRound());
      circleButton->setChecked(s.circle());
      boxButton->setChecked(!s.circle());
      }