int ShibeTranslator::saveToFile(const QString &fileName)
{
	QStringList resultList;
	resultList.append(getMapList(&buttonMap,"Button_"));
	resultList.append(getMapList(&labelMap,"Label_"));
	resultList.append(getMapList(&checkBoxMap,"CheckBox_"));
	resultList.append(getMapList(&groupBoxMap,"GroupBox_"));
	resultList.append(getMapList(&spinBoxMap,"SpinBox_"));
	resultList.append(getMapList(&stringMap,"String_"));
	if(resultList.isEmpty())return 1;
	resultList.sort();
	QFile writeFile(fileName);
	if(writeFile.open(QIODevice::WriteOnly|QIODevice::Truncate))
	{
		writeFile.write(QString(resultList.join("\r\n")+"\r\n").toUtf8());
		writeFile.close();
		return 0;
	}
	return 2;
}