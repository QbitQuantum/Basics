ZDLAboutDialog::ZDLAboutDialog(ZDLWidget *parent):QDialog(parent){
	setWindowTitle("About "ZDL_ENGINE_NAME);
	QVBoxLayout *box = new QVBoxLayout(this);
	QHBoxLayout *hbox = new QHBoxLayout();
	box->addLayout(hbox);
	QVBoxLayout *vbox = new QVBoxLayout();
	QLabel *title = new QLabel(QString(ZDL_ENGINE_NAME)+" "+ZDL_VERSION_STRING,this);

	QFont font;
	font.setPointSize(24);
	title->setFont(font);
	title->setAlignment(Qt::AlignHCenter);

	vbox->addWidget(title);

#if defined(USE_BMP_LOGO)
	QLabel *pic = new QLabel(this);
	pic->setPixmap(QPixmap(aboutImg));
#else
	QLabel *pic = new QLabel(this);
	QPixmap map(":zdl3.svg");
	if(!map.isNull()){
	        pic->setPixmap(map);
	}else{
		pic->setPixmap(QPixmap(aboutImg));
	}
#endif

	hbox->addWidget(pic);
	hbox->addLayout(vbox);
	QFrame *hrTop = new QFrame(this);
	hrTop->setFrameStyle(QFrame::HLine);
	box->addWidget(hrTop);
	box->addWidget(new QLabel(QString("Source: ")+QString(ZDL_SOURCE),this));
	box->addWidget(new QLabel("Copyright (C) ZDL Software Foundation 2004-2012", this));
	QLabel *url = new QLabel("<a href=http://zdl.vectec.net>http://zdl.vectec.net</a>",this);
	url->setOpenExternalLinks(true);
	box->addWidget(url);
	box->addWidget(new QLabel(QString("Source: ")+QString(ZDL_SOURCE),this));	
	box->addWidget(new QLabel(QString("Build: ")+QString(ZDL_BUILD),this));
	box->addWidget(new QLabel(QString("Revision: ")+QString(ZDL_REVISION),this));
#if defined(ZDL_BUILD_NUMBER)
	if(ZDL_BUILD_NUMBER > 0){
		box->addWidget(new QLabel(QString("Build #: ")+QString::number(ZDL_BUILD_NUMBER),this));
	}
#endif
#if defined(ZDL_BUILD_JOB)
	box->addWidget(new QLabel(QString("Build job: ")+QString(ZDL_BUILD_JOB),this));
#endif
	QFrame *hrMid = new QFrame(this);
	hrMid->setFrameStyle(QFrame::HLine);
	box->addWidget(hrMid);
	
	box->addWidget(new QLabel("Special thanks to BioHazard for the original version",this));
	box->addWidget(new QLabel("Huge thanks to NeuralStunner.  Without his help, none of this would be possible.", this));
	box->addWidget(new QLabel("Special thanks to Blzut3, Risen, Enjay, DRDTeam.org, ZDoom.org",this));

	ZDLConfiguration *conf = ZDLConfigurationManager::getConfiguration();
	if(conf){
		QString systemConfPath = conf->getPath(ZDLConfiguration::CONF_SYSTEM);
		QString userConfPath = conf->getPath(ZDLConfiguration::CONF_USER);

		QFrame *hrBot = new QFrame(this);
		hrBot->setFrameStyle(QFrame::HLine);
		box->addWidget(hrBot);

		/*QLabel *systemConf = new QLabel("System Configuration File: "+systemConfPath,this);
		  systemConf->setTextInteractionFlags(Qt::TextSelectableByMouse);
		  box->addWidget(systemConf);*/

		QLabel *userConf = new QLabel("User Configuration File: "+userConfPath,this);
		userConf->setCursor(Qt::IBeamCursor);
		userConf->setTextInteractionFlags(Qt::TextSelectableByMouse);

		box->addWidget(userConf);
	}



	QDialogButtonBox *btnBox = new QDialogButtonBox(QDialogButtonBox::Ok,Qt::Horizontal,this);
	box->addWidget(btnBox);
	connect(btnBox, SIGNAL(accepted()), this, SLOT(close()));
}