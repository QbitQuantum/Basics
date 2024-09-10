void OptionSelectionMenu::Render(RenderDevice* prender, String title)
{
    // If we are invisible, render shortcut notifications.
    // Both child and parent have visible == true even if only child is shown.
    if (DisplayState == Display_None)
    {
        renderShortcutChangeMessage(prender);
        return;
    }

    title += Label;

    // Delegate to sub-menu if active.
    if (GetSubmenu() != NULL)
    {
        if (title.GetSize() > 0)
            title += " > ";

        GetSubmenu()->Render(prender, title);
        return;
    }

    Color focusColor(180, 80, 20, 210);
    Color pickedColor(120, 55, 10, 140);
    Color titleColor(0x18, 0x1A, 0x4D, 210);
    Color titleOutlineColor(0x18, 0x18, 0x18, 240);

    float    labelsSize[2]     = {0.0f, 0.0f};
    float    bufferSize[2]     = {0.0f, 0.0f};
    float    valuesSize[2]     = {0.0f, 0.0f};
    float    maxValueWidth     = 0.0f;

    UPInt    selection[2] = { 0, 0 };
    Vector2f labelSelectionRect[2];
    Vector2f valueSelectionRect[2];
    bool     havelLabelSelection = false;
    bool     haveValueSelection = false;

    float textSize = 22.0f;
    prender->MeasureText(&DejaVu, "      ", textSize, bufferSize);

    String values;
    String menuItems;

    int highlightIndex = 0;
    if (DisplayState == Display_Menu)
    {
        highlightIndex = SelectedIndex;
        for (UInt32 i = 0; i < Items.GetSize(); i++)
        {
            if (i > 0)
                values += "\n";
            values += Items[i]->GetValue();
        }

        for (UInt32 i = 0; i < Items.GetSize(); i++)
        {
            if (i > 0)
                menuItems += "\n";
            menuItems += Items[i]->GetLabel();
        }
    }
    else
    {
        values = Items[SelectedIndex]->GetValue();
        menuItems = Items[SelectedIndex]->GetLabel();
    }

    // Measure labels
    const char* menuItemsCStr = menuItems.ToCStr();
    havelLabelSelection = FindLineCharRange(menuItemsCStr, highlightIndex, selection);
    prender->MeasureText(&DejaVu, menuItemsCStr, textSize, labelsSize,
                         selection, labelSelectionRect);

    // Measure label-to-value gap
    const char* valuesCStr = values.ToCStr();
    haveValueSelection = FindLineCharRange(valuesCStr, highlightIndex, selection);
    prender->MeasureText(&DejaVu, valuesCStr, textSize, valuesSize, selection, valueSelectionRect);

    // Measure max value size (absolute size varies, so just use a reasonable max)
    maxValueWidth = prender->MeasureText(&DejaVu, "Max value width", textSize);
    maxValueWidth = Alg::Max(maxValueWidth, valuesSize[0]);

    Vector2f borderSize(4.0f, 4.0f);
    Vector2f totalDimensions = borderSize * 2 + Vector2f(bufferSize[0], 0) + Vector2f(maxValueWidth, 0)
                                + Vector2f(labelsSize[0], labelsSize[1]);
    
    Vector2f fudgeOffset= Vector2f(10.0f, 25.0f);  // This offset looks better
    Vector2f topLeft    = (-totalDimensions / 2.0f)  + fudgeOffset;    
    Vector2f bottomRight = topLeft + totalDimensions;

    // If displaying a single item, shift it down.
    if (DisplayState == Display_SingleItem)
    {
        topLeft.y     += textSize * 7;
        bottomRight.y += textSize * 7;
    }

    prender->FillRect(topLeft.x, topLeft.y, bottomRight.x, bottomRight.y, Color(40,40,100,210));

    Vector2f labelsPos = topLeft + borderSize;
    Vector2f valuesPos = labelsPos + Vector2f(labelsSize[0], 0) + Vector2f(bufferSize[0], 0);

    // Highlight selected label
    Vector2f selectionInset = Vector2f(0.3f, 2.0f);
    if (DisplayState == Display_Menu)
    {
        Vector2f labelSelectionTopLeft = labelsPos + labelSelectionRect[0] - selectionInset;
        Vector2f labelSelectionBottomRight = labelsPos + labelSelectionRect[1] + selectionInset;

        prender->FillRect(labelSelectionTopLeft.x, labelSelectionTopLeft.y,
                          labelSelectionBottomRight.x, labelSelectionBottomRight.y,
                          SelectionActive ? pickedColor : focusColor);
    }

    // Highlight selected value if active
    if (SelectionActive)
    {
        Vector2f valueSelectionTopLeft = valuesPos + valueSelectionRect[0] - selectionInset;
        Vector2f valueSelectionBottomRight = valuesPos + valueSelectionRect[1] + selectionInset;
        prender->FillRect(valueSelectionTopLeft.x, valueSelectionTopLeft.y,
                          valueSelectionBottomRight.x, valueSelectionBottomRight.y,
                          focusColor);
    }

    // Measure and draw title
    if (DisplayState == Display_Menu && title.GetLength() > 0)
    {
        Vector2f titleDimensions;
        prender->MeasureText(&DejaVu, title.ToCStr(), textSize, &titleDimensions.x);
        Vector2f titleTopLeft = topLeft - Vector2f(0, borderSize.y) * 2 - Vector2f(0, titleDimensions.y);
        titleDimensions.x = totalDimensions.x;
        
        prender->FillRect(titleTopLeft.x, titleTopLeft.y,
                          titleTopLeft.x + totalDimensions.x,
                          titleTopLeft.y + titleDimensions.y + borderSize.y * 2,
                          titleOutlineColor);
        
        prender->FillRect(titleTopLeft.x + borderSize.x / 2, titleTopLeft.y + borderSize.y / 2,
                          titleTopLeft.x + totalDimensions.x - borderSize.x / 2,
                          titleTopLeft.y + borderSize.y / 2 + titleDimensions.y,
                          titleColor);
                          
        prender->RenderText(&DejaVu, title.ToCStr(), titleTopLeft.x + borderSize.x,
                            titleTopLeft.y + borderSize.y, textSize, Color(255,255,0,210));
    }

    prender->RenderText(&DejaVu, menuItemsCStr, labelsPos.x, labelsPos.y, textSize, Color(255,255,0,210));

    prender->RenderText(&DejaVu, valuesCStr, valuesPos.x, valuesPos.y, textSize, Color(255,255,0,210));
}