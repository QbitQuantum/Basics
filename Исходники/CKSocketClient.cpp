void CKSocketClient::playMessage(const QString &message) {
	ostringstream os;
	os << message.toStdString() << endl;
	ColorKeeperModel::logMessage(os.str());
	if (message.compare(QString("GET_SCREEN_INFO")) == 0) {
		try {
			const DisplayDevice
					& currScreen =
							ColorKeeperModel::Instance().getDeviceInfo().getCalibrableDisplayDevice(
									_currentScreen);
			ColorKeeperModel::Instance().addCalibModelForScreen(_currentScreen);
			QString sendMessage("SCREEN_INFO_ [index]");

			sendMessage.append(currScreen.getOSIndex());
			sendMessage.append(";[uid]");
			sendMessage.append(currScreen.getFullSerialNumber().c_str());
			sendMessage.append(";[manufacturer]");
			sendMessage.append(currScreen.getManufacturerName().c_str());
			sendMessage.append(";[model]");
			sendMessage.append(currScreen.getModelName().c_str());
			sendMessage.append(";[type]");
			sendMessage.append(currScreen.getStringType().c_str());
			sendMessage.append(";[profil]");
			sendMessage.append(
					ColorKeeperModel::Instance().getScreenProfilName(
							currScreen.getOSIndex()).c_str());
			sendMessage.append("\n");
			writeSocket(sendMessage);

		} catch (std::string e) { //TODO exception
			QString sendMessage = "Error";
			writeSocket(sendMessage);
		}
	} else if (message.contains(QString("DISPLAY_LUM_PATT")) == true) {
		QString m = message;
		m.remove(QString("DISPLAY_LUM_PATT "));
		QChar sc = m[0];
		m.remove(sc);
		int screen = sc.digitValue();
		float gamma = m.toFloat();

		emit displayLumContPatt(gamma, screen, false);
	} else if (message.contains(QString("SET_LUT_ON")) == true) {
		QChar sc = message[11];
		int screen = sc.digitValue();
		ColorKeeperModel::Instance().setScreenShouldApplyCorrection(screen,
				true);
	} else if (message.contains(QString("SET_LUT_OFF")) == true) {
		QChar sc = message[12];
		int screen = sc.digitValue();
		ColorKeeperModel::Instance().setScreenShouldApplyCorrection(screen,
				false);

	} else if (message.contains(QString("UNSET_MOSAIC")) == true) {
		QChar sc = message[13];
		int screen = sc.digitValue();
		emit displayLumContPatt(-1, screen, false);
	} else if (message.contains(QString("SET_MOSAIC")) == true) {
		QChar sc = message[11];
		int screen = sc.digitValue();
		emit displayLumContPatt(-1, screen, true);
	} else if (message.contains(QString("SET_PATCH_COLOR")) == true) {
		QChar sc = message[16];
		int screen = sc.digitValue();
		QStringList list = message.split(QChar('-'));
		QStringList::Iterator it = list.begin() + 1;
		QString tmp = (*it);
		float r = tmp.toFloat() / 255.f;
		++it;
		tmp = (*it);
		float g = tmp.toFloat() / 255.f;
		++it;
		tmp = (*it);
		float b = tmp.toFloat() / 255.f;
		++it;
		tmp = (*it);
		QChar halo = tmp[0];
		bool drawHalo = false;
		if (halo == QChar('t')) {
			drawHalo = true;
		}

		emit displayPatch(screen, r, g, b, drawHalo);
		QString sendMessage("PATCH_OK\n");
		writeSocket(sendMessage);
	} else if (message.contains(QString("SET_REC_COLOR")) == true) {
		QChar sc = message[14];
		int screen = sc.digitValue();
		QStringList list = message.split(QChar('-'));
		QStringList::Iterator it = list.begin() + 1;
		QString tmp = (*it);
		float r = tmp.toFloat() / 255.f;
		++it;
		tmp = (*it);
		float g = tmp.toFloat() / 255.f;
		++it;
		tmp = (*it);
		float b = tmp.toFloat() / 255.f;
		++it;
		tmp = (*it);
		emit displayFullScreenRec(screen, r, g, b);
		QString sendMessage("REC_OK\n");
		writeSocket(sendMessage);
	} else if (message.contains(QString("SET_LUT_SIZE")) == true) {
		QChar sc = message[13];
		int screen = sc.digitValue();
		QStringList list = message.split(QChar('-'));
		QStringList::Iterator it = list.begin() + 1;
		QString tmp = (*it);
		unsigned int size = tmp.toInt();
		ColorKeeperModel::Instance().setCalibSizeForScreen(screen, size);
		QString sendMessage("SET_LUT_SIZE_OK\n");
		writeSocket(sendMessage);
	} else if (message.contains(QString("VALUE")) == true) {
		QChar sc = message[6];
		int screen = sc.digitValue();
		QStringList list = message.split(QChar('-'));
		QStringList::Iterator it = list.begin() + 1;
		QString tmp = (*it);
		unsigned short red = tmp.toInt();
		++it;
		tmp = (*it);
		unsigned short green = tmp.toInt();
		++it;
		tmp = (*it);
		unsigned short blue = tmp.toInt();
		ostringstream os;
		os << (int) red << (int) green << (int) blue << endl;
		ColorKeeperModel::logMessage(os.str());
		ColorKeeperModel::Instance().addCalibValueForScreen(screen, red, green,
				blue);
	} else if (message.contains(QString("SET_LUT_DONE")) == true) {
		//		QString sendMessage("SET_LUT_OK\n");
		//		writeSocket(sendMessage);
		QChar sc = message[13];
		int screen = sc.digitValue();
		ColorKeeperModel::Instance().setCalibDoneForScreen(screen);

	} else if (message.contains(QString("SHOULD_DISPLAY")) == true) {
		QChar sc = message[15];
		int screen = sc.digitValue();
		QChar va = message[17];
		bool tog = false;
		if (va == QChar('t')) {
			tog = true;
		}
		ColorKeeperModel::Instance().shoudDisplayCalibForScreen(screen, tog);
	} else if (message.contains(QString("UPDATE_CALIB_FILE")) == true) {
		QChar sc = message[18];
		int screen = sc.digitValue();
		QString infos = message;
		infos.remove(0, 19);
		infos.replace(QChar('#'), QChar('\n'));
		ColorKeeperModel::Instance().updateCorrection(screen, infos);
		QString sendMessage("UPDATE_OK\n");
		writeSocket(sendMessage);
	} else if (message.contains(QString("BUH_BYE")) == true) {
		QChar sc = message[8];
		int screen = sc.digitValue();
		ColorKeeperModel::Instance().endCalib(screen);
	}
}