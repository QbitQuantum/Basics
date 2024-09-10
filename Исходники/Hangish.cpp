int main(int argc, char *argv[])
{
    QCoreApplication::setOrganizationName("Hangish");
    QCoreApplication::setApplicationName("Hangish");
    QCoreApplication::setApplicationVersion("0.6.0");

    QScopedPointer<QGuiApplication> app(SailfishApp::application(argc, argv));
    QScopedPointer<QQuickView> view(SailfishApp::createView());
    ConversationModel *conversationModel = new ConversationModel();
    RosterModel *rosterModel = new RosterModel();
    ContactsModel *contactsModel = new ContactsModel();
    FileModel *fileModel = new FileModel();
    Client *c = new Client(rosterModel, conversationModel, contactsModel);
    ImageHandler *ih = new ImageHandler();
    ih->setAuthenticator(c->getAuthenticator());
    //Do this once when app is launching
    ih->cleanCache();

    view->rootContext()->setContextProperty("conversationModel", conversationModel);
    view->rootContext()->setContextProperty("rosterModel", rosterModel);
    view->rootContext()->setContextProperty("contactsModel", contactsModel);
    view->rootContext()->setContextProperty("fileModel", fileModel);
    view->engine()->rootContext()->setContextProperty("Client", c);
    view->engine()->rootContext()->setContextProperty("ImageHandler", ih);


    QDBusConnection system = QDBusConnection::systemBus();
    if (!system.isConnected())
    {
        qFatal("Cannot connect to the D-Bus session bus.");
        return 1;
    }
    system.connect("net.connman",
                   "/net/connman/technology/wifi",
                   "net.connman.Technology",
                   "PropertyChanged",
                   c,
                   SLOT(connectivityChanged(QString,QDBusVariant))
                  );
    system.connect("net.connman",
                   "/net/connman/technology/cellular",
                   "net.connman.Technology",
                   "PropertyChanged",
                   c,
                   SLOT(connectivityChanged(QString,QDBusVariant))
                  );

    view->setSource(SailfishApp::pathTo("qml/harbour-hangish.qml"));
    view->showFullScreen();
    app->exec();
}