std::string
PyFontAttributes_ToString(const FontAttributes *atts, const char *prefix)
{
    std::string str;
    char tmpStr[1000];

    const char *font_names = "Arial, Courier, Times";
    switch (atts->GetFont())
    {
      case FontAttributes::Arial:
          SNPRINTF(tmpStr, 1000, "%sfont = %sArial  # %s\n", prefix, prefix, font_names);
          str += tmpStr;
          break;
      case FontAttributes::Courier:
          SNPRINTF(tmpStr, 1000, "%sfont = %sCourier  # %s\n", prefix, prefix, font_names);
          str += tmpStr;
          break;
      case FontAttributes::Times:
          SNPRINTF(tmpStr, 1000, "%sfont = %sTimes  # %s\n", prefix, prefix, font_names);
          str += tmpStr;
          break;
      default:
          break;
    }

    SNPRINTF(tmpStr, 1000, "%sscale = %g\n", prefix, atts->GetScale());
    str += tmpStr;
    if(atts->GetUseForegroundColor())
        SNPRINTF(tmpStr, 1000, "%suseForegroundColor = 1\n", prefix);
    else
        SNPRINTF(tmpStr, 1000, "%suseForegroundColor = 0\n", prefix);
    str += tmpStr;
    const unsigned char *color = atts->GetColor().GetColor();
    SNPRINTF(tmpStr, 1000, "%scolor = (%d, %d, %d, %d)\n", prefix, int(color[0]), int(color[1]), int(color[2]), int(color[3]));
    str += tmpStr;
    if(atts->GetBold())
        SNPRINTF(tmpStr, 1000, "%sbold = 1\n", prefix);
    else
        SNPRINTF(tmpStr, 1000, "%sbold = 0\n", prefix);
    str += tmpStr;
    if(atts->GetItalic())
        SNPRINTF(tmpStr, 1000, "%sitalic = 1\n", prefix);
    else
        SNPRINTF(tmpStr, 1000, "%sitalic = 0\n", prefix);
    str += tmpStr;
    return str;
}