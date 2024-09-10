/**
* \author Jules Gorny - ALCoV team, ISIT, UMR 6284 UdA – CNRS
**/
void writeXMLfromPatient(QString xmlPath, Patient* pat)
{
	QString tab = "    ";
	QFile file(xmlPath);
    file.open(QIODevice::WriteOnly | QIODevice::Text);
    QTextStream out(&file);

    out << "<Patient Id=\"" << pat->getId() << "\">\n";

	QVector<Property> propertiesPat = pat->getProperties();
	for(int p=0; p<propertiesPat.size(); p++)
	{
		Property prop = propertiesPat[p];
		out << tab << "<Property tag=\"" << prop.getTag() << "\" tagName=\"" << prop.getTagName() << "\" value=\"" << prop.getValue() << "\"/>\n";
	}

	QVector<Image*> imgs = pat->getImgs();
	for(int i=0; i<imgs.size(); i++)
	{
		Image* img = imgs[i];
		out << tab << "<" << img->getType() << ">\n";

		QVector<Study*> studies = img->getStudies();
		for(int st=0; st<studies.size(); st++)
		{
			Study* study = studies[st];
			out << tab << tab << "<Study description=\"" << study->getDescription() << "\">\n";

			QVector<Property> propertiesStud = study->getProperties();
			for(int p=0; p<propertiesStud.size(); p++)
			{
				Property prop = propertiesStud[p];
				out << tab << tab << tab << "<Property tag=\"" << prop.getTag() << "\" tagName=\"" << prop.getTagName() << "\" value=\"" << prop.getValue() << "\"/>\n";
			}

			QVector<Series*> series = study->getSeries();
			for(int se=0; se<series.size(); se++)
			{
				Series* serie = series[se];
				out << tab << tab << tab << "<Series description=\"" << serie->getDescription() << "\">\n";
				
				QVector<Property> propertiesSeries = serie->getProperties();
				for(int p=0; p<propertiesSeries.size(); p++)
				{
					Property prop = propertiesSeries[p];
					out << tab << tab << tab << tab << "<Property tag=\"" << prop.getTag() << "\" tagName=\"" << prop.getTagName() << "\" value=\"" << prop.getValue() << "\"/>\n";
				}

				QVector<Extract*> extracts = serie->getExtracts();
				for(int e=0; e<extracts.size(); e++)
				{
					Extract* extract = extracts[e];
					extract->fillFilesCommonProperty();
					out << tab << tab << tab << tab << "<Extract number=\"" << QString::number(extract->getNumber()) << "\">\n";

					QVector<Property> propertiesExtr = extract->getProperties();
					for(int p=0; p<propertiesExtr.size(); p++)
					{
						Property prop = propertiesExtr[p];
						out << tab << tab << tab << tab << tab << "<Property tag=\"" << prop.getTag() << "\" tagName=\"" << prop.getTagName() << "\" value=\"" << prop.getValue() << "\"/>\n";
					}

					QVector<File*> files = extract->getFiles();
					for(int f=0; f<files.size(); f++)
					{
						File* file = files[f];
						out << tab << tab << tab << tab << tab << "<File location=\"" << file->getPath() << "\">\n";

						QVector<Property> properties = file->getProperties();
						for(int p=0; p<properties.size(); p++)
						{
							Property prop = properties[p];
							out << tab << tab << tab << tab << tab << tab << "<Property tag=\"" << prop.getTag() << "\" tagName=\"" << prop.getTagName() << "\" value=\"" << prop.getValue() << "\"/>\n";
						}
						out << tab << tab << tab << tab << tab << "</File>\n";
					}
					out << tab << tab << tab << tab << "</Extract>\n";
				}
				out << tab << tab << tab << "</Series>\n";
			}
			out << tab << tab << "</Study>\n";
		}
		out << tab << "</" << img->getType() << ">\n";
	}
    out << "</Patient>";

    // optional, as QFile destructor will already do it:
    file.close(); 
}