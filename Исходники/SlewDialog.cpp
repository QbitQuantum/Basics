void SlewDialog::loadPointsFromFile()
{
	QVariantMap result;
	QString pointsJsonPath = StelFileMgr::findFile("modules/TelescopeControl", (StelFileMgr::Flags)(StelFileMgr::Directory|StelFileMgr::Writable)) + "/points.json";

	if (pointsJsonPath.isEmpty())
	{
		qWarning() << "SlewDialog: Error loading points";
		return;
	}
	if(!QFileInfo(pointsJsonPath).exists())
	{
		qWarning() << "SlewDialog::loadPointsFromFile(): No pointss loaded. File is missing:"
			   << QDir::toNativeSeparators(pointsJsonPath);
		storedPointsDescriptions = result;
		return;
	}

	QFile pointsJsonFile(pointsJsonPath);

	QVariantMap map;

	if(!pointsJsonFile.open(QFile::ReadOnly))
	{
		qWarning() << "SlewDialog: No points loaded. Can't open for reading"
			   << QDir::toNativeSeparators(pointsJsonPath);
		storedPointsDescriptions = result;
		return;
	}
	else
	{
		map = StelJsonParser::parse(&pointsJsonFile).toMap();
		pointsJsonFile.close();
	}

	//File contains any points?
	if(map.isEmpty())
	{
		storedPointsDescriptions = result;
		return;
	}

	QString version = map.value("version", "0.0.0").toString();
	if(version < QString(TELESCOPE_CONTROL_VERSION))
	{
		QString newName = pointsJsonPath + ".backup." + QDateTime::currentDateTime().toString("yyyy-MM-dd-hh-mm-ss");
		if(pointsJsonFile.rename(newName))
		{
			qWarning() << "SlewDialog: The existing version of points.json is obsolete. Backing it up as "
				   << QDir::toNativeSeparators(newName);
			qWarning() << "SlewDialog: A blank points.json file will have to be created.";
			storedPointsDescriptions = result;
			return;
		}
		else
		{
			qWarning() << "SlewDialog: The existing version of points.json is obsolete. Unable to rename.";
			storedPointsDescriptions = result;
			return;
		}
	}
	map.remove("version");//Otherwise it will try to read it as a point

	//Read pointss, if any
	QMapIterator<QString, QVariant> node(map);

	if(node.hasNext())
	{
		ui->comboBoxStoredPoints->addItem(q_("Select one"));
		do
		{
			node.next();

			QVariantMap point = node.value().toMap();
			storedPoint sp;
			sp.name       = point.value("name").toString();
			sp.number     = point.value("number").toInt();
			sp.radiansRA  = point.value("radiansRA").toDouble();
			sp.radiansDec = point.value("radiansDec").toDouble();

			QVariant var;
			var.setValue(sp);
			ui->comboBoxStoredPoints->addItem(sp.name,var);
		} while (node.hasNext());
	}
}