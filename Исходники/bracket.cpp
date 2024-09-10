Element* Bracket::drop(const DropData& data)
      {
      Element* e = data.element;
      if (e->type() == BRACKET) {
            Bracket* b = static_cast<Bracket*>(e);
            b->setParent(parent());
            b->setTrack(track());
            b->setSpan(span());
            b->setLevel(level());
            score()->undoRemoveElement(this);
            score()->undoAddElement(b);
            return b;
            }
      delete e;
      return 0;
      }