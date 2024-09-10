void RenderMathMLFraction::addChild(RenderObject* child, RenderObject* beforeChild)
{
    RenderBlock* row = new (renderArena()) RenderMathMLBlock(node());
    RefPtr<RenderStyle> rowStyle = makeBlockStyle();
    
    rowStyle->setTextAlign(CENTER);
    Length pad(static_cast<int>(rowStyle->fontSize() * gHorizontalPad), Fixed);
    rowStyle->setPaddingLeft(pad);
    rowStyle->setPaddingRight(pad);
    
    // Only add padding for rows as denominators
    bool isNumerator = isEmpty();
    if (!isNumerator) 
        rowStyle->setPaddingTop(Length(2, Fixed));
    
    row->setStyle(rowStyle.release());
    RenderBlock::addChild(row, beforeChild);
    row->addChild(child);
    updateFromElement();
}