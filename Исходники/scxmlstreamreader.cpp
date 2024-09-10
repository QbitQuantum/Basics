bool ScXmlStreamAttributes::valueAsBool (const QString& attrName, bool def) const
{
	bool retValue = def;
	QStringRef att = value(attrName);
	if (!att.isEmpty())
	{
		bool success = false;
		QString strVal = QString::fromRawData(att.constData(), att.length());
		int intVal = strVal.toInt(&success);
		if (success)
			retValue = static_cast<bool>(intVal);
	}
	return retValue;
}