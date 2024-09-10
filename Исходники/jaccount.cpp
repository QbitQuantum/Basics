JAccount::JAccount(const QString &id) :
	Account(id, JProtocol::instance()),
	d_ptr(new JAccountPrivate(this))
{
	Q_D(JAccount);
	d->client.reset(new Client(id));
	connect(d->client.data(), SIGNAL(disconnected(Jreen::Client::DisconnectReason)),
			this, SLOT(_q_disconnected(Jreen::Client::DisconnectReason)));
	connect(d->client.data(), SIGNAL(serverFeaturesReceived(QSet<QString>)),
			this ,SLOT(_q_init_extensions(QSet<QString>)));

	d->loadedModules = 0;
	d->privacyManager = new PrivacyManager(d->client.data());
	d->pubSubManager = new Jreen::PubSub::Manager(d->client.data());
	d->privateXml = new Jreen::PrivateXml(d->client.data());
	d->roster = new JRoster(this);
	Jreen::Capabilities::Ptr caps = d->client->presence().payload<Jreen::Capabilities>();
	caps->setNode(QLatin1String("http://qutim.org/"));
	d->conferenceManager = new JMUCManager(this, this);
	d->messageSessionManager = new JMessageSessionManager(this);
	connect(d->messageSessionManager, SIGNAL(messageEcnrypted(quint64)), SIGNAL(messageEcnrypted(quint64)));
	d->softwareDetection = new JSoftwareDetection(this);
	d->client->presence().addExtension(new VCardUpdate());

	Jreen::Disco *disco = d->client->disco();
	disco->setSoftwareVersion(QLatin1String("qutIM"),
							  versionString(),
							  SystemInfo::getFullName());

	disco->addIdentity(Jreen::Disco::Identity(QLatin1String("client"),
											  QLatin1String("type"),
											  QLatin1String("qutIM"),
											  QLatin1String("en")));
	QString qutim = tr("qutIM", "Local qutIM's name");
	QString lang = tr("en", "Default language");
	if(qutim != QLatin1String("qutIM") && lang != QLatin1String("en"))
		disco->addIdentity(Jreen::Disco::Identity(QLatin1String("client"), QLatin1String("type"),qutim,lang));
	
	connect(d->roster, SIGNAL(loaded()), &d->signalMapper, SLOT(map()));
	connect(d->privacyManager, SIGNAL(listsReceived()), &d->signalMapper, SLOT(map()));
	d->signalMapper.setMapping(d->roster, 1);
	d->signalMapper.setMapping(d->privacyManager, 2);
	connect(d->client.data(), SIGNAL(connected()), d->privacyManager, SLOT(request()));
	connect(&d->signalMapper, SIGNAL(mapped(int)), this, SLOT(_q_on_module_loaded(int)));
	
	d->roster->loadFromStorage();

	connect(d->conferenceManager.data(), SIGNAL(conferenceCreated(qutim_sdk_0_3::Conference*)),
			this, SIGNAL(conferenceCreated(qutim_sdk_0_3::Conference*)));

	foreach (const ObjectGenerator *gen, ObjectGenerator::module<JabberExtension>()) {
		if (JabberExtension *ext = gen->generate<JabberExtension>()) {
			d->extensions.append(ext);
			ext->init(this);
		}
	}

	{
		// Temporary hook
		// TODO: Remove this hook or make migration more automatic
		Config config = this->config(QStringLiteral("general"));
		const QString passwd = QStringLiteral("passwd");
		if (config.hasChildKey(passwd)) {
			d->keyChain->write(this, config.value(passwd, QString(), Config::Crypted));
			config.remove(passwd);
		}
	}
//	JPGPSupport::instance()->addAccount(this);
}