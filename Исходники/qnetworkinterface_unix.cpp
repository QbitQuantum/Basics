static QNetworkInterfacePrivate *findInterface(int socket, QList<QNetworkInterfacePrivate *> &interfaces,
                                               struct ifreq &req)
{
    QNetworkInterfacePrivate *iface = 0;
    int ifindex = 0;

#ifndef QT_NO_IPV6IFNAME
    // Get the interface index
    ifindex = if_nametoindex(req.ifr_name);

    // find the interface data
    QList<QNetworkInterfacePrivate *>::Iterator if_it = interfaces.begin();
    for ( ; if_it != interfaces.end(); ++if_it)
        if ((*if_it)->index == ifindex) {
            // existing interface
            iface = *if_it;
            break;
        }
#else
    // Search by name
    QList<QNetworkInterfacePrivate *>::Iterator if_it = interfaces.begin();
    for ( ; if_it != interfaces.end(); ++if_it)
        if ((*if_it)->name == QLatin1String(req.ifr_name)) {
            // existing interface
            iface = *if_it;
            break;
        }
#endif

    if (!iface) {
        // new interface, create data:
        iface = new QNetworkInterfacePrivate;
        iface->index = ifindex;
        interfaces << iface;

#ifdef SIOCGIFNAME
        // Get the canonical name
        QByteArray oldName = req.ifr_name;
        if (qt_safe_ioctl(socket, SIOCGIFNAME, &req) >= 0) {
            iface->name = QString::fromLatin1(req.ifr_name);

            // reset the name:
            memcpy(req.ifr_name, oldName, qMin<int>(oldName.length() + 1, sizeof(req.ifr_name) - 1));
        } else
#endif
        {
            // use this name anyways
            iface->name = QString::fromLatin1(req.ifr_name);
        }

        // Get interface flags
        if (qt_safe_ioctl(socket, SIOCGIFFLAGS, &req) >= 0) {
            iface->flags = convertFlags(req.ifr_flags);
        }

#ifdef SIOCGIFHWADDR
        // Get the HW address
        if (qt_safe_ioctl(socket, SIOCGIFHWADDR, &req) >= 0) {
            uchar *addr = (uchar *)req.ifr_addr.sa_data;
            iface->hardwareAddress = iface->makeHwAddress(6, addr);
        }
#endif
    }

    return iface;
}