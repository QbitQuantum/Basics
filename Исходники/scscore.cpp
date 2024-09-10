static void addText(Score* score, int subtype, const QString& s)
{
    MeasureBase* measure = score->first();
    if (measure == 0 || measure->type() != VBOX) {
        score->insertMeasure(VBOX, measure);
        measure = score->first();
    }
    Text* text = new Text(score);
    switch(subtype) {
    case TEXT_TITLE:
        text->setTextStyleType(TEXT_STYLE_TITLE);
        break;
    case TEXT_SUBTITLE:
        text->setTextStyleType(TEXT_STYLE_SUBTITLE);
        break;
    case TEXT_COMPOSER:
        text->setTextStyleType(TEXT_STYLE_COMPOSER);
        break;
    case TEXT_POET:
        text->setTextStyleType(TEXT_STYLE_POET);
        break;
    }
    text->setParent(measure);
    text->setText(s);
    score->undoAddElement(text);
}