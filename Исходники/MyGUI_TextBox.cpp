 void TextBox::setPropertyOverride(const std::string& _key, const std::string& _value)
 {
     if (_key == "TextColour")
         setTextColour(utility::parseValue<Colour>(_value));
     else if (_key == "TextAlign")
         setTextAlign(utility::parseValue<Align>(_value));
     else if (_key == "FontName")
         setFontName(_value);
     else if (_key == "FontHeight")
         setFontHeight(utility::parseValue<int>(_value));
     else if (_key == "Caption")
         setCaptionWithReplacing(_value);
     else if (_key == "TextShadowColour")
         setTextShadowColour(utility::parseValue<Colour>(_value));
     else if (_key == "TextShadow")
         setTextShadow(utility::parseValue<bool>(_value));
     else
     {
         Base::setPropertyOverride(_key, _value);
         return;
     }
     eventChangeProperty(this, _key, _value);
 }