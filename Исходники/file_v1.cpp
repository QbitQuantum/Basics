void File_v1::loadIndicator(CrochetTab *tab, QXmlStreamReader *stream)
{
    Indicator *i = new Indicator();

    qreal x = 0, y = 0;
    QString textColor, bgColor;
    QString text;

    while(!(stream->isEndElement() && stream->name() == "indicator")) {
        stream->readNext();
        QString tag = stream->name().toString();

        if(tag == "x") {
            x = stream->readElementText().toDouble();
        } else if(tag == "y") {
            y = stream->readElementText().toDouble();
        } else if(tag == "text") {
            text = stream->readElementText();
			//the text might be html formatted in old saves, so we need to strip it. A regex could work,
			//but is hard to make performant with inline css, and wouldn't work well with text that has
			//brackets in it.
			QTextDocument doc;
			doc.setHtml( text );
			text = doc.toPlainText();
        } else if(tag == "textColor") {
            textColor = stream->readElementText();
        } else if(tag == "bgColor") {
            bgColor = stream->readElementText();
        }
    }

    tab->scene()->addItem(i);
    i->setPos(x,y);
    i->setText(text);
    i->setTextColor(textColor);
    i->setBgColor(bgColor);
	ChartItemTools::recalculateTransformations(i);
}