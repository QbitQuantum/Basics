void CTile_browser_dlg::on_batchLoadPushButton_clicked()
{
	QFileDialog::Options options;
	QString selectedFilter;
	QString fileName = QFileDialog::getOpenFileName(this, tr("Choose Bitmap"), QString(tileBankBrowser.getAbsPath().c_str()) , tr("Targa Bitmap (*.tga);;PNG Image (*.png);;All Files (*.*);;"), &selectedFilter, options);
	QFileInfo fi(fileName);
	QString baseName = fi.baseName() ;


	if (!fileName.isEmpty())
	{
		QRegExp rx("\\d{2}$");
		baseName = baseName.remove(rx);
	
		
		//TODO titegus: What's the point in asking for rotation if Texture != Alpha ???
		bool rotate = (QMessageBox::Yes == QMessageBox::question(this, tr("Import rotated tiles"), tr("Do you want to use rotation to reuse alpha tiles?"), QMessageBox::Yes | QMessageBox::No ));

		for (int i=0; i<CTileSet::count; i++)
		{
			if (tileTextureButtonGroup->checkedId() == Alpha)
			{
				// Current transition
				CTileSet::TTransition transition=(CTileSet::TTransition)i;



				// Transition to patch
				CTileSetTransition* trans=tileBankBrowser.getTileSet (tileSetIndex)->getTransition (transition);
				if (tileBankBrowser.getTile (trans->getTile())->getRelativeFileName (CTile::alpha)=="")
				{
					// Continue ?
					int ok;

					// Try to load transition with rotation
					for (int rot=0; rot<4; rot++)
					{
						// Try to load a tile with a file name like /tiletransition0.tga
						QString transitionNumber = QString::number(transition);
						QString batchNumber = transitionNumber.rightJustified(2, '0');
						QString nextBaseName = baseName + batchNumber;
						QString nextFileName = QDir::toNativeSeparators(fi.absolutePath()) + QDir::separator() + nextBaseName + QString(".") + fi.suffix();
						FILE *pFile=fopen (nextFileName.toStdString().c_str(), "rb");

						// Close the file and add the tile if opened
						if (pFile)
						{
							fclose (pFile);
							ok=browserModel.setTileTransitionAlpha (i, nextFileName.toStdString().c_str(), (4-rot)%4);

							// End
							break;
						}

						// Rotate the transition
						transition=CTileSet::rotateTransition (transition);

						if (!rotate)
							break;
					}
					if (!ok)
						break;
				}
			}
			else
			{

				//TODO titegus: Check that, Batch Load seems useless
				// Current transition
				CTileSet::TTransition transition=(CTileSet::TTransition)i;

				// Transition to patch
				//CTileSetTransition* trans=tileBankBrowser.getTileSet (tileSetIndex)->getTransition (transition);
				//if (tileBankBrowser.getTile (trans->getTile())->getRelativeFileName ((CTile::TBitmap)tileTextureButtonGroup->checkedId())=="")
				//{
				//	// Try to load a tile with a file name like /tiletransition0.tga
				//	char sName2[256];
				//	char sFinal[256];
				//	sprintf (sName2, "%s%02d", sName, (int)transition);
				//	_makepath (sFinal, sDrive, sPath, sName2, sExt);
				//	FILE *pFile=fopen (sFinal, "rb");

				//	// Close the file and add the tile if opened
				//	if (pFile)
				//	{
				//		fclose (pFile);
				//		if (!infoList.setTileTransition (i, sFinal, (CTile::TBitmap) tileTextureButtonGroup->checkedId()))
				//			break;
				//	}
				//}
			}
		}
		

		LoadInThread();

	}
}