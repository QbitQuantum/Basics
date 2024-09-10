/*
 * 	LoadData class constuctor
 * 	Inputs: parent, QString fileInput
 * 	Constructor takes in a route number as fileInput, such as fileInput = 10
 *	and looks for a file with name route10.xml. If it's not found, it lets caller
 *	know to create it, and if it is found it loads up specified station and time info.
 */
LoadData::LoadData(QObject* parent, QString fileInput) {
	buses.clear();
	stations.clear();
	failFlag = false; //Fail flag set to true if file is not found
	QString fileName = "route" + fileInput + ".xml";
	//Open file in specified folder with inputted file name
	QString appFolder(QDir::currentPath());
	QString fileExtension = appFolder + "/app/native/assets/schedule/"
			+ fileName;
	QFile *file = new QFile(fileExtension);

	if (!file->open(QIODevice::ReadOnly | QIODevice::Text)) {
		//qDebug() << "Failed to open " + fileName;
		//Now download file...
		failFlag = true;
		return;
	}
	qDebug() << "Start load data: " + fileName;
	QDomDocument doc("route"); //Get the root node, route
	QString bl = "h";
	QString *errorMsg = &bl;
	//If the xml file is corrupted & doesn't have root node "route", then redownload file.
	if (!doc.setContent(file, true, errorMsg)) {
		////qDebug() << "I failed to open " + fileName;
		file->close();
		//Delete file, redownload
		file->remove();
		failFlag = true;
		return;
	}
	file->close();
	root = doc.documentElement(); //Setup root node

}