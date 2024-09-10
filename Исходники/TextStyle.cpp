bool TextStyleData::readProperties(XmlReader& e)
      {
      const QStringRef& tag(e.name());

      if (tag == "name")
            name = e.readElementText();
      else if (tag == "family")
            family = e.readElementText();
      else if (tag == "size")
            size = e.readDouble();
      else if (tag == "bold")
            bold = e.readInt();
      else if (tag == "italic")
            italic = e.readInt();
      else if (tag == "underline")
            underline = e.readInt();
      else if (tag == "align")
            setAlign(Align(e.readInt()));
      else if (tag == "anchor")     // obsolete
            e.skipCurrentElement();
      else if (ElementLayout::readProperties(e))
            ;
      else if (tag == "sizeIsSpatiumDependent" || tag == "spatiumSizeDependent")
            sizeIsSpatiumDependent = e.readInt();
      else if (tag == "frameWidth") { // obsolete
            hasFrame = true;
            frameWidthMM = e.readDouble();
            }
      else if (tag == "frameWidthS") {
            hasFrame = true;
            frameWidth = Spatium(e.readDouble());
            }
      else if (tag == "frame")
            hasFrame = e.readInt();
      else if (tag == "square")
            _square = e.readInt();
      else if (tag == "paddingWidth")          // obsolete
            paddingWidthMM = e.readDouble();
      else if (tag == "paddingWidthS")
            paddingWidth = Spatium(e.readDouble());
      else if (tag == "frameRound")
            frameRound = e.readInt();
      else if (tag == "frameColor")
            frameColor = e.readColor();
      else if (tag == "foregroundColor")
            foregroundColor = e.readColor();
      else if (tag == "backgroundColor")
            backgroundColor = e.readColor();
      else if (tag == "circle")
            circle = e.readInt();
      else if (tag == "systemFlag")
            systemFlag = e.readInt();
      else
            return false;
      return true;
      }