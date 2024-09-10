/*!
*	\en
*	Gets name for new template. Need for OpenOffice v2.
*	\_en
*	\ru
*	Получение имени для нового шаблона. Нужна из-за блокировок в OpenOffice v2.
*	\_ru
*/
QString
aReport::getName4NewTemplate()
{
	uint count=0;
	QFile tmpf;
	QString suff = ".odt";
	QString fname;
	if(type==RT_office_calc) suff = ".ods";
	if(type==RT_msoffice_word || type==RT_msoffice_excel) suff = ".xml";
	do
	{
		// tpl->getDir() должно заканчиваться на /
		fname =  QDir::convertSeparators(QString(tpl->getDir()+".ananas-report%1%2").arg(count).arg(suff));
		tmpf.setName(fname);
		if(tmpf.exists())
		{
			if(tmpf.remove()) break;
			else ++count;
		}
		else
		{
			break;
		}
	}while(count<100);

	aLog::print(aLog::MT_DEBUG, tr("aReport: name for template = %1").arg(fname));
	return fname;
}