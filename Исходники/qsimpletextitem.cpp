QSimpleTextItem* QSimpleTextItem::Clone()
{
    QSimpleTextItem *pClone = new QSimpleTextItem(this->sceneBoundingRect(),this->GetText());
    //QSimpleTextItem *pClone = new QSimpleTextItem(this->boundingRect(),this->GetText());
    if (!pClone)
    {
        return NULL;
    }

    pClone->SetFontColor(this->GetFontColor());
    pClone->SetRectOutLineColor(this->GetRectOutLineColor());
    pClone->SetRectBackColor(this->GetRectBackColor());
    pClone->SetRectFrontColor(this->GetRectFrontColor());
    pClone->SetFontSize(this->GetFontSize());
    pClone->SetFontName(this->GetFontName());
    pClone->SetFontBold(this->GetFontBold());
    pClone->SetFontItalic(this->GetFontItalic());
    pClone->SetFontUnderLine(this->GetFontUnderLine());
    pClone->SetFontWordInterval(this->GetFontWordInterval());
    pClone->SetRectOutLine(this->GetRectOutLine());
    pClone->SetLineInterval(this->GetLineInterval());
    pClone->setFlag(QGraphicsItem::ItemIsSelectable, true);
    pClone->setFlag(QGraphicsItem::ItemIsMovable, true);
    pClone->SetName(this->GetName());
    pClone->SetText(this->GetText());
    pClone->SetTextAlign(this->GetTextAlign());

    pClone->setVisible(this->isVisible());
    pClone->SetPattern(this->GetPattern());
    pClone->bFitSize = bFitSize;
    pClone->setId(id());

    // pClone->setRect(this->sceneBoundingRect());
    return pClone;
}