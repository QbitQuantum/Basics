void InspectorNote::dot3Clicked()
      {
      Note* note = static_cast<Note*>(inspector->element());
      if (note == 0)
            return;
      NoteDot* dot = note->dot(2);
      if (dot) {
            dot->score()->select(dot);
            inspector->setElement(dot);
            dot->score()->end();
            }
      }