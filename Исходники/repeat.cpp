Marker::Marker(Score* s)
   : Text(s)
      {
      setFlags(ELEMENT_MOVABLE | ELEMENT_SELECTABLE | ELEMENT_ON_STAFF);
      setTextStyle(s->textStyle(TEXT_STYLE_REPEAT));
      }