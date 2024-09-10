Keyswitch::Keyswitch(XKeyboard *keyboard, QWidget *parent) : QLabel(parent)
{
	keys=keyboard;
	QSettings * antico = new QSettings(QCoreApplication::applicationDirPath() + "/antico.cfg", QSettings::IniFormat, this);
	antico->beginGroup("Style");
	map_path = antico->value("path").toString()+"/language/";
	antico->endGroup(); //Style
	xkbConf = X11tools::loadXKBconf();
	if (xkbConf->status!=DONT_USE_XKB) {
		load_rules();
		qDebug()<<"XKB status : " <<xkbConf->status;
		if (xkbConf->status==USE_XKB)
			set_xkb();
		init();
		if (groupeName.count()>1 || xkbConf->showSingle) {
			draw_icon();
			createMenu();
		}
	}

}