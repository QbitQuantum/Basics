	void Plugin::genQR ()
	{
		const auto& url = sender ()->property ("Poshuku/QRd/URL").toUrl ();

		const std::unique_ptr<QRcode, decltype (&QRcode_free)> code
		{
			QRcode_encodeString (url.toEncoded ().constData (),
					0, QR_ECLEVEL_H, QR_MODE_8, true),
			&QRcode_free
		};

		if (!code)
		{
			QMessageBox::critical (nullptr,
					"LeechCraft",
					tr ("Failed to generate QR code for the page."));
			return;
		}

		const auto width = code->width;
		QImage image { width, width, QImage::Format_Mono };
		image.setColor (0, QColor { Qt::white }.rgb ());
		image.setColor (1, QColor { Qt::black }.rgb ());
		for (int y = 0; y < width; ++y)
			for (int x = 0; x < width; ++x)
				image.setPixel (x, y, code->data [y * width + x] & 0x01);

		const auto& geom = QApplication::desktop ()->availableGeometry (QCursor::pos ());
		const auto& dim = std::min (geom.width (), geom.height ());
		if (dim < width)
		{
			QMessageBox::critical (nullptr,
					"LeechCraft",
					tr ("Sorry, but the QR code is bigger than your display."));
			return;
		}

		auto scale = (width < 2.0 * dim / 3) ? (2.0 * dim / 3 / width) : dim / width;
		if (scale > 1)
			image = image.scaled (width * scale, width * scale, Qt::KeepAspectRatio, Qt::FastTransformation);

		auto label = new QLabel;
		label->setAttribute (Qt::WA_DeleteOnClose);
		label->setPixmap (QPixmap::fromImage (image));
		label->show ();
	}