void SunsetPluginSettingsPane::on_filenameInput_editingFinished ()
{
	QString filename=ui.filenameInput->text ().trimmed ();

	fileSpecified=false;
	fileResolved=false;
	fileExists=false;
	fileOk=false;

	referenceLongitude=Longitude ();

	if (!isBlank (filename))
	{
		fileSpecified=true;

		QString resolved=plugin->resolveFilename (filename, getEffectivePluginPaths ());

		if (!resolved.isEmpty ())
		{
			fileResolved=true;
			resolvedFilename=QFileInfo (resolved).absoluteFilePath ();

			if (QFile::exists (resolved))
			{
				fileExists=true;

				try
				{
					source=SunsetPluginBase::readSource (resolved);

					QString referenceLongitudeString=SunsetPluginBase::readReferenceLongitudeString (resolved);
					referenceLongitudeFound=!referenceLongitudeString.isEmpty ();
					referenceLongitude=Longitude::parse (referenceLongitudeString);

					fileOk=true;
				}
				catch (FileOpenError &ex)
				{
					fileError=ex.errorString;
				}
			}
		}
	}

	updateFilenameLabel ();
	updateSourceLabel ();
	updateReferenceLongitudeLabel ();
	updateReferenceLongitudeNoteLabel ();
}