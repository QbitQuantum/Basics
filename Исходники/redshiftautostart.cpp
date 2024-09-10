/*!
 * Main function.
 *
 * Creates a RedshiftEnabler object and connects it to the readyCheck dbus signal, so that if a new redshift plasmoid
 * is created (this sends the readyCheck signal) this is enabled by this program. Moreover this program sends the
 * readyForStart signal once launched to enable already existent redshift plasmoids during the login phase.
 */
int main(int argc, char *argv[])
{
    QCoreApplication app(argc, argv);
    RedshiftEnabler *enabler = new RedshiftEnabler();
    //Responds to the readyCheck signal with a readyForStart signal
    QDBusConnection dbus = QDBusConnection::sessionBus();
    dbus.connect("", "/", "org.kde.redshift", "readyCheck",
                 enabler, SLOT(sendSignal()));
    //Sends the signal once started to enable already possibly running instances of redshift data engine
    enabler->sendSignal();
    return app.exec();
}