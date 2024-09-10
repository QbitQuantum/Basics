QString QuteComboBox::getWidgetXmlText()
{
	xmlText = "";
	QXmlStreamWriter s(&xmlText);
	createXmlWriter(s);

#ifdef  USE_WIDGET_MUTEX
	widgetLock.lockForRead();
#endif

	s.writeStartElement("bsbDropdownItemList");
	for (int i = 0; i < static_cast<QComboBox *>(m_widget)->count(); i++) {
		s.writeStartElement("bsbDropdownItem");
		s.writeTextElement("name", static_cast<QComboBox *>(m_widget)->itemText(i));
		s.writeTextElement("value", QString::number(static_cast<QComboBox *>(m_widget)->itemData(i).toInt()) );
		s.writeTextElement("stringvalue", stringValues[i]);
		s.writeEndElement();
	}
	s.writeEndElement();
	s.writeTextElement("selectedIndex", QString::number(((QComboBox *)m_widget)->currentIndex()));
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