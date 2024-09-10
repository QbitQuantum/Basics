Element* Lyrics::drop(const DropData& data)
      {
      Element::Type type = data.element->type();
      if (type == Element::Type::SYMBOL || type == Element::Type::FSYMBOL) {
            Text::drop(data);
            return 0;
            }
      Text* e = static_cast<Text*>(data.element);
      if (!(type == Element::Type::TEXT && e->textStyle().name() == "Lyrics Verse Number")) {
            delete e;
            return 0;
            }
      e->setParent(this);
      score()->undoAddElement(e);
      return e;
      }