void FaceTrackNoIR::saveAs()
{
    looping++;
	QSettings settings("opentrack");
	QString oldFile = settings.value ( "SettingsFile", QCoreApplication::applicationDirPath() + "/settings/default.ini" ).toString();

	QString fileName = QFileDialog::getSaveFileName(this, tr("Save file"),
													oldFile,
                                                    tr("Settings file (*.ini);;All Files (*)"));
	if (!fileName.isEmpty()) {

		QFileInfo newFileInfo ( fileName );
		if ((newFileInfo.exists()) && (oldFile != fileName)) {
			QFile newFileFile ( fileName );
			newFileFile.remove();
		}

		QFileInfo oldFileInfo ( oldFile );
		if (oldFileInfo.exists()) {
			QFile oldFileFile ( oldFile );
			oldFileFile.copy( fileName );
		}

		settings.setValue ("SettingsFile", fileName);
        save();
    }

    looping--;
    fill_profile_cbx();
}