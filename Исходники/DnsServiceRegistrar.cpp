/*
 * DnsServiceRegistrar::add
 *
 * Registers a new service.
 *
 * Parameters:
 *	- type: service type
 *	- port: port number of the registered service
 *	- name: service name (optional)
 *
 * Return value: reference of the DNS service if registration was successful, NULL otherwise
 */
DNSServiceRef DnsServiceRegistrar::add(const QString& type, quint16 port, const QString& name)
{
    /* Deal with name default value */
    char *nameStr;
    if (name == "") {
        nameStr = NULL;
    } else {
        nameStr = name.toUtf8().data();
    }

    /* Create and register the new service ref. */
    DNSServiceRef ref;
     DNSServiceErrorType err = DNSServiceRegister(&ref, 0, 0, nameStr, type.toUtf8().data(), NULL,
                                                                 NULL, qToBigEndian(port), 0, NULL, registerCallback, this);
    if (err != kDNSServiceErr_NoError) {
        Model::logger().addEntry(Logger::Error, QString("Error while registering service (error code = %1)").arg(err));
        return NULL;
    }

    /* Create the QSocketNotifier */
    int sockFd = DNSServiceRefSockFD(ref);
    RefNotifier *pNotif = new RefNotifier(ref, sockFd, QSocketNotifier::Read, this);
    connect(pNotif, SIGNAL(activated(int)), this, SLOT(onNotifierActivated()));

    return ref;
}