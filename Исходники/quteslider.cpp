QString QuteSlider::getWidgetXmlText()
{
	xmlText = "";
	QXmlStreamWriter s(&xmlText);
	createXmlWriter(s);

#ifdef  USE_WIDGET_MUTEX
	widgetLock.lockForWrite();
#endif
	s.writeTextElement("minimum", QString::number(property("QCS_minimum").toDouble(), 'f', 8));
	s.writeTextElement("maximum", QString::number(property("QCS_maximum").toDouble(), 'f', 8));
	s.writeTextElement("value", QString::number(m_value, 'f', 8));
	s.writeTextElement("mode", property("QCS_mode").toString());

	s.writeStartElement("mouseControl");
	s.writeAttribute("act", property("QCS_mouseControlAct").toString());
	s.writeCharacters(property("QCS_mouseControl").toString());
	s.writeEndElement();
	s.writeTextElement("resolution", QString::number(property("QCS_resolution").toDouble(), 'f', 8));
	s.writeStartElement("randomizable");
	s.writeAttribute("group", QString::number(property("QCS_randomizableGroup").toInt()));
	s.writeCharacters(property("QCS_randomizable").toBool() ? "true": "false");
	s.writeEndElement();

	s.writeEndElement();
#ifdef  USE_WIDGET_MUTEX
	widgetLock.unlock();
#endif
	return xmlText;
}