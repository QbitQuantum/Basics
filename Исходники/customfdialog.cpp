void FDialogPreview::GenPreview(QString name)
{
	QPixmap pm;
	QString Buffer = "";
	updtPix();
	if (name.isEmpty())
		return;
	QFileInfo fi = QFileInfo(name);
	if (fi.isDir())
		return;
	int w = pixmap()->width();
	int h = pixmap()->height();
	bool mode = false;
	QString ext = fi.suffix().toLower();
	QString formatD(FormatsManager::instance()->extensionListForFormat(FormatsManager::IMAGESIMGFRAME, 1));
 	QStringList formats = formatD.split("|");
	formats.append("pat");
	formats.removeAll("pdf");
	
	QStringList allFormatsV = LoadSavePlugin::getExtensionsForPreview(FORMATID_FIRSTUSER);
	if (ext.isEmpty())
		ext = getImageType(name);
	if (formats.contains(ext.toUtf8()))
	{
		ScImage im;
		//No doc to send data anyway, so no doc to get into scimage.
		CMSettings cms(0, "", Intent_Perceptual);
		cms.allowColorManagement(false);
		if (im.loadPicture(name, 1, cms, ScImage::Thumbnail, 72, &mode))
		{
			int ix,iy;
			if ((im.imgInfo.exifDataValid) && (!im.imgInfo.exifInfo.thumbnail.isNull()))
			{
				ix = im.imgInfo.exifInfo.width;
				iy = im.imgInfo.exifInfo.height;
			}
			else
			{
				ix = im.width();
				iy = im.height();
			}
			int xres = im.imgInfo.xres;
			int yres = im.imgInfo.yres;
			QString tmp = "";
			QString tmp2 = "";
			QImage im2 = im.scaled(w - 5, h - 44, Qt::KeepAspectRatio, Qt::SmoothTransformation);
			QPainter p;
			QBrush b(QColor(205,205,205), IconManager::instance()->loadPixmap("testfill.png"));
			// Qt4 FIXME imho should be better
			pm = *pixmap();
			p.begin(&pm);
			p.fillRect(0, 0, w, h-44, b);
			p.fillRect(0, h-44, w, 44, QColor(255, 255, 255));
			p.drawImage((w - im2.width()) / 2, (h - 44 - im2.height()) / 2, im2);
			p.drawText(2, h-29, tr("Size:")+" "+tmp.setNum(ix)+" x "+tmp2.setNum(iy));
			if (!(extensionIndicatesPDF(ext) || extensionIndicatesEPSorPS(ext)))
				p.drawText(2, h-17, tr("Resolution:")+" "+tmp.setNum(xres)+" x "+tmp2.setNum(yres)+" "+ tr("DPI"));
			QString cSpace;
			if ((extensionIndicatesPDF(ext) || extensionIndicatesEPSorPS(ext)) && (im.imgInfo.type != ImageType7))
				cSpace = tr("Unknown");
			else
				cSpace=colorSpaceText(im.imgInfo.colorspace);
			p.drawText(2, h-5, tr("Colorspace:")+" "+cSpace);
			p.end();
			setPixmap(pm);
			repaint();
		}
	}
	else if (allFormatsV.contains(ext.toUtf8()))
	{
		FileLoader *fileLoader = new FileLoader(name);
		int testResult = fileLoader->testFile();
		delete fileLoader;
		if ((testResult != -1) && (testResult >= FORMATID_FIRSTUSER))
		{
			const FileFormat * fmt = LoadSavePlugin::getFormatById(testResult);
			if( fmt )
			{
				QImage im = fmt->readThumbnail(name);
				if (!im.isNull())
				{
					QString desc = tr("Size:")+" ";
					desc += value2String(im.text("XSize").toDouble(), PrefsManager::instance()->appPrefs.docSetupPrefs.docUnitIndex, true, true);
					desc += " x ";
					desc += value2String(im.text("YSize").toDouble(), PrefsManager::instance()->appPrefs.docSetupPrefs.docUnitIndex, true, true);
					im = im.scaled(w - 5, h - 21, Qt::KeepAspectRatio, Qt::SmoothTransformation);
					QPainter p;
					QBrush b(QColor(205,205,205), IconManager::instance()->loadPixmap("testfill.png"));
					pm = *pixmap();
					p.begin(&pm);
					p.fillRect(0, 0, w, h-21, b);
					p.fillRect(0, h-21, w, 21, QColor(255, 255, 255));
					p.drawImage((w - im.width()) / 2, (h - 21 - im.height()) / 2, im);
					p.drawText(2, h-5, desc);
					p.end();
					setPixmap(pm);
					repaint();
				}
			}
		}
	}
	else if (ext.toUtf8() == "sce")
	{
		QByteArray cf;
		if (loadRawText(name, cf))
		{
			QString f;
			if (cf.left(16) == "<SCRIBUSELEMUTF8")
				f = QString::fromUtf8(cf.data());
			else
				f = cf.data();
			ScPreview *pre = new ScPreview();
			QImage im = pre->createPreview(f);
			im = im.scaled(w - 5, h - 21, Qt::KeepAspectRatio, Qt::SmoothTransformation);
			QPainter p;
			QBrush b(QColor(205,205,205), IconManager::instance()->loadPixmap("testfill.png"));
			pm = *pixmap();
			p.begin(&pm);
			p.fillRect(0, 0, w, h-21, b);
			p.fillRect(0, h-21, w, 21, QColor(255, 255, 255));
			p.drawImage((w - im.width()) / 2, (h - 21 - im.height()) / 2, im);
			QString desc = tr("Size:")+QString(" %1 x %2").arg(im.width()).arg(im.height());
			p.drawText(2, h-5, desc);
			p.end();
			setPixmap(pm);
			repaint();
			delete pre;
		}
	}
	else
	{
		ScSlaInfoReader slaInfos;
		if (slaInfos.readInfos(name))
		{
			QString Title = tr("Title:")+" ";
			QString ti2 = slaInfos.title();
			if (ti2.isEmpty())
				ti2= tr("No Title");
			Title += ti2+"\n";
			QString Author = tr("Author:")+" ";
			QString au2 = slaInfos.author();
			if (au2.isEmpty())
				au2 = tr("Unknown");
			Author += au2+"\n";
			QString Format =  tr("File Format:")+" ";
			QString fm2 = slaInfos.format();
			if (fm2.isEmpty())
				fm2 = tr("Unknown");
			Format += fm2;
			setText( tr("Scribus Document")+"\n\n"+Title+Author+Format);
		}
		else  if ((ext == "txt") || (ext == "html") || (ext == "xml"))
		{
			if (loadText(name, &Buffer))
				setText(Buffer.left(200));
		}
	}
}