void CGUITextLayout::ParseText(const CStdStringW &text, DWORD defaultStyle, vector<DWORD> &colors, vector<DWORD> &parsedText)
{
  // run through the string, searching for:
  // [B] or [/B] -> toggle bold on and off
  // [I] or [/I] -> toggle italics on and off
  // [COLOR ffab007f] or [/COLOR] -> toggle color on and off
  // [CAPS <option>] or [/CAPS] -> toggle capatilization on and off

  DWORD currentStyle = defaultStyle; // start with the default font's style
  DWORD currentColor = 0;

  stack<DWORD> colorStack;
  colorStack.push(0);

  // these aren't independent, but that's probably not too much of an issue
  // eg [UPPERCASE]Glah[LOWERCASE]FReD[/LOWERCASE]Georeg[/UPPERCASE] will work (lower case >> upper case)
  // but [LOWERCASE]Glah[UPPERCASE]FReD[/UPPERCASE]Georeg[/LOWERCASE] won't
#define FONT_STYLE_UPPERCASE 4
#define FONT_STYLE_LOWERCASE 8

  int startPos = 0;
  size_t pos = text.Find(L'[');
  while (pos != CStdString::npos && pos + 1 < text.size())
  {
    DWORD newStyle = 0;
    DWORD newColor = currentColor;
    bool newLine = false;
    // have a [ - check if it's an ON or OFF switch
    bool on(true);
    int endPos = pos++; // finish of string
    if (text[pos] == L'/')
    {
      on = false;
      pos++;
    }
    // check for each type
    if (text.Mid(pos,2) == L"B]")
    { // bold - finish the current text block and assign the bold state
      newStyle = FONT_STYLE_BOLD;
      pos += 2;
    }
    else if (text.Mid(pos,2) == L"I]")
    { // italics
      newStyle = FONT_STYLE_ITALICS;
      pos += 2;
    }
    else if (text.Mid(pos,10) == L"UPPERCASE]")
    {
      newStyle = FONT_STYLE_UPPERCASE;
      pos += 10;
    }
    else if (text.Mid(pos,10) == L"LOWERCASE]")
    {
      newStyle = FONT_STYLE_LOWERCASE;
      pos += 10;
    }
    else if (text.Mid(pos,3) == L"CR]" && on)
    {
      newLine = true;
      pos += 3;
    }
    else if (text.Mid(pos,5) == L"COLOR")
    { // color
      size_t finish = text.Find(L']', pos + 5);
      if (on && finish != CStdString::npos)
      { // create new color
        newColor = colors.size();
        colors.push_back(g_colorManager.GetColor(text.Mid(pos + 5, finish - pos - 5)));
        colorStack.push(newColor);
      }
      else if (!on && finish == pos + 5)
      { // revert to previous color
        if (colorStack.size() > 1)
          colorStack.pop();
        newColor = colorStack.top();
      }
      pos = finish + 1;
    }

    if (newStyle || newColor != currentColor || newLine)
    { // we have a new style or a new color, so format up the previous segment
      CStdStringW subText = text.Mid(startPos, endPos - startPos);
      if (currentStyle & FONT_STYLE_UPPERCASE)
        subText.ToUpper();
      if (currentStyle & FONT_STYLE_LOWERCASE)
        subText.ToLower();
      AppendToUTF32(subText, ((currentStyle & 3) << 24) | (currentColor << 16), parsedText);
      if (newLine)
        parsedText.push_back(L'\n');

      // and switch to the new style
      startPos = pos;
      currentColor = newColor;
      if (on)
        currentStyle |= newStyle;
      else
        currentStyle &= ~newStyle;
    }
    pos = text.Find(L'[',pos);
  }
  // now grab the remainder of the string
  CStdStringW subText = text.Mid(startPos, text.GetLength() - startPos);
  if (currentStyle & FONT_STYLE_UPPERCASE)
    subText.ToUpper();
  if (currentStyle & FONT_STYLE_LOWERCASE)
    subText.ToLower();
  AppendToUTF32(subText, ((currentStyle & 3) << 24) | (currentColor << 16), parsedText);
}