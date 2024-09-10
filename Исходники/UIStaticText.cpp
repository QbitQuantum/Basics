YamlNode * UIStaticText::SaveToYamlNode(UIYamlLoader * loader)
{
    YamlNode *node = UIControl::SaveToYamlNode(loader);

    UIStaticText *baseControl = new UIStaticText();

    //Temp variable
    VariantType *nodeValue = new VariantType();

    //Font
    //Get font name and put it here
    nodeValue->SetString(FontManager::Instance()->GetFontName(this->GetFont()));
    node->Set("font", nodeValue);

    //TextColor
    const Color &textColor = GetTextColor();
    if (baseControl->GetTextColor() != textColor)
    {
        nodeValue->SetColor(textColor);
        node->Set("textcolor", nodeValue);
    }

    // Text Color Inherit Type.
    int32 colorInheritType = (int32)GetTextBackground()->GetColorInheritType();
    if (baseControl->GetTextBackground()->GetColorInheritType() != colorInheritType)
    {
        node->Set("textcolorInheritType", loader->GetColorInheritTypeNodeValue(colorInheritType));
    }

    // ShadowColor
    const Color &shadowColor = GetShadowColor();
    if (baseControl->GetShadowColor() != shadowColor)
    {
        nodeValue->SetColor(shadowColor);
        node->Set("shadowcolor", nodeValue);
    }

    // Shadow Color Inherit Type.
    colorInheritType = (int32)GetShadowBackground()->GetColorInheritType();
    if (baseControl->GetShadowBackground()->GetColorInheritType() != colorInheritType)
    {
        node->Set("shadowcolorInheritType", loader->GetColorInheritTypeNodeValue(colorInheritType));
    }

    // ShadowOffset
    const Vector2 &shadowOffset = GetShadowOffset();
    if (baseControl->GetShadowOffset() != shadowOffset)
    {
        nodeValue->SetVector2(shadowOffset);
        node->Set("shadowoffset", nodeValue);
    }

    //Text
    const WideString &text = GetText();
    if (baseControl->GetText() != text)
    {
        node->Set("text", text);
    }
    //Multiline
    if (baseControl->textBlock->GetMultiline() != this->textBlock->GetMultiline())
    {
        node->Set("multiline", this->textBlock->GetMultiline());
    }
    //multilineBySymbol
    if (baseControl->textBlock->GetMultilineBySymbol() != this->textBlock->GetMultilineBySymbol())
    {
        node->Set("multilineBySymbol", this->textBlock->GetMultilineBySymbol());
    }
    //fitting - Array of strings
    if (baseControl->textBlock->GetFittingOption() != this->textBlock->GetFittingOption())
    {
        node->SetNodeToMap("fitting", loader->GetFittingOptionNodeValue(textBlock->GetFittingOption()));
    }

    // Text Align
    if (baseControl->GetTextAlign() != this->GetTextAlign())
    {
        node->SetNodeToMap("textalign", loader->GetAlignNodeValue(this->GetTextAlign()));
    }

    // Draw type. Must be overriden for UITextControls.
    if (baseControl->GetBackground()->GetDrawType() != this->GetBackground()->GetDrawType())
    {
        node->Set("drawType", loader->GetDrawTypeNodeValue(this->GetBackground()->GetDrawType()));
    }

    SafeDelete(nodeValue);
    SafeRelease(baseControl);

    return node;
}