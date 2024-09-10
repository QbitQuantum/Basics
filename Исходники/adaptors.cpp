        InstanceAdaptor::InstanceAdaptor(AbstractPlugin *p_plgn) : Adaptor(Core::instance ()) {
            if (p_plgn == NULL){
                emit pluginCantLoad (Core::arguments ()->value ("plugin").toString ());
                QApplication::quit ();
            } else {
                connect(QApplication::instance (),SIGNAL(aboutToQuit()),this,SIGNAL(aboutToQuit()));
                QDBusConnection::sessionBus ().connect ("org.thesii.Wintermute","/Factory",
                                                        "org.thesii.Wintermute.Factory","pluginCantLoad",
                                                        this,SIGNAL(pluginCantLoad(QString)));
                QDBusConnection::sessionBus ().connect ("org.thesii.Wintermute","/Factory",
                                                        "org.thesii.Wintermute.Factory","pluginLoaded",
                                                        this,SIGNAL(pluginLoaded(QString)));
                QDBusConnection::sessionBus ().connect ("org.thesii.Wintermute","/Factory",
                                                        "org.thesii.Wintermute.Factory","pluginUnloaded",
                                                        this,SIGNAL(pluginUnloaded(QString)));

                QDBusConnection::sessionBus ().connect ("org.thesii.Wintermute","/Factory",
                                                        "org.thesii.Wintermute.Factory","aboutToQuit",
                                                        this,SLOT(aboutToQuit()));

                setParent(p_plgn);
                //setAutoRelaySignals (true);
            }
        }