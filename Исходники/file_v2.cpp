void File_v2::loadIndicator(CrochetTab *tab, QXmlStreamReader *stream)
{
    Indicator *i = new Indicator();

    qreal x = 0, y = 0;
	bool fontused = false;
	int fontsize;
    QString textColor, bgColor, fontname;
    QString text, style;
	QPointF pivotScale, pivotRotation;
	QTransform transform;
    qreal   m11 = 1, m12 = 0, m13 = 0,
            m21 = 0, m22 = 1, m23 = 0,
            m31 = 0, m32 = 0, m33 = 1;
			
	qreal rotation = 0, scaleX = 1, scaleY = 1;
    int group = -1;
	unsigned int layer = 0;
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
        } else if(tag == "style") {
            style = stream->readElementText();
        } else if(tag == "group") {
            group = stream->readElementText().toInt();
        } else if (tag == "fontname") {
			fontname = stream->readElementText();
			fontused = true;
		} else if (tag == "fontsize") {
			fontsize = stream->readElementText().toInt();
			fontused = true;
		} else if (tag == "layer") {
			layer = stream->readElementText().toUInt();
			
		} else if (tag == "newscale") {
			scaleX = stream->attributes().value("scaleX").toString().toDouble();
			scaleY = stream->attributes().value("scaleY").toString().toDouble();
			pivotScale.rx() = stream->attributes().value("pivotX").toString().toDouble();
			pivotScale.ry() = stream->attributes().value("pivotY").toString().toDouble();
			stream->readElementText();
			
		} else if (tag == "rotation") {
			rotation = stream->attributes().value("rotation").toString().toDouble();
			pivotRotation.rx() = stream->attributes().value("pivotX").toString().toDouble();
			pivotRotation.ry() = stream->attributes().value("pivotY").toString().toDouble();
			stream->readElementText();
			
		}  else if(tag == "transformation") {
            m11 = stream->attributes().value("m11").toString().toDouble();
            m12 = stream->attributes().value("m12").toString().toDouble();
            m13 = stream->attributes().value("m13").toString().toDouble();
            m21 = stream->attributes().value("m21").toString().toDouble();
            m22 = stream->attributes().value("m22").toString().toDouble();
            m23 = stream->attributes().value("m23").toString().toDouble();
            m31 = stream->attributes().value("m31").toString().toDouble();
            m32 = stream->attributes().value("m32").toString().toDouble();
            m33 = stream->attributes().value("m33").toString().toDouble();
            stream->readElementText();
        } 
    }
	DEBUG("Style is: ");
	DEBUG(style);
	transform.setMatrix(m11, m12, m13, m21, m22, m23, m31, m32, m33);
    tab->scene()->addItem(i);
    i->setTransform(transform);
	ChartItemTools::setRotation(i, rotation);
	ChartItemTools::setScaleX(i, scaleX);
	ChartItemTools::setScaleY(i, scaleY);
	ChartItemTools::setRotationPivot(i, pivotRotation, false);
	ChartItemTools::setScalePivot(i, pivotScale, false);
    i->setPos(x,y);
	i->setText(text);
	qDebug() << "loading text " << text;
    i->setTextColor(textColor);
    i->setBgColor(bgColor);
	i->setLayer(layer);
	if (fontused)
		i->setFont(QFont(fontname, fontsize));
	
	ChartItemTools::recalculateTransformations(i);
	
    //i->setTextInteractionFlags(Qt::TextEditorInteraction);

    if(style.isEmpty())
        style = Settings::inst()->value("chartRowIndicator").toString();
    i->setStyle(style);

    if(group != -1) {
        tab->scene()->addToGroup(group, i);
		tab->scene()->getGroup(group)->setLayer(layer);
	}
}